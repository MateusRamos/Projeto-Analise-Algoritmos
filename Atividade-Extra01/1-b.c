void letraB(int n, int m) {
    int i, j;
    int resultado = 0;

    for(i = 1; i <= n; i++)
    {
        for(j = 0; j <=m; j++)
		{
			resultado = resultado + (i * j);		
		}        
    }

    return resultado;
	    
}
