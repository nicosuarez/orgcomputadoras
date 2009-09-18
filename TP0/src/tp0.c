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
		/*Si la cantidad de bytes a leer es mayor o igual
		 * al tamaño del archivo, posiciono al principio sino*/
		if(bytes >= sizeFile)
			fseek(fd, 0, SEEK_SET);
		else
			fseek(fd, sizeFile - bytes, SEEK_SET);
	}
	else
	{
		if(bytes > sizeFile)
			return;
		fseek(fd, bytes, SEEK_SET);
	}
	buffer = (char) fgetc(fd);
	while(!feof(fd))
	{
	 	printf("%c", buffer);
		buffer = (char) fgetc(fd);
	}
	fclose(fd);
}


int main(int argc, char* argv[])
{
	readLines(argv[1], atoi(argv[2]), FIRST_OPTION);
	printf("\n****** FIN readFile FIRST_OPTION ******\n\n");

	readLines(argv[1], atoi(argv[2]), SECOND_OPTION);
	printf("\n****** FIN readFile SECOND_OPTION ******\n\n");

	readBytes(argv[1], atoi(argv[2]), FIRST_OPTION);
	printf("\n****** FIN readBytes FIRST_OPTION ******\n\n");

	readBytes(argv[1], atoi(argv[2]), SECOND_OPTION);
	printf("\n****** FIN readBytes SECOND_OPTION ******\n\n");
	return 0;
}
