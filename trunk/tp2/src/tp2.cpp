#include <stdio.h>
#include <stdlib.h>
#include <iostream>


void cantidadDeVias(register int vias, register int tamanioCache, register int tamanioBloque){
	//register char c;
	//char vector[tamanioCache/ vias][vias];
	char vector[tamanioCache][vias];

	for(register int j= 0; j< vias; j++){
		for(register int i= 0; i< tamanioCache/vias/tamanioBloque; i++){

			vector[i * tamanioBloque][j]= 'a';
		}
	}
	for(register int j= 0; j< vias; j++){
		vector[0][j]= 'a';
	}

}



int main(int argc, char* argv[]){
	std::cout << atoi(argv[1]) << " " << atoi(argv[2]) << " " << atoi(argv[3]);
	cantidadDeVias(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	return 0;
}
