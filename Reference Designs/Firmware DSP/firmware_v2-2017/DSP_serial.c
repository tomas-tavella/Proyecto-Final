//#include "DSP2833x_Device.h"     // Headerfile Include File
//#include "DSP2833x_Examples.h"   // Examples Include File

//#include "math.h"

#include "DSP_define.h"

#define TIMEOUT 1000 			//En [ms]

void scia_initializate(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_cfg(void);
int scia_receive(void);
void send_polynomial(Polynomial_cfg);

extern volatile Uint32 time_ms;


void scia_initialize(void){

	   InitSciaGpio();
	   scia_fifo_init();	   // Initialize the SCI FIFO
	   scia_cfg();             // Configure SCI

}

/* Envío y repeción de configuraciones */

void send_siegfried(Siegfried_cfg cfg){
	int i=0;

	send16_int(t_SIEGFRIED);

	delayms(1);
	for(i=0;i<6;i++){
		delayms(1);
		send32_float(cfg.C[i]);
	}

	for(i=0;i<2;i++){
		delayms(1);
		send32_float(cfg.W_lim[i]);
	}


	delayms(1);
	send32_float(cfg.R);
	delayms(1);
	send16_int(cfg.Ts);
	delayms(1);
	send32_float(cfg.Kw);
	delayms(1);
	send32_float(cfg.Kt);
	delayms(1);
	send32_float(cfg.KCM);

}

void send_polynomial(Polynomial_cfg cfg){
	int i=0;

	send16_int(t_POLYNOMIAL);

	delayms(1);
	for(i=0;i<5;i++){
		delayms(1);
		send32_float(cfg.C[i]);
	}

	for(i=0;i<2;i++){
		delayms(1);
		send32_float(cfg.W_lim[i]);
	}

	delayms(1);
	send32_float(cfg.R);
	delayms(1);
	send16_int(cfg.Ts);
	delayms(1);
	send16_int(cfg.Ct_on);
	delayms(1);
	send32_float(cfg.Kw);
	delayms(1);
	send32_float(cfg.Kt);
	delayms(1);
	send32_float(cfg.KCM);

}

void send_PID(PID_cfg cfg){
	//int i=0;

	send16_int(t_PID);


	delayms(1);
	send32_float(cfg.K);
	delayms(1);
	send32_float(cfg.Td);
	delayms(1);
	send32_float(cfg.Ti);
	delayms(1);
	send32_float(cfg.N);
	delayms(1);
	send32_float(cfg.reference);
	delayms(1);
	send16_int(cfg.Ts);


}

void send_setup(setup workbench){
int i;
	for(i=0;i<2;i++){
		delayms(1);

		send32_float(workbench.W_sat[i]);
	}

	for(i=0;i<2;i++){
		delayms(1);
		send32_float(workbench.u_sat[i]);
	}

	delayms(1);
	send32_float(workbench.Ku);
	delayms(1);
	send32_float(workbench.KBE);
	delayms(1);
	send32_float(workbench.N);
	delayms(1);
	send32_float(workbench.Tp);

}

Polynomial_cfg receive_polynomial(){
	Polynomial_cfg cfg_temp;
	int i=0;
	for(i=0;i<5;i++){
		cfg_temp.C[i] = _IQ(receive32_float());
	}
	for(i=0;i<2;i++){
			cfg_temp.W_lim[i] = _IQ(receive32_float());
	}
	cfg_temp.R  = _IQ(receive32_float());
	cfg_temp.Ts = receive16_int();
	cfg_temp.Ct_on = receive16_int();
	cfg_temp.Kw = receive32_float();
	cfg_temp.Kt = receive32_float();
	cfg_temp.KCM = receive32_float();

	return cfg_temp;
}

Siegfried_cfg receive_siegfried(){
	Siegfried_cfg cfg_temp;
	int i=0;
	for(i=0;i<6;i++){
		cfg_temp.C[i] = _IQ(receive32_float());
	}
	for(i=0;i<2;i++){
			cfg_temp.W_lim[i] = _IQ(receive32_float());
	}
	cfg_temp.R  = _IQ(receive32_float());
	cfg_temp.Ts = receive16_int();
	cfg_temp.Kw = receive32_float();
	cfg_temp.Kt = receive32_float();
	cfg_temp.KCM = receive32_float();
	return cfg_temp;
}

setup receive_setup(){
	setup workbench;
	int i=0;
	for(i=0;i<2;i++){
		workbench.W_sat[i] = _IQ(receive32_float());
	}
	for(i=0;i<2;i++){
			workbench.u_sat[i] = _IQ(receive32_float());
	}
	workbench.Ku  = _IQ(receive32_float());
	workbench.KBE  = _IQ(receive32_float());
	workbench.N  = _IQ(receive32_float());
	workbench.Tp  = _IQ(receive32_float());


	return workbench;
}

PID_cfg receive_PID(){
	PID_cfg cfg;

	cfg.K  = _IQ(receive32_float());
	cfg.Td  = _IQ(receive32_float());
	cfg.Ti  = _IQ(receive32_float());
	cfg.N  = _IQ(receive32_float());
	cfg.reference  = _IQ(receive32_float());
	cfg.Ts  = receive16_int();


	return cfg;
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
	int received_temp = 0;
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


/************** Configuración de perifericos *********************/
void scia_cfg()
{

	SciaRegs.SCICCR.bit.SCICHAR=0x7;	 //8 char bits
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

	SciaRegs.SCIHBAUD    = 0;//0x0001;  				// 9600 baud @LSPCLK = 37.5MHz.
	SciaRegs.SCILBAUD    = 0x25;//0xF5; // 115200 baud 	//0x00E7;

	SciaRegs.SCIPRI.bit.FREE = 1;
	//SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
	SciaRegs.SCICTL1.bit.SWRESET=1;  //enabled SCI communication
}

// Initalize the SCI FIFO
void scia_fifo_init()
{
	//SciaRegs.SCIFFTX.bit.SCIFFENA=1; //Enable SCI FIFO
	//SciaRegs.SCIFFTX.bit.TXFFINTCLR=1; //Clear flag interrupt
	//SciaRegs.SCIFFTX.bit.TXFFIENA=0; //interrupt based on TXFFIVL match disabled

	SciaRegs.SCIFFTX.all=0xE040;

	//SciaRegs.SCIFFRX.bit.RXFFIENA =0;
	//SciaRegs.SCIFFRX.bit.RXFFINTCLR= 1;
	//SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;
	//SciaRegs.SCIFFRX.bit.RXFFIL=0xf;

    SciaRegs.SCIFFRX.all=0x204f;

    SciaRegs.SCIFFCT.all=0x0;

	//SciaRegs.SCIFFTX.bit.SCIRST=1; //Resume transmit
	//SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1; //Re-enable transmit
	//SciaRegs.SCIFFRX.bit.RXFIFORESET=1; //Re-enable receive

}
