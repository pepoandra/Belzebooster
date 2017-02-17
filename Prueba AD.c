#include	<p30f2012.h>
#define	FCY	7370000UL		//Frecuencia del oscilador (FRC)
#include	<libpic30.h>
#include	<dsp.h>

_FOSC(FRC);						//Oscilador en modo Fast RC
_FWDT(WDT_OFF);					//Watchdog deshabilitado
_FBORPOR(MCLR_EN & PWRT_OFF);	//MCLR habilitado, lo otro ni idea
_FGS(CODE_PROT_OFF);			//Protección del código deshabilitada

void bitabit (unsigned int);

int main()
{
	unsigned int ADCVALUE;
	TRISB = 0x0080;
	TRISC = 0;
	TRISD = 0;
	TRISF = 0;
	ADPCFG = 0xFF7F;
	ADCON1 = 0x00E0;
	ADCHS = 0x0007;
	ADCSSL = 0;
	ADCON3 = 0x1F02;
	ADCON2 = 0;
	ADCON1bits.FORM = 0;
	
	ADCON1bits.ADON = 1;
	ADCON1bits.SAMP = 1;
	while(1)
	{
		while(ADCON1bits.DONE==1)
		{	
			ADCVALUE = 0xFEF;
			ADCON1bits.DONE=0;
			ADCON1bits.SAMP = 1;
		}
		bitabit(ADCVALUE);
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




void anexo6 (unsigned int dato)
{
	unsigned int salida;

	salida = dato & 0x0001;
	if(salida == 0x0001)
		PORTBbits.RB0 = 1;
	else
		PORTBbits.RB0 = 0;
		
	salida = dato & 0x0002;
	if(salida == 0x0002)
		PORTBbits.RB1 = 1;
	else
		PORTBbits.RB1 = 0;
		
		salida = dato & 0x0004;
	if(salida == 0x0004)
		PORTBbits.RB2 = 1;
	else
		PORTBbits.RB2 = 0;
		
		salida = dato & 0x0008;
	if(salida == 0x0008)
		PORTBbits.RB3 = 1;
	else
		PORTBbits.RB3 = 0;
		
		salida = dato & 0x0010;
	if(salida == 0x0010)
		PORTBbits.RB4 = 1;
	else
		PORTBbits.RB4 = 0;
		
		salida = dato & 0x0020;
	if(salida == 0x0020)
		PORTBbits.RB5 = 1;
	else
		PORTBbits.RB5 = 0;
	
	__delay32(4000000);
	PORTB=0;
	PORTBbits.RB8=1;
	__delay32(8000000);

			salida = dato & 0x0040;
	if(salida == 0x0040)
		PORTBbits.RB0 = 1;
	else
		PORTBbits.RB0 = 0;
		
		salida = dato & 0x0080;
	if(salida == 0x0080)
		PORTBbits.RB1 = 1;
	else
		PORTBbits.RB1 = 0;
		
		salida = dato & 0x0100;
	if(salida == 0x0100)
		PORTBbits.RB2 = 1;
	else
		PORTBbits.RB2 = 0;
		
		salida = dato & 0x0200;
	if(salida == 0x0200)
		PORTBbits.RB3 = 1;
	else
		PORTBbits.RB3 = 0;
		
		salida = dato & 0x0400;
	if(salida == 0x0400)
		PORTBbits.RB4 = 1;
	else
		PORTBbits.RB4 = 0;
		
		salida = dato & 0x0800;
	if(salida == 0x0800)
		PORTBbits.RB5 = 1;
	else
		PORTBbits.RB5 = 0;
	
		__delay32(4000000);
	
}

