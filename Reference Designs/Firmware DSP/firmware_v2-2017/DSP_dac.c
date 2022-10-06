//#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "DSP_define.h"

void dac_write(Uint16,Uint16);
void dac_read(Uint16);
void dac_init(void);

extern void spi_xmit(Uint16 a);
extern void spi_fifo_init(void);
extern void spi_init(void);


void dac_write(Uint16 command,Uint16 word)
{
	spi_xmit(command);   // Envío comando
    spi_xmit(word>>8);	 // Orden de transmisión MSB a LSB
	spi_xmit(word);
	while (SciaRegs.SCIFFTX.bit.TXFFST!=0){}
}

void dac_init(){

	/* Inicialización de módulo SPI */
	spi_fifo_init();
	spi_init();

	/* Inicialización de CLR & ALARM */
	EALLOW;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;			//DAC-CLR output
	   GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;
	   STOP_on;

	   GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;			//DAC-ALARM input with pullup
	   GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;
	   GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;
	EDIS;
	STOP_off;
	dac_write(COMMAND_CONTROL,0x1001); 			 	// Range = 0-10, enabled, slew rate disable, no Rext
	//STOP_on;
	//dac_write(COMMAND_CONFIG,0x0000); 			 	// Range = 0-10, enabled, slew rate disable, no Rext
}


void dac_read(Uint16 word)
{
	Uint16 ReceivedChar;

	spi_xmit(0x02);   // Envío comando
    spi_xmit(0);	 // Orden de transmisión MSB a LSB
	spi_xmit(word);
	while(SciaRegs.SCIFFRX.bit.RXFFST !=1) { } // wait for XRDY =1 for empty state
			// Get character
	       ReceivedChar = SciaRegs.SCIRXBUF.all;
}
