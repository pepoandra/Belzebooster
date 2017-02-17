#include	<p30f2012.h>
#define	FCY	58960000UL		//Frecuencia del oscilador (FRC)
#include	<libpic30.h>
#include	<dsp.h>

_FOSC(FRC_PLL8);						//Oscilador en modo Fast RC
_FWDT(WDT_OFF);					//Watchdog deshabilitado
_FBORPOR(MCLR_EN & PWRT_OFF);	//MCLR habilitado, lo otro ni idea
_FGS(CODE_PROT_OFF);			//Protección del código deshabilitada

void bitabit (unsigned int);
void ADC (char);
void envolvente (char);
void tremolo (void);
void compresor (void);
void distorsion (void);
void anexo6 (unsigned int);


//Declaracion de variables globales
int pote1,pote2,selefe,g_envconta=0,guitarra,g_envacti=0,g_forma,g_periodo=600;
float g_envolvente=1,g_valorinicial=0.5;



int main(void)
{
	int i=0;
	
	TRISC = 0x0000;
	TRISD = 0x0000;
	TRISF = 0x0000;
	g_envacti = 0;
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

		if(g_envacti==0)
			g_envolvente=1;

		if(ADCON1bits.DONE == 1)
		{
			/* //ADCON1bits.SAMP=0;
				switch(i)
				{
					case 0:							
							guitarra = ADCBUF0;
							i++;		
							break;
							
					case 1:
							pote1 = ADCBUF1;
							i++;
							break;
							
					case 2:
							guitarra = ADCBUF2;
							i++;
							break;
							
					case 3: 
							pote2 = ADCBUF3;
							i++;
							break;
							
					case 4:
							guitarra = ADCBUF4;
							i++;
							break;
							
					case 5: 
							guitarra = ADCBUF5;
							i++;
							break;
							
					case 6: 
							selefe = ADCBUF6;
							i++;
							break;
							
					case 7:
							guitarra = ADCBUF7;
							i++;
							break;
							
				
					case 8:
							guitarra = ADCBUF8;
							i++;
							break;
						
					case 9:
							pote1 = ADCBUF9;
							i++;
							break;
						
					case 10: 
							guitarra = ADCBUFA;
							i++;
							break;
						
					case 11: 
							pote2 = ADCBUFB;
							i++;
							break;
						
					case 12: 
							 guitarra = ADCBUFC;
							 i++;
							 break;
							
					case 13:
							 guitarra = ADCBUFD;
							 i++;
							 break;
							
					case 14:
							//selefe = ADCBUFE;
							 i++;
							 break;
							
					case 15:
							 guitarra = ADCBUFF;
							 i = 0;
							 break;
							 
				
				
			}	*/
			selefe = ADCBUF6;
			ADCON1bits.DONE = 0;
			ADCON1bits.SAMP = 1;		//Inicia el sampleo nuevamente
			bitabit(selefe);			//Saca la guitarra por los puertos

		}

		/*
		if (selefe < 1365)
			guitarra=0xFFF;
		if (selefe > 1365 && selefe < 2730)				
			guitarra=0x800;
		if (selefe > 2730)
			guitarra=0x000; */ 
		

	
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
		ADCON1bits.ADON = 0;
		ADCON2bits.VCFG = 0;		//Tensión de referencia: AVdd y AVss
		ADCON3bits.ADCS = 19;		//Frecuencia de sampleo = (19 + 1) * Fcy / 2
		ADCSSL = 0x1DF;			//Selección entradas analógicas escaneadas
		ADCHSbits.CH0NA = 0;		//Entrada negativa CH0 conectada a Vref- AVss
		ADCHSbits.CH0SA = 7;		//Si CSCNA=1, CH0SA es ignorado		
		ADCON2bits.BUFM = 0;		//16 buffers de 16 bits de ancho de palabra
		ADCON2bits.CSCNA = 1;		//Escanear entradas seleccionadas
		ADCON2bits.ALTS = 0;		//Sampling alternado desactivado
		//Probemos aumentando el tiempo de muestreo, a ver si capta algo
		ADCON3bits.SAMC = 31;		//Tiempo de muestreo
		ADCON1bits.SSRC = 7;		//Conversión automática
		ADCON1bits.FORM = 0;		//Formato de salida = "integer"
		ADCON1bits.ASAM = 0;		//Muestreo automático
		ADCON3bits.ADRC = 0;		//Clock derivado del sistema
		ADCON1bits.ADON = 1;		//Enciende el módulo A/D
	}
	else
		ADCON1bits.ADON = 0;
}

