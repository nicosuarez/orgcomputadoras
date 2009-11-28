#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define ITERACIONES_BLOQUE 1024 * 1024

void tamanioBloque(){
	register char c;
	char* vector = new char[ITERACIONES_BLOQUE];
	register unsigned int i = 0;
	for(; i< ITERACIONES_BLOQUE; i++){
		vector[i]= 'z';
	}
}



int main(int argc, char* argv[]){
	tamanioBloque();
	return 0;
}
