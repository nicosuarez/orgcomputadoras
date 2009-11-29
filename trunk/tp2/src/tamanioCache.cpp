#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void tamanioCache(register int tamanioBloque, register int n){
	register char c;
	char vector[n * tamanioBloque];

	for(register int i= 0; i< n; i++){
		vector[i * tamanioBloque]= 'a';
	}
	for(register int i= 0; i< n; i++){
		vector[i * tamanioBloque]= 'a';
	}

}
