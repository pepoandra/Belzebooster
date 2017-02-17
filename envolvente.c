 distorsion ();

 distorsion ()
{


}
		
		
void envolvente (char);

void envolvente (char activado)
{
	float periodociclos, ciclo;
	g_envacti = activado;	
	g_envconta++;
	periodociclos = g_periodo * 48;
	if(g_envconta == periodociclos)
		g_envconta = 0;

	switch (g_forma)
	{
		case 0:  // Cuadrada
				ciclo = periodociclos / 2;
				if(g_envconta > ciclo)
					g_envolvente = 1;
				if(g_envconta <= ciclo)
					g_envolvente = g_valorinicial;
				if(g_envconta == periodo)
					g_envconta = 0;
				break;
			
		case 1:  // Triangular
				if(g_envconta < periodociclos / 2)
					g_envolvente = ((1 - g_valorinicial)/(periodociclos / 2)) * (g_envconta / 48); 
				if(g_envconta > periodociclos / 2)
					g_envolvente = 1-((1 - g_valorinicial)/(periodociclos / 2)) * ((g_envconta / 48) - (periodociclos/2) / 48);
				break;
				
		case 2:   // Senoidal
				g_envolvente = sin (g_envconta / (periodociclos/360));
				break;
	}
}
		

