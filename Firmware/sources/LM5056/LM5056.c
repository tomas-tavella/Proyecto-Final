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
#include "LM5056_defines.h"
#include "LM5056_I2C.h"
#include "LM5056.h"



struct LM5056_AVG_BLOCK_READ LM5056_avg_block_rawData;
struct LM5056_avg_measures avg_measures;
struct I2Cmsg LM5056_comm;

void LM5056_Read_avg_block(void){
    LM5056_comm.MsgStatus = I2C_MSGSTAT_INACTIVE;
    LM5056_comm.SlaveAddress = LM5056_ADDR;
    LM5056_comm.NumOfBytes = 13;
    LM5056_comm.command = MFR_AVG_BLOCK_READ;
    LM5056_comm.data = &LM5056_avg_block_rawData;

    while(LM5056_I2CA_ReadData(&LM5056_comm) != I2C_SUCCESS);
}

void LM5056_measures(void){

    Uint16 temp;
    temp = (LM5056_avg_block_rawData.AVG_VIN.msb<<8)|(LM5056_avg_block_rawData.AVG_VIN.lsb);
    avg_measures.AVG_VIN = (temp*VIN_10_R - VIN_B_m)/VIN_M_m;

    temp = (LM5056_avg_block_rawData.AVG_VOUT.msb<<8)|(LM5056_avg_block_rawData.AVG_VOUT.lsb);
    avg_measures.AVG_VOUT = (temp*VOUT_10_R - VOUT_B)/VOUT_M;

    temp = (LM5056_avg_block_rawData.AVG_IIN.msb<<8)|(LM5056_avg_block_rawData.AVG_IIN.lsb);
    temp = ((temp^0xfff)+1)&&0xfff;
    avg_measures.AVG_IIN = (temp*IIN_10_R - IIN_B)/IIN_M;

    temp = (LM5056_avg_block_rawData.AVG_PIN.msb<<8)|(LM5056_avg_block_rawData.AVG_PIN.lsb);
    avg_measures.AVG_PIN = (temp*PIN_10_R - PIN_B)/PIN_M;

    temp = (LM5056_avg_block_rawData.TEMPERATURE.msb<<8)|(LM5056_avg_block_rawData.TEMPERATURE.lsb);
    avg_measures.TEMPERATURE = (temp*TEMPERATURE_10_R - TEMPERATURE_B)/TEMPERATURE_M;

}



//
// End of file
//

