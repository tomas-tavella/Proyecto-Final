//###########################################################################
//
// FILE:	LM5056.c
//
// TITLE:	LM5056 Initialization & Support Functions.
//



//
// Included Files
//

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "DSP2833x_I2c.h"
#include "LM5056_defines.h"
#include "LM5056_I2C.h"

Uint16 data[13];
struct I2Cmsg *CurrentMsgPtr;             // Used in interrupts

void LM5056_I2CA_Init(void);
__interrupt void i2c_int1a_isr(void);


//
// I2CA_Init -
//
void LM5056_I2CA_Init(void)
{
    EALLOW;
    PieVectTable.I2CINT1A = &i2c_int1a_isr;
    EDIS;

    InitI2CGpio();

    //
    // Initialize I2C
    //
    I2caRegs.I2CSAR = LM5056_ADDR;   // Slave address of LM5056

#if (CPU_FRQ_150MHZ)            // Default - For 150MHz SYSCLKOUT
    //
    // Prescaler - need 7-12 Mhz on module clk (150/15 = 10MHz)
    //
    I2caRegs.I2CPSC.all = 14;
#endif
#if (CPU_FRQ_100MHZ)            // For 100 MHz SYSCLKOUT
    //
    // Prescaler - need 7-12 Mhz on module clk (100/10 = 10MHz)
    //
    I2caRegs.I2CPSC.all = 9;
#endif

    I2caRegs.I2CCLKL = 10;      // NOTE: must be non zero
    I2caRegs.I2CCLKH = 5;       // NOTE: must be non zero - I2c freq 400kHz

    I2caRegs.I2CIER.all = 0x24; // Enable SCD & ARDY interrupts

    //
    // Take I2C out of reset
    // Stop I2C when suspended
    //
    I2caRegs.I2CMDR.all = 0x0020;

    I2caRegs.I2CFFTX.all = 0x6000;  // Enable FIFO mode and TXFIFO
    I2caRegs.I2CFFRX.all = 0x2040;  // Enable RXFIFO, clear RXFFINT,

    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;
    return;
}


//
// I2CA_ReadData -
//
Uint16 LM5056_I2CA_ReadData(struct I2Cmsg *msg)
{

    I2caRegs.I2CMDR.all = 0x0020;
    I2caRegs.I2CFFRX.bit.RXFFRST = 1;

    CurrentMsgPtr = msg;
    //
    // Wait until the STP bit is cleared from any previous master communication.
    // Clearing of this bit by the module is delayed until after the SCD bit is
    // set. If this bit is not checked prior to initiating a new message, the
    // I2C could get confused.
    //

    if (I2caRegs.I2CMDR.bit.STP == 1)
    {
        return I2C_STP_NOT_READY_ERROR;
    }

    I2caRegs.I2CSAR = msg->SlaveAddress;

    //
    // Check if bus busy
    //

    if (I2caRegs.I2CSTR.bit.BB == 1)
    {
        return I2C_BUS_BUSY_ERROR;
    }

    // Send command code to LM5056 - opt: IRS=1 TRX=1 MST=1 - NO STOP COND (STP = 0)
    I2caRegs.I2CCNT = 1;
    I2caRegs.I2CDXR = msg->command;

    I2caRegs.I2CMDR.all = 0x2620;

    msg->MsgStatus =  I2C_MSGSTAT_SEND_NOSTOP_BUSY;

    // Wait until ARDY is received to read data
    while (msg->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY);

    if(msg->MsgStatus == I2C_MSGSTAT_RESTART)
    {
        I2caRegs.I2CCNT = msg->NumOfBytes;  // Setup how many bytes to expect
        I2caRegs.I2CMDR.all = 0x2C20;       // Send restart as master receiver IRS=1 TRX=0 MST = 1 STP = 1
        msg->MsgStatus =  I2C_MSGSTAT_READ_BUSY;
        return I2C_SUCCESS;
    }

    return I2C_ERROR;
}

//
// i2c_int1a_isr - I2C-A
//
__interrupt void i2c_int1a_isr(void)
{
    Uint16 IntSource, i;

    //
    // Read interrupt source
    //
    IntSource = I2caRegs.I2CISRC.all;

    //
    // Interrupt source = stop condition detected
    //
    if(IntSource == I2C_SCD_ISRC)    {
            if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_READ_BUSY) // Expect to reading data
            {

                for(i=0; i < CurrentMsgPtr->NumOfBytes; i++)
                {
                    CurrentMsgPtr->data[i] = I2caRegs.I2CDRR;
                }
                I2caRegs.I2CFFRX.bit.RXFFINTCLR =1;
                I2caRegs.I2CFFRX.bit.RXFFRST = 0;

                CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;
                I2caRegs.I2CMDR.all = 0; // If no ACK bit is received then send STP condition
            }
    }  // end of stop condition detected

    //
    // Interrupt source = Register Access Ready
    // This interrupt is used to determine when the LM5056 address setup
    // portion of the read data communication is complete. Since no stop bit is
    // commanded, this flag tells us when the message has been sent instead of
    // the SCD flag. If a NACK is received, clear the NACK bit and command a
    // stop. Otherwise, move on to the read data portion of the communication.
    //
    else if(IntSource == I2C_ARDY_ISRC)
    {
        if(I2caRegs.I2CSTR.bit.NACK == 1)
        {
            I2caRegs.I2CMDR.bit.STP = 1;
            I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT; // If no ACK bit is received then send STP condition
        }
        if(CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY)
        {
            CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_RESTART; // If ACK bit is received then resend Start condition to read data
        }
    }

    else
    {
        //
        // Generate some error due to invalid interrupt source
        //
        __asm("   ESTOP0");
    }

    //
    // Enable future I2C (PIE Group 8) interrupts
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}


//
// End of file
//

