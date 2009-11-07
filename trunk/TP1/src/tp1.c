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

int esMayor (char* x, char* y, int num)
{
  if (num){
    return atoi(x) > atoi(y);
  }
  else {
  return strcmp(x , y) > 0;
  }
}

//int main(int argc, char* argv[])
//{
//	int i;
//	int lineas = 20;
//	char** vector = (char**)malloc(sizeof(char*)*lineas);
//	for(i=0; i<lineas; i++)
//	{
//		vector[i] = (char*)malloc(sizeof(char)*MAX);
//	}
//	vector[0] = "1\0";
//	vector[1] = "3\0";
//	vector[2] = "5\0";
//	vector[3] = "2\0";
//	vector[4] = "4\0";
//	vector[5] = "10\0";
//	vector[6] = "7\0";
//	vector[7] = "6\0";
//	vector[8] = "9\0";
//	vector[9] = "8\0";
//	vector[10] = "22\0";
//	vector[11] = "15\0";
//	vector[12] = "18\0";
//	vector[13] = "24\0";
//	vector[14] = "41\0";
//	vector[15] = "120\0";
//	vector[16] = "71\0";
//	vector[17] = "64\0";
//	vector[18] = "95\0";
//	vector[19] = "83\0";
//
//	printf("Antes\n");
//
//	for(i=0; i<lineas; i++)
//	{
//	  printf("%s\n",vector[i]);
//	}
//
//	quickSort(&vector[0], &vector[lineas-1], 1);
//
//	printf("\nDespues\n");
//
//	for(i=0; i<lineas; i++)
//	{
//	  printf("%s\n",vector[i]);
//	}
////	char *cadenas[5];
////	int i;
////	cadenas[0] = "1\0";
////	cadenas[1] = "3\0";
////	cadenas[2] = "5\0";
////	cadenas[3] = "2\0";
////	cadenas[4] = "4\0";
////	printf("Antes: %p\n", cadenas);
////	quickSort(cadenas, cadenas+4, 1);
////	printf("Despues: %p\n", cadenas);
////	for(i=0; i<5; i++)
////	{
////		printf("%s\n", cadenas[i]);
////	}
//	return 0;
//}

int main(int argc, char* argv[]){

	int siguiente_opcion = 0;

	int numeric = 0; /*Por defecto ordena alfabeticamente*/

	int i, j;

	FILE* fdInput, *fdOutput;

	char* file = NULL; /*Nombre del fichero de entrada*/

	/* El nombre del fichero que recibe la salida del programa */
	char* fichero_salida = NULL ;

	/* Una cadena que lista las opciones cortas validas */
	const char* const op_cortas = "hno:V" ;

	/* Una estructura de varios arrays describiendo los valores largos */
	const struct option op_largas[] =
	{
			{ "help",         0,  NULL,   'h'},
			{ "numeric",      0,  NULL,   'n'},
			{ "output",       1,  NULL,   'o'},
			{ "version",       0,  NULL,   'V'},
			{ NULL,           0,  NULL,   0  }
	};

	while (siguiente_opcion != -1)
	{
		/* Llamamos a la funcion getopt */
		siguiente_opcion = getopt_long (argc, argv, op_cortas, op_largas, NULL);

		switch (siguiente_opcion)
		{
			case 'h' : /* -h o --help */
				imprime_uso(stdout);
				exit(EXIT_SUCCESS);

			case 'V' : /* -V o --version*/
				imprime_version();
				exit(EXIT_SUCCESS);

			case 'n' :
				numeric = 1;
				break;

			case 'o' : /* -o o --output*/
				fichero_salida= optarg;
				break;

			case '?' : /* opcion no valida */
				imprime_uso(stderr); /* codigo de salida 1 */
				exit(1);

			case -1 : /* No hay mas opciones */
				break;

			default : /* Algo mas? No esperado. Abortamos */
				abort();
			}
	}

	file = argv[optind];

	if (file != NULL){
		fdInput = fopen(file, "r");
	}
	else{
		fprintf(stderr, "Error: No se especifico el archivo de entrada.\n");
		imprime_uso(stderr);
		exit(1);
	}

	if(fichero_salida == NULL)
	{
		fprintf(stderr, "Error: No se especifico el archivo de salida.\n");
		imprime_uso(stderr);
		return -1;
	}

	/*pude abrir el archivo, estoy situado en la primer linea*/
	int lineas= 0;
	char buffer, charAnterior='\0';

	/*Cuento la cantidad de lineas que tiene el archivo*/
	while (!feof(fdInput)){
		buffer= (char)fgetc(fdInput);
		if (buffer == '\n' && charAnterior !='\n'){
			lineas++;
		}
		charAnterior = buffer;
	}

	/*Recorro de a una las lineas del archivo y las copio en un vector*/
	char** vector = (char**)malloc(sizeof(char*)*lineas);
	fseek(fdInput, 0, SEEK_SET);
	for(i=0; i<lineas; i++)
	{
		vector[i] = (char*)malloc(sizeof(char)*MAX);
		buffer= (char)fgetc(fdInput);
		j=0;
		while(buffer != '\n' && j<MAX-1)
		{
			vector[i][j] = buffer;
			buffer= (char)fgetc(fdInput);
			j++;
		}
		vector[i][j] = '\0';
	}
	printf("Antes de ordenar\n");
	for(i=0; i<lineas; i++)
	{
		printf("%s\n", vector[i]);
	}

	quickSort(&vector[0], &vector[lineas-1], numeric);
	printf("\nDespues de ordenar\n");
	if(strcmp(fichero_salida, "-") != 0)
	{
		fdOutput = fopen(fichero_salida, "wt");
		if(fdOutput == NULL)
		{
			fprintf(stderr, "Error: No se pudo crear el archivo de salida");
			fclose(fdInput);
			for(i=0; i<lineas; i++)
			{
				free(vector[i]);
			}
			free(vector);
			return -1;
		}
	}
	else
	{
		fdOutput = stdout;
	}

	for(i=0; i<lineas; i++)
	{
		fprintf(fdOutput, "%s\n", vector[i]);
		free(vector[i]);
	}
	free(vector);
	fclose(fdInput);
	fclose(fdOutput);
	return 0;
}
