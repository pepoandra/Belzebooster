void distorsion (void);

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
	
	if (bandera = 1)
		frecuenvo = frecuenvo - 0.5;
	else
		frecuenvo = frecuenvo + 0.5;
		
	g_periodo = 1/frecuenvo;
	g_valorinicial = 0.5;
	g_forma = 2;
	envolvente(1);
}

		