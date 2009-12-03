#include <iostream>

void tamanioCache(register int tamanioBloque, register int n, char *vector)
{
	register int i;

	for(i=0; i< n; i++)
	{
		vector[i * tamanioBloque]= 'a';
	}

	for(i=0; i< n; i++)
	{
		vector[i * tamanioBloque]= 'a';
	}
}

int main(int argc, char* argv[])
{
	if(argc >= 3)
	{
		register int tamanioBloque = atoi(argv[1]);
		register int n = atoi(argv[2]);
		char *vector =  new char[n * tamanioBloque];
		tamanioCache(tamanioBloque, n, vector);
		delete []vector;
	}
	return 0;
}

