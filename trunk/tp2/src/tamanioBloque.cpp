#include <iostream>

#define ITERACIONES_BLOQUE 1024 * 1024

void tamanioBloque(char *vector){

	register unsigned long i = 0;
	for(i=0; i< ITERACIONES_BLOQUE; i++){
		vector[i]= 'z';
	}
}

int main(int argc, char* argv[]){
	char vector[ITERACIONES_BLOQUE];
	tamanioBloque(vector);
	return 0;
}