void envolvente (char activado)
{
	float periodociclos, ciclo;
	int senoidal;
	g_envacti = activado;	
	g_envconta++;
	periodociclos = g_periodo * 48;
	ciclo = periodociclos / 2;
	if(g_envconta  ==  periodociclos)
		g_envconta = 0;

	switch (g_forma)
	{
		case 0:  // Cuadrada
	
				if(g_envconta > ciclo)
					g_envolvente = 1;
				if(g_envconta  <= ciclo)
					g_envolvente = g_valorinicial;
				break;
			
		case 1:  // Triangular
				if(g_envconta < ciclo)
					g_envolvente = g_valorinicial + ((1 - g_valorinicial)/ciclo) * (g_envconta / 48); 
				if(g_envconta > ciclo)
					g_envolvente =g_valorinicial + ((1 - g_valorinicial)/ciclo) * ((g_envconta / 48) - ciclo / 48);
				break;
				
		case 2:   // Senoidal
				
				senoidal = (sin (g_envconta / (periodociclos/360)))/100;
				g_envolvente = ((1-g_valorinicial) * senoidal) + g_valorinicial;				
				break;
				
		default:
				g_envolvente = 1;
				break;
	}
}
		
void tremolo (void)
{
	unsigned int t_pote1,t_pote2;
	
	t_pote1 = pote1;
	t_pote2 = pote2;
	
	if(t_pote1 < 1365)
	{
		g_forma = 0;
		g_periodo= (t_pote2 / (1365/100)) * 20;
	} 
	
	if(t_pote1 > 1365 && t_pote1 < 2730)
	{
		g_forma = 1;
		t_pote1 = pote1 - 1365;
		g_periodo= (t_pote2 / (1365/100)) * 20;
	}
	
	if(pote1>2730)
	{
		g_forma = 2;
		t_pote1 = pote1 - 2730;
		
		g_periodo= (t_pote2 / (1365/100)) * 20;
	}
	if(g_periodo < 60)
		g_periodo = 60;
	
	g_valorinicial = t_pote2 / 4096;

			
envolvente(1);
}

void compresor (void)
{

	int comp_pote1, comp_npote1, comp_pote2, comp_npote2;
	float divisor, multiplicador;
		envolvente(0);
	comp_pote1 = pote1/4 + 3072; //Pote1 0-1024, con el 0 en 3072 y en 1024 (parte negativa)
	comp_npote1 = 1024 - pote1/4;
	divisor = 4096 / pote1;
	comp_pote2 = pote2/8 + 2560; //Pote2 0-512, con el 0 en 2560
	comp_npote2 = 1536 - pote2/8;
	multiplicador = pote1/pote2;
	
	//Compresión de la señal
	if(guitarra > comp_pote1  && guitarra > 2048)	//Si la señal es mayor al nivel de atenuación
		guitarra = guitarra / divisor;				//se la divide por la relación NvM/Nva
		
	if(guitarra < comp_pote2 && guitarra > 2560)	//Si señal < nv de amplificación & > nv de ruido
		guitarra = guitarra * multiplicador;		//se multiplica por la relación Nva/NvG

	//Lo mismo, pero para la parte negativa de la señal
		
	if(guitarra < comp_npote1 && guitarra < 2048)
		guitarra = guitarra * divisor;
		
	if(guitarra > comp_npote2 && guitarra < 1536)
		guitarra = guitarra / multiplicador;
}

 void distorsion (void)
{
	int		diferencia, bandera, clipp, clipn;
	float	frecuenvo, frecumin;

	clipp = (pote1/4) + 3072;

	if (guitarra > clipp)
		guitarra = clipp;
	
	diferencia = clipp - 2048;
	clipn = 2048 - diferencia;
	
	if (guitarra < clipn)
		guitarra = clipn;
	
	frecuenvo = 1/g_periodo;
	
	frecumin = (pote2 * 10)/4096;
	
	if (frecuenvo == 15)
		bandera = 1;
	if (frecuenvo == frecumin)
		bandera = 0;
	
	if (bandera == 1)
		frecuenvo = frecuenvo - 0.5;
	else
		frecuenvo = frecuenvo + 0.5;
		
	g_periodo = 1/frecuenvo;
	g_valorinicial = 0.5;
	g_forma = 2;
	envolvente(1);
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


