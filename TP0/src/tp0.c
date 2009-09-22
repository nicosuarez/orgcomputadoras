#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define FIRST_OPTION 0
#define SECOND_OPTION 1

/*Muestra las ultimas de un archivo
 * Parametros:
 * 	path: ruta del archivo a leer
 * 	lines: cantidad de lineas a leer
 * 	option: si option=0 lee las ultimas lineas, si option=1 lee desde la linea igual a lines*/
void readLines(char *path, int lines, int option)
{
	FILE *fd1, *fd2;
	int countLines=0;
	char buffer;

	fd1 = fopen(path, "r");
	if(fd1 == NULL)
	{
		printf("No se pudo abrir el archivo: %s", path);
		return;
	}

	if( option == SECOND_OPTION )
	{
		countLines = 1;
		buffer = (char) fgetc(fd1);
		while(!feof(fd1))
		{
			if(countLines == lines)
			 	printf("%c", buffer);
			else if(buffer == '\n')
				countLines++;
			buffer = (char) fgetc(fd1);
		}
		fclose(fd1);
		return;
	}

	fd2 = fopen(path, "r");
	if(fd1 == NULL)
	{
		printf("No se pudo abrir el archivo: %s", path);
		fclose(fd1);
		return;
	}

	buffer = (char) fgetc(fd1);
	while(!feof(fd1))
	{
		if(buffer == '\n')
		{
			if(countLines < lines)
				countLines++;
			else
				while((char)fgetc(fd2) != '\n')
				{
				}
		}
		buffer = (char) fgetc(fd1);
	}
	if(countLines == lines)
		while((char)fgetc(fd2) != '\n')
		{
		}
	buffer = (char) fgetc(fd2);
	while(!feof(fd2))
	{
		printf("%c", buffer);
		buffer = (char) fgetc(fd2);
	}
	fclose(fd1);
	fclose(fd2);
}


/*Muestra los bytes de un archivo
 * Parametros:
 * 	path: ruta del archivo a leer
 * 	bytes: cantidad de bytes a leer
 * 	option: si option=0 lee los ultimos bytes, si option=1 lee desde el byte igual a bytes*/
void readBytes(char *path, int bytes, int option)
{
	FILE *fd;
	char buffer;
	int sizeFile = 0;
	fd = fopen(path, "rb");
	if(fd == NULL)
	{
		printf("No se pudo abrir el archivo: %s", path);
		return;
	}
	fseek(fd, 0, SEEK_END);
	sizeFile = ftell(fd);
	if(option == SECOND_OPTION)
	{
		/*aca lo modifique porq me parece q estaba mal apuntado.. avisen
		 * igual quedo comentado como estaba antes*/

		/*Si la cantidad de bytes a leer es mayor o igual
		 * al tamaño del archivo, posiciono al principio sino*/
		/*if(bytes >= sizeFile)
			fseek(fd, 0, SEEK_SET);
		else
			fseek(fd, sizeFile - bytes, SEEK_SET);*/

		/* tiene q empezar a leer en una posicion mayor al tamaño del archivo
		 * entonces no lee nada*/
		if (bytes >= sizeFile)
			return;
		else
			fseek(fd, bytes, SEEK_SET);
	}
	else
	{
		/* esto tmb me parece q estaba mal */

		/*if(bytes > sizeFile)
			return;
		fseek(fd, bytes, SEEK_SET);*/
		if (bytes > sizeFile)
			return;
		fseek(fd, sizeFile - bytes, SEEK_SET);
	}
	buffer = (char) fgetc(fd);
	while(!feof(fd))
	{
	 	printf("%c", buffer);
		buffer = (char) fgetc(fd);
	}
	fclose(fd);
}

const char* nombre_programa;


void imprime_uso (){
    printf("Uso: %s opciones [ argumentos ...] NOMBRE_ARCHIVO\n", nombre_programa);
    printf("    -h  --help                  Ense�a esta ayuda\n"
           "    -n  --lines lineas          Cantidad de lineas a leer\n"
           "    -b  --bytes                 Lee la cantidad de bytes en vez de las lineas\n");
}

void imprime_version(){
	printf("Version [66.20] Organizacion de Computadoras\n"
		   "Segundo Cuatrimestre 2009");
}



char* substr(char* cadena, int comienzo, int longitud)
{
	if (longitud == 0) longitud = strlen(cadena)-comienzo-1;

	char *nuevo = (char*)malloc(sizeof(char) * longitud);

	strncpy(nuevo, cadena + comienzo, longitud);

	return nuevo;
}

