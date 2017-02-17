#include	<p30f2012.h>
#define	FCY	58960000UL		//Frecuencia del oscilador (FRCx8)
#include	<libpic30.h>

_FOSC(FRC_PLL8);						//Oscilador en modo Fast RC
_FWDT(WDT_OFF);					//Watchdog deshabilitado
_FBORPOR(MCLR_EN & PWRT_OFF);	//MCLR habilitado, lo otro ni idea
_FGS(CODE_PROT_OFF);			//Protección del código deshabilitada

unsigned int pote1,pote2,selefe,g_envconta=0,guitarra;


void bitabit (unsigned int);

void ADC (char);

int main()
{
	int i=0;
	TRISC = 0;					
	TRISD = 0;
	TRISF = 0;
	ADPCFG = 0x220;				// 1 = digital, 0 = analógico
	TRISB = 0x1DF;				//Config bits como entradas o salidas. 1 = input, 0 = output
	ADC(1);						//Llamada a la función ADC, que configura el módulo ADC
	
	selefe=0x0F0;
	while(1)
	{
	ADCON1bits.SAMP = 1;		//Inicia el sampleo
	__delay32(1000);
	ADCON1bits.SAMP = 0;
		if(ADCON1bits.DONE == 1)
			selefe=ADCBUF6;			
		
		bitabit(selefe);			//Saca la guitarra por los puertos
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

void ADC (char habilitar)
{
	if(habilitar  ==  1)
	{
		ADCON2bits.VCFG = 0;		//Tensión de referencia: AVdd y AVss
		ADCON3bits.ADCS = 63;		//Frecuencia de sampleo = (19 + 1) * Fcy / 2
		ADCSSL = 0;				//Selección entradas analógicas escaneadas
		ADCHSbits.CH0NA = 0;		//Entrada negativa CH0 conectada a Vref- AVss
		ADCHSbits.CH0SA = 7;		//Si CSCNA=1, CH0SA es ignorado		
		ADCON2bits.BUFM = 0;		//16 buffers de 16 bits de ancho de palabra
		ADCON2bits.CSCNA = 0;		//Escanear entradas seleccionadas
		ADCON2bits.ALTS = 0;		//Sampling alternado desactivado
		ADCON3bits.SAMC = 31;		//Tiempo de muestreo
		ADCON1bits.SSRC = 0;		//Conversión automática
		ADCON1bits.FORM = 0;		//Formato de salida = "integer"
		ADCON1bits.ASAM = 0;		//Muestreo manual 0  -   Automático 1
	//	ADCON3bits.ADRC = 0;		//Clock derivado del sistema
		ADCON1bits.ADON = 1;		//Enciende el módulo A/D
	}
	else
		ADCON1bits.ADON = 0;
}
