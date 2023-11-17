void letraD(int n, int m, int A) {
    int resultado = 0, soma = 0;

	for(j = 1; j <= m; j++)
	{
   		for(i = 1; i <= n; i++)
    	{
 			soma = soma + A[i][j];
    	}
    	
	   	if(resultado == 0)
		{
			resultado = soma;
		}
		else
		{
		    if(soma < resultado)
			{
				resultado = soma;
			}	
		} 
		
		soma = 0;
	}

    return resultado;
}


