// TI File $Revision: /main/2 $
// Checkin $Date: March 22, 2007   10:40:22 $
//###########################################################################
//
// FILE:   DSP2833x_I2c.h
//
// TITLE:  DSP2833x Enhanced Quadrature Encoder Pulse Module
//         Register Bit Definitions.
//
//###########################################################################

#ifndef LM5056_I2C_H
#define LM5056_I2C_H



//
// Defines
//
#define I2C_SLAVE_ADDR        0x40
#define I2C_NUMBYTES          2
#define I2C_EEPROM_HIGH_ADDR  0x00
#define I2C_EEPROM_LOW_ADDR   0x30
#define I2C_COMMAND           0xdc




struct I2Cmsg
{
    Uint16 MsgStatus;   // Word stating what state msg is in:
                        //   I2C_MSGCMD_INACTIVE = do not send msg
                        //   I2C_MSGCMD_BUSY = msg start has been sent,
                        //                     awaiting stop
                        //   I2C_MSGCMD_SEND_WITHSTOP = command to send
                        //       master trans msg complete with a stop bit
                        //   I2C_MSGCMD_SEND_NOSTOP = command to send
                        //       master trans msg without the stop bit
                        //   I2C_MSGCMD_RESTART = command to send a restart
                        //       as a master receiver with a stop bit
    Uint16 SlaveAddress; // I2C address of slave msg is intended for
    Uint16 NumOfBytes;   // Num of valid bytes in (or to be put in MsgBuffer)

    //
    // Command of LM5056A
    //
    Uint16 command;


    //
    // Array holding msg data - max that MAX_BUFFER_SIZE can be is 16 due to
    // the FIFO's
    Uint16 *data;
};


#endif  // end of LM5056_I2C_H definition

//
// End of file
//

