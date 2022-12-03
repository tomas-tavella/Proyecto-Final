//#include "DSP2833x_Device.h"     // Headerfile Include File
//#include "DSP2833x_Examples.h"   // Examples Include File

//#include "math.h"



#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"

#define TIMEOUT 1000 			//En [ms]
#define SENDFRAME_FLOAT 0x11
#define SENDFRAME_INT 0x12
#define ENDFRAME 0x10

void scia_initializate(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_cfg(void);
int scia_receive(void);

extern volatile Uint32 time_ms;

void floattoa(float n, char* res, int afterpoint);

void scia_initialize(void){

	   InitSciaGpio();
	   scia_fifo_init();	   // Initialize the SCI FIFO
	   scia_cfg();             // Configure SCI

}


/************** Configuración de perifericos *********************/
void scia_cfg()
{

    SciaRegs.SCICCR.bit.SCICHAR=0x7;     //8 char bits
    SciaRegs.SCICCR.bit.ADDRIDLE_MODE=0; //Iddle mode enabled

    SciaRegs.SCICCR.bit.LOOPBKENA=0;     //No loopback enabled
    SciaRegs.SCICCR.bit.PARITYENA=0;     //No parity bit
    SciaRegs.SCICCR.bit.STOPBITS=0;      //1 stop bit

    //SciaRegs.SCICCR.all =0x0007; // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
    SciaRegs.SCICTL1.bit.SWRESET=0;
    SciaRegs.SCICTL1.bit.RXENA=1;       //RX enabled
    SciaRegs.SCICTL1.bit.TXENA=1;       //TX enabled
    SciaRegs.SCICTL1.bit.RXERRINTENA=0; //Receive error disabled
    SciaRegs.SCICTL1.bit.SLEEP=0;       //Sleep disabled
    SciaRegs.SCICTL1.bit.TXWAKE=0;


    //SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE

    SciaRegs.SCICTL2.bit.RXBKINTENA=1;
    SciaRegs.SCICTL2.bit.TXINTENA=1;
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA =1;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1;


    SciaRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 37.5MHz.
    SciaRegs.SCILBAUD    =0x00E7;
    //SciaRegs.SCIHBAUD    = 0;//0x0001;                  // 9600 baud @LSPCLK = 37.5MHz.
    //SciaRegs.SCILBAUD    = 0x25;//0xF5; // 115200 baud  //0x00E7;

    SciaRegs.SCIPRI.bit.FREE = 1;
    //SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
    SciaRegs.SCICTL1.bit.SWRESET=1;  //enabled SCI communication
}

// Initalize the SCI FIFO
void scia_fifo_init()
{
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x204f;
    SciaRegs.SCIFFCT.all=0x0;
}



/* Funciones de envio y recepción de datos */
void send32_float(float data){
	int j=0,a;
	Uint32* temp = &data;
	scia_xmit(SENDFRAME_FLOAT);
	for(j=0;j<4;j++){
		a = (*temp>>(8*j))&0xff;
		scia_xmit(a);
	}

	scia_xmit(ENDFRAME);
}

void send16_int(int data){
	int j=0;
	int* temp = &data;

	scia_xmit(SENDFRAME_INT);
	for(j=0;j<2;j++){
		scia_xmit(*temp>>(8*j));
	}

	scia_xmit(ENDFRAME);
}

float receive32_float(){
	Uint32 received_temp = 0;
	float ReceivedData=0.0;
	Uint32 *temp = &ReceivedData;
	Uint32 data_temp=0;
	Uint32 time = time_ms;
	int f_exit=0, i=0;

	/* Espera SENDFRAME */
if (scia_receive()!=SENDFRAME_FLOAT)
	return INFINITY;

/* Recibe 4 datos de 8 bits y los concatena en un dato FLOAT */
while(!f_exit){
	received_temp = scia_receive();
	if(received_temp  != -1) { // wait for RRDY/RXFFST =1 for 1 data available in FIFO
		data_temp = data_temp|(received_temp<<(i*8));
		i++;
		if (i>3){
			*temp = data_temp;
			f_exit=1;
		}
	}
	if (time_ms-time > TIMEOUT)
		break;
}

/* Si TIMEOUT */
if (f_exit == 0)
	return INFINITY;

/* Espera de ENDFRAME */
if (scia_receive()!=ENDFRAME)
	return INFINITY;

/* Si recibe ENDFRAME devolver dato FLOAT */
return ReceivedData;
}


int receive16_int(){

int ReceiveData=0,temp_data;
Uint32 time = time_ms;
int f_exit=0, i=0;

if (scia_receive()!=SENDFRAME_INT)
	return -1;

while(!f_exit){

	temp_data = scia_receive();
	if(temp_data != -1) { // wait for RRDY/RXFFST =1 for 1 data available in FIFO
		ReceiveData |= ((temp_data)<<(8*i));
		i++;
		if (i>1)
			f_exit=1;
	}
	if (time_ms-time > TIMEOUT)
		break;
}

if (f_exit == 0)
	return -1;
if (scia_receive()!=ENDFRAME)
	return -1;
return ReceiveData;
}



/* Funciones locales */

// Transmit a character from the SCI
void scia_xmit(int a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
    SciaRegs.SCITXBUF= a&0xff;
}

int scia_receive()
{
	Uint32 time = time_ms;
    while ((SciaRegs.SCIFFRX.bit.RXFFST == 0)&&(time_ms-time < TIMEOUT)) {}
    if(SciaRegs.SCIFFRX.bit.RXFFST > 0)
    	return SciaRegs.SCIRXBUF.all;
    return -1;
}

// Send String of characters
void scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}

// Float to string
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating-point/double number to a string.
void floattoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}


