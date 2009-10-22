#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "qsort.c"


void ordenar(int *,int,int);

void imprime_uso (){
    printf("Usage:\n");
    printf("	qsort -h\n"
           "	qsort -V\n"
           "	qsort [options] archivo\n"
           "Options:\n"
    	   "	-h, --help		Imprime ayuda.\n"
    	   "	-V, --version   Version del programa.\n"
    	   "	-o, --output    Archivo de salida.\n"
    	   "	-n, --numeric   Ordenar los datos numericamente en vez de alfabeticamente.\n"
           "Examples:\n"
    	   "	qsort -n numeros.txt\n");
}

void imprime_version(){
	printf("Version [66.20] Organizacion de Computadoras\n"
		   "Segundo Cuatrimestre 2009\n");
}


int main(int argc, char* argv[]){

	int siguiente_opcion = 0;

	int numeric = 0; //Por defecto ordena alfabeticamente

	/* El nombre del fichero que recibe la salida del programa */
	const char* fichero_salida = NULL ;

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
				imprime_uso();
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
				imprime_uso(); /* codigo de salida 1 */
				exit(1);

			case -1 : /* No hay mas opciones */
				break;

			default : /* Algo mas? No esperado. Abortamos */
				abort();
			}
	}

	char* file = NULL;
	file = argv[optind];

	FILE* fd;

	if (file != NULL){
		fd = fopen(file, "r");
	}
	else{
		imprime_uso();
		exit(1);
	}

	//pude abrir el archivo, estoy situado en la primer linea
	int lineas= 1;
	char buffer;

	while (!feof(fd)){
		buffer= (char)fgetc(fd);
		if (buffer == '\n'){
			lineas++;
		}
	}

	char** vector[lineas];
	char* s;

	fd = fopen(file, "r");

	int i;
	//recorro de a una las lineas del archivo
	for(i=0; i<lineas; i++){
		s= NULL;
		buffer= (char)fgetc(fd);
		while(buffer != '\n'){
			s= strcat(s, &buffer);
			buffer= (char)fgetc(fd);
		}
		vector[i]= &s;
	}

	quicksort(vector[0], vector[lineas-1], numeric);


	//ejemplo
	/*int N = 7;
	int array[N];

	int i = 0;
	array[i++] = 1;
	array[i++] = 7;
	array[i++] = 8;
	array[i++] = 256;
	array[i++] = 5;
	array[i++] = 4;
	array[i++] = 10;

	// Dar valores al array
	ordenar(array,0,N-1); // Para llamar a la función

	for ( i = 0; i < N; i++){
		printf("%i \n", array[i]);
	}*/

	return 0;
}

//parametros pedidos en el tp son distintos
void ordenar(int *array,int desde,int hasta)
{
	int i,d,aux; // i realiza la búsqueda de izquierda a derecha
	// y j realiza la búsqueda de derecha a izquierda.
	if(desde>=hasta)
	return;

	for(i=desde+1,d=hasta;;) // Valores iniciales de la búsqueda.
	{
		for(;i<=hasta && array[i]<=array[desde];i++); // Primera búsqueda
			for(;d>=0 && array[d]>=array[desde];d--); // segunda búsqueda
				if(i<d) // si no se han cruzado:
				{
					aux=array[i]; // Intercambiar.
					array[i]=array[d];
					array[d]=aux;
				}
				else // si se han cruzado:
					break; // salir del bucle.
	}
	if(d==desde-1) // Si la segunda búsqueda se sale del array
		d=desde; // es que el pivote es el elemento

	// más pequeño: se cambia con él mismo.
	aux=array[d]; // Colocar el pivote
	array[d]=array[desde]; // en su posición.
	array[desde]=aux;

	ordenar(array,desde,d-1); // Ordenar el primer array.
	ordenar(array,d+1,hasta); // Ordenar el segundo array.
}
