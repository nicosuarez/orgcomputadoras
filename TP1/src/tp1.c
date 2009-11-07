#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
//#include "qsort.h"

#define MAX 256

void imprime_uso (FILE *output){
    fprintf(output, "Usage:\n");
    fprintf(output, "	qsort -h\n"
           "	qsort -V\n"
           "	qsort [options] archivo\n"
           "Options:\n"
    	   "	-h, --help	Imprime ayuda.\n"
    	   "	-V, --version   Version del programa.\n"
    	   "	-o, --output    Archivo de salida.\n"
    	   "	-n, --numeric   Ordenar los datos numericamente en vez de alfabeticamente.\n"
           "Examples:\n"
    	   "	qsort -n -o salida.txt numeros.txt\n");
}

void imprime_version(){
	printf("Version [66.20] Organizacion de Computadoras\n"
		   "Segundo Cuatrimestre 2009\n");
}

void swap(char** a, char** b)
{
  char* temp=*a;

  *a=*b;

  *b=temp;

}

int esMayor (char* x, char* y, int num)
{
  if (num){
    return atoi(x) > atoi(y);
  }
  else {
  return strcmp(x , y) > 0;
  }
}

int main(int argc, char* argv[])
{
	int i;
	int lineas = 20;
	char** vector = (char**)malloc(sizeof(char*)*lineas);
	for(i=0; i<lineas; i++)
	{
		vector[i] = (char*)malloc(sizeof(char)*MAX);
	}
	vector[0] = "1\0";
	vector[1] = "3\0";
	vector[2] = "5\0";
	vector[3] = "2\0";
	vector[4] = "4\0";
	vector[5] = "10\0";
	vector[6] = "7\0";
	vector[7] = "6\0";
	vector[8] = "9\0";
	vector[9] = "8\0";
	vector[10] = "22\0";
	vector[11] = "15\0";
	vector[12] = "18\0";
	vector[13] = "24\0";
	vector[14] = "41\0";
	vector[15] = "120\0";
	vector[16] = "71\0";
	vector[17] = "64\0";
	vector[18] = "95\0";
	vector[19] = "83\0";

	printf("Antes\n");

	for(i=0; i<lineas; i++)
	{
	  printf("%s",vector[i]);
	}

	quickSort(&vector[0], &vector[lineas-1], 1);

	printf("Despues\n");

	for(i=0; i<lineas; i++)
	{
	  printf("%s",vector[i]);
	}
//	char *cadenas[5];
//	int i;
//	cadenas[0] = "1\0";
//	cadenas[1] = "3\0";
//	cadenas[2] = "5\0";
//	cadenas[3] = "2\0";
//	cadenas[4] = "4\0";
//	printf("Antes: %p\n", cadenas);
//	quickSort(cadenas, cadenas+4, 1);
//	printf("Despues: %p\n", cadenas);
//	for(i=0; i<5; i++)
//	{
//		printf("%s\n", cadenas[i]);
//	}
	return 0;
}


