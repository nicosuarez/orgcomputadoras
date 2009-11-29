#include <stdio.h>
#include <stdlib.h>
#include <iostream>


void cantidadDeVias(register unsigned int vias, register unsigned int tamanioCache, register unsigned int tamanioBloque){
	//register char c;
	//char vector[tamanioCache/ vias][vias];
	register unsigned int i;
	register unsigned int j;
	register unsigned int tamanioFor;
	register unsigned int tamanioVector = tamanioCache/vias;	
	
	char vector[tamanioVector][vias];
	
//	for (i = 0; i < tamanioVector; i++){
//		vector[i] = new char[vias];
//	}

	tamanioFor = tamanioVector / tamanioBloque;
	for(i= 0; i< tamanioFor; i++){
		for(j= 0; j< vias; j++){
			vector[i * tamanioBloque][j]= 'a';
		}
	}
	for(j= 0; j< vias; j++){
		vector[0][j]= 'a';
	}

}



int main(int argc, char* argv[]){
	std::cout << atoi(argv[1]) << " " << atoi(argv[2]) << " " << atoi(argv[3]) << std::endl;
	//cantidadDeVias(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	
	register unsigned int vias = atoi(argv[1]); 
	register unsigned int tamanioCache = atoi(argv[2]);
	register unsigned int tamanioBloque = atoi(argv[3]);
	register unsigned int i;
	register unsigned int j;
	register unsigned int k;
	register unsigned int tamanioFor;
		
	char vector[tamanioCache][vias];
	
//	for (i = 0; i < tamanioVector; i++){
//		vector[i] = new char[vias];
//	}

	tamanioFor = tamanioCache / tamanioBloque / vias;

	for (k = 0; k < 100; k++){		
		for(i= 0; i< tamanioFor; i++){
			for(j= 0; j< vias; j++){
				vector[i * tamanioBloque][j]= 'a';
			}
		}
	}
	
	for(j= 0; j< vias; j++){
		vector[0][j]= 'a';
	}
	
	
	return 0;
}
