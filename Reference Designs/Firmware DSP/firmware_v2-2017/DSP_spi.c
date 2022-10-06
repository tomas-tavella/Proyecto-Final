//#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "DSP_define.h"


void spi_xmit(Uint16 a);
void spi_fifo_init(void);
void spi_init(void);

void spi_init()
{
	SpiaRegs.SPICCR.all =0x0007;	             // Reset on, rising edge, 8-bit char bits
	SpiaRegs.SPICTL.all =0x0E;    		         // Enable master mode, with delay,
                                                 // enable talk, and SPI int disabled.
	SpiaRegs.SPIBRR =0x007F;   					 // SPI baud rate = (150M/4)/4 = 9.375 MHz
    SpiaRegs.SPICCR.all =0x0087;		         // Relinquish SPI from Reset
    SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission
}

void spi_xmit(Uint16 a)
{
    SpiaRegs.SPITXBUF=(a<<8);
}



void spi_fifo_init()
{
// Initialize SPI FIFO registers
    SpiaRegs.SPIFFTX.all=0xE040;
    SpiaRegs.SPIFFRX.all=0x204f;
    SpiaRegs.SPIFFCT.all=0x0;
}
