pote1 = pote1/8 + 3584;		//Tomo solamente los dos bits de mayor peso
factor_amp = pote2/2048;

if(guitarra > pote1)
{
	resta = guitarra - pote1;						//Calculo la diferencia entre
													//el valor de guitarra y el del "espejo"

	guitarra = guitarra - resta*2*factor_amp;		//Le resto a guitarra el doble de la diferencia por
													//el factor de amplitud
}
bitabit(guitarra);
