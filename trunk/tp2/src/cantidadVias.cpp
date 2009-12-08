#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[]){

	register unsigned int vias = atoi(argv[1]);
	register unsigned int tamanioCache = atoi(argv[2]);
	register unsigned int tamanioBloque = atoi(argv[3]);
	register unsigned int i;
	register unsigned int j;
	register unsigned int k;
	register unsigned int tamanioFor;

	char **vector = new char*[vias];
	for (i = 0; i < vias; i++){
		vector[i] = new char[tamanioCache];
	}

	tamanioFor = tamanioCache / tamanioBloque / vias; //cantidad de bloques por via

	for (k = 0; k < 100; k++){
		for(i= 0; i< tamanioFor; i++){
			for(j= 0; j< vias; j++){
				vector[j][i * tamanioBloque]= 'a';
			}
		}
	}

	for(j= 0; j< vias; j++){
		vector[j][0]='z';
	}

	for (i = 0; i < vias; i++){
			delete vector[i];
	}
	delete []vector;
	return 0;
}