/*define la cantidad de lineas a leer, y la opcion de lectura*/
void definirLineas(int siguiente_archivo, int optind, int argc, char* argv[],
		char* cantLineasString){

		char* file = NULL;

		if (siguiente_archivo == -1)
			siguiente_archivo = optind;
		else siguiente_archivo++;

		if (siguiente_archivo < argc){
			file = argv[siguiente_archivo++];
		}

		if (file == NULL){
			imprime_uso();
	        exit(1);
	    }

		int readingOption = FIRST_OPTION;

		int cantLineas;

		if (cantLineasString[0] == '+'){
			readingOption = SECOND_OPTION;
			cantLineas = atoi(substr(cantLineasString, 1,0));
			cantLineas++;
		} else {
			cantLineas = atoi(cantLineasString);
			cantLineas++;
		}

		readLines(file, cantLineas, readingOption);

}



int main(int argc, char* argv[])
{
	int siguiente_opcion;

	  /* Una cadena que lista las opciones cortas v�lidas */
	  const char* const op_cortas = "hb:n:V" ;

	  /* Una estructura de varios arrays describiendo los valores largos */
	  const struct option op_largas[] =
	  {
	      { "help",         0,  NULL,   'h'},
	      { "bytes",      1,  NULL,   'b'},
	      { "lines",       1,  NULL,   'n'},
	      { "version",       0,  NULL,   'V'},
	      { NULL,           0,  NULL,   0  }
	  };

	  int showBytes = 1;

	  char* cantLineasString = "10"; //Le pongo por default 10 lineas
	  char* cantBytesString = NULL;

	  /* Guardar el nombre del programa para incluirlo a la salida */
	  nombre_programa = argv[0];

	  /* Guarda la posicion del siguiente archivo a leer*/
	  int siguiente_archivo= -1;

	  /* Si se ejecuta sin par�metros ni opciones */
	  if (argc == 1)
	  {
	      imprime_uso();
	      exit(EXIT_SUCCESS);
	  }

	  while (1)
	  {
	      /* Llamamos a la funci�n getopt */
	      siguiente_opcion = getopt_long (argc, argv, op_cortas, op_largas, NULL);

	      if (siguiente_opcion == -1)
	          break; /* No hay m�s opciones. Rompemos el bucle */

	      switch (siguiente_opcion)
	      {
	          case 'h' : /* -h o --help */
	              imprime_uso();
	              exit(EXIT_SUCCESS);

	          case 'V' : /* -V o --version*/
	        	  imprime_version();
	        	  exit(EXIT_SUCCESS);

	          case 'b' : 				  
				  cantBytesString = optarg;
	              break;

	          case 'n' : 
				  showBytes = 0;
	              cantLineasString = optarg;

	              definirLineas(siguiente_archivo, optind, argc, argv,
	            			cantLineasString);
	              break;

	          case '?' : /* opci�n no valida */
	              imprime_uso(); /* c�digo de salida 1 */
	              exit(1);

	          case -1 : /* No hay m�s opciones */
	              break;

	          default : /* Algo m�s? No esperado. Abortamos */
	              abort();
		  }
	  }



	  /* ESTO LO DEJE COMENTADO PORQ ME FALTA COMPLETAR
	   * LA PARTE DE DEFINIR_BYTES()*/

	  /*char* file = NULL;

	  if (optind < argc)
	  {
		  //Supuestamente llega al final el nombre de archivo y lo leo.
	      file = argv[optind++];
	  }

	  if (file == NULL){
		  imprime_uso();
		  exit(1);
	  }

	  int readingOption = FIRST_OPTION;

	  int cantLineas;
	  int cantBytes;

	  if (cantLineasString[0] == '+'){
		    readingOption = SECOND_OPTION;
			cantLineas = atoi(substr(cantLineasString, 1,0));
	  } else {
		    cantLineas = atoi(cantLineasString);
	  }
	  
	  if (cantBytesString != NULL){
		  if (cantBytesString[0] == '+'){
				readingOption = SECOND_OPTION;
				cantBytes = atoi(substr(cantBytesString, 1,0));
		  } else {
				cantBytes = atoi(cantBytesString);
		  }
	  } else {
		  showBytes = 0;  
	  }  

	  if (showBytes){
		  readBytes(file, cantBytes, readingOption);
		  printf("\n****** FIN readBytes ******\n\n");
	  } else {
		  readLines(file, cantLineas, readingOption);
		  printf("\n****** FIN readFile ******\n\n");

	  }*/



	return 0;
}
