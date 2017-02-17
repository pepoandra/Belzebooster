void compresor ()
{
	envolvente(0);
	int comp_pote1, comp_npote1, comp_pote2, comp_npote2:
	float divisor, multiplicador;
	
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
