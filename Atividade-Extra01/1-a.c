void letraA(int n, int a) {
    int i;
    float resultado = 0, aux;

    for (i = 1; i <= n; i++)
    {
        aux = i / pow(a,i);
        resultado = resultado + aux;
    }

    return resultado;
	    
}
