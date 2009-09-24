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
		/* tiene q empezar a leer en una posicion mayor al tamaño del archivo
		 * entonces no lee nada*/
		if (bytes >= sizeFile)
			return;
		else
			fseek(fd, bytes, SEEK_SET);
	}
	else
	{
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
    printf("    -h  --help                  Muestra esta ayuda y finaliza\n"
           "    -n  --lines lineas          Cantidad de lineas a leer\n"
           "    -c  --bytes                 Lee la cantidad de bytes en vez de las lineas\n");
}

void imprime_version(){
	printf("Version [66.20] Organizacion de Computadoras\n"
		   "Segundo Cuatrimestre 2009");
}


/*define la cantidad de lineas a leer, y la opcion de lectura*/
void definirLineas(int optind, int argc, char* argv[],
		int cantLineas, int showBytes, int readingOption){

		char* file = NULL;

		/*Las siguiente variables se usan para leer la stdin*/
		char* tempFile = "temp_tail.txt";
		char c = '\0';
		FILE *fd;

		/* Guarda la posicion del siguiente archivo a leer*/
		int siguiente_archivo = optind;

		while(siguiente_archivo <= argc)
		{

			if (siguiente_archivo < argc){
				file = argv[siguiente_archivo];
			}
			else /*Si no se paso un archivo por parametro lee de la stdin*/
			{
				if(optind < argc)
					break;
				file = tempFile;
				fd = fopen(file, "wb");
				c = fgetc(stdin);
				while(c != EOF)
				{
					fputc(c, fd);
					c = fgetc(stdin);
				}
				fclose(fd);
			}

			if (file == NULL){
				imprime_uso();
				exit(1);
			}

			/*Si hay mas de un archivo a leer, muestra el nombre del archivo*/
			if(optind + 1 < argc)
				printf("==> %s <==\n", file);

			if(showBytes)
				readBytes(file, cantLineas, readingOption);
			else
				readLines(file, cantLineas, readingOption);
			printf("\n\n");
			siguiente_archivo++;
		}
		if(optind == argc)
			remove(tempFile);
}

int main(int argc, char* argv[])
{
	  int siguiente_opcion = 0;

	  /* Una cadena que lista las opciones cortas validas */
	  const char* const op_cortas = "hc:n:V" ;

	  /* Una estructura de varios arrays describiendo los valores largos */
	  const struct option op_largas[] =
	  {
	      { "help",         0,  NULL,   'h'},
	      { "bytes",      1,  NULL,   'c'},
	      { "lines",       1,  NULL,   'n'},
	      { "version",       0,  NULL,   'V'},
	      { NULL,           0,  NULL,   0  }
	  };

	  int showBytes = 0; //Por defecto muestra las ultimas lineas
	  int cantLineas = 10; //Le pongo por default 10 lineas
	  int readingOption = FIRST_OPTION;

	  /* Guardar el nombre del programa para incluirlo a la salida */
	  nombre_programa = argv[0];

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

	          case 'c' :
	        	  showBytes = 1;
	        	  if(optarg[0]=='+')
	        	  {
	        		  cantLineas = atoi(optarg+1);
	        		  readingOption = SECOND_OPTION;
	        	  }
	        	  else
	        		  cantLineas = atoi(optarg);
	              break;

	          case 'n' :
				  showBytes = 0;
	        	  if(optarg[0]=='+')
	        	  {
	        		  cantLineas = atoi(optarg+1);
	        		  readingOption = SECOND_OPTION;
	        	  }
	        	  else
	        		  cantLineas = atoi(optarg);
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
      definirLineas(optind, argc, argv,
					cantLineas, showBytes, readingOption);
	return 0;
}
