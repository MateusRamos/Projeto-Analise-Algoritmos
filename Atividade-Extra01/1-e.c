void letraE(int n, int m, int B) {
    int resultado = 0, produto = 1;

	for(i = 1; i <= n; i++)
	{
   		for(j = 1; j <= m; j++)
    	{
 			produto = produto * B[i][j];
    	}
    	
		if(soma > resultado)
		{
			resultado = B[i][j];
		}	
			
		soma = 0;
	}

    return resultado;
}

