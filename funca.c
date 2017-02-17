#include	<p30f2012.h>
#define	FCY	58960000UL		//Frecuencia del oscilador (FRC)
#include	<libpic30.h>
#include	<dsp.h>

_FOSC(FRC_PLL8);						//Oscilador en modo Fast RC
_FWDT(WDT_OFF);					//Watchdog deshabilitado
_FBORPOR(MCLR_EN & PWRT_OFF);	//MCLR habilitado, lo otro ni idea
_FGS(CODE_PROT_OFF);			//Protección del código deshabilitada

void bitabit (unsigned int);

//Declaracion de variables globales
int selefe;

int main(void)
{
	int i=0;
	
	TRISC = 0x0000;
	TRISD = 0x0000;
	TRISF = 0x0000;
	g_envacti = 0;
	selefe=0x0F0;
	ADPCFG = 0xFF7F;			// 1 = digital, 0 = analog
	TRISB = 0x0080;		//Config bits como entradas o salidas. 1 = input, 0 = output
	
	// /////////////////////////////////////////////////////////////////////////////////////////////////////////
		ADCON1bits.ADON = 0;		//Apaga el módulo A/D
		
		ADCON1bits.SSRC = 0x7;		//Conversión automática
		ADCON1bits.FORM = 0x0;		//Formato de salida = "integer"
		ADCON1bits.ASAM = 0x0;		//Muestreo manual
		
		ADCON2bits.VCFG = 0x000;		//Tensión de referencia: AVdd y AVss
		ADCON2bits.BUFM = 0x0;		//1 buffer de 16 palabras
		ADCON2bits.ALTS = 0x0;		//Mux A activado
		
		ADCSSL = 0x0;					//Selección de entradas analógicas escaneadas
		
		ADCON3bits.SAMC = 0x1F;		//31 Tad
		ADCON3bits.ADRC = 0x1;		//Clock interno del A/D
		ADCON3bits.ADCS = 0x3F;		//Frecuencia de sampleo = (63 + 1) * Fcy / 2
	
		ADCHSbits.CH0NA = 0x000;		//Multiplexor seteado en el channel 0
		ADCHSbits.CH0SA = 0x7;		//Entrada positiva en AN7
	
		ADCON1bits.ADON = 0x1;		//Enciende el módulo A/D
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	
	ADCON1bits.SAMP = 1;		//Inicia el sampleo
	while(1)
	{
		if(ADCON1bits.DONE == 1)
		{
			selefe = ADCBUF0;
			ADCON1bits.DONE = 0;
			ADCON1bits.SAMP = 1;		//Inicia el sampleo nuevamente
			bitabit(selefe);			//Saca la guitarra por los puertos
		}	
	}
	return(0);
}


void bitabit (unsigned int guitarraprocesada)
{
	unsigned int salida;
	
	salida = guitarraprocesada & 0x0001;
	if(salida == 0x0001)
		PORTBbits.RB5 = 1;
	else
		PORTBbits.RB5 = 0;
		
	salida = guitarraprocesada & 0x0002;
	if(salida == 0x0002)
		PORTCbits.RC15 = 1;
	else
		PORTCbits.RC15 = 0;
		
	salida = guitarraprocesada & 0x0004;
	if(salida == 0x0004)
		PORTCbits.RC13 = 1;
	else
		PORTCbits.RC13 = 0;
		
	salida = guitarraprocesada & 0x0008;
	if(salida == 0x0008)
		PORTCbits.RC14 = 1;
	else
		PORTCbits.RC14 = 0;
		
	salida = guitarraprocesada & 0x0010;
	if(salida == 0x0010)
		PORTDbits.RD9 = 1;
	else
		PORTDbits.RD9 = 0;
		
	salida = guitarraprocesada & 0x0020;
	if(salida == 0x0020)
		PORTDbits.RD8 = 1;
	else
		PORTDbits.RD8 = 0;
		
	salida = guitarraprocesada & 0x0040;
	if(salida == 0x0040)
		PORTFbits.RF6 = 1;
	else
		PORTFbits.RF6 = 0;
		
	salida = guitarraprocesada & 0x0080;
	if(salida == 0x0080)
		PORTFbits.RF3 = 1;
	else
		PORTFbits.RF3 = 0;
		
	salida = guitarraprocesada & 0x0100;
	if(salida == 0x0100)
		PORTFbits.RF2 = 1;
	else
		PORTFbits.RF2 = 0;
		
	salida = guitarraprocesada & 0x0200;
	if(salida == 0x0200)
		PORTFbits.RF5 = 1;
	else
		PORTFbits.RF5 = 0;
		
	salida = guitarraprocesada & 0x0400;
	if(salida == 0x0400)
		PORTFbits.RF4 = 1;
	else
		PORTFbits.RF4 = 0;
		
	salida = guitarraprocesada & 0x0800;
	if(salida == 0x0800)
		PORTBbits.RB9 = 1;
	else
		PORTBbits.RB9 = 0;
}
