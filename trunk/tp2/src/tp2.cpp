#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#define TAMANIO_BLOQUE "tamanioBloque"
#define TAMANIO_CACHE "tamanioCache"
#define CANT_VIAS "cantidadVias"
#define CACHEGRIND  "valgrind --tool=cachegrind --log-file=salidaValgrind --cachegrind-out-file=salidaCachegrind "
#define CG_ANNOTATE "cg_annotate --auto=yes --show=Dr,Dw,D1mr,D1mw salidaCachegrind "
#define FILE_OUTPUT_CACHEGRIND "salidaCachegrind"
#define FILE_OUTPUT_CGANNOTATE "salidaCgannotate"
#define FILE_OUTPUT_GREP "salidaGrep"
#define FILE_OUTPUT_VALGRIND "salidaValgrind"
#define SIZE_BUFFER 512

using std::string;

void imprime_uso (FILE *output){
    fprintf(output, "Usage:\n");
    fprintf(output, "	tp2 -h\n"
           "	tp2 -V\n"
           "	tp2 [Cache data]\n"
           "Options:\n"
    	   "	-h, --help	Imprime ayuda.\n"
    	   "	-V, --version   Version del programa.\n"
           "Examples:\n"
    	   "	tp2 --D1=16384,2,64\n");
}

void imprime_version(){
	printf("Version [66.20] Organizacion de Computadoras\n"
		   "Segundo Cuatrimestre 2009\n");
}

void replaceText(string &word, const string &toReplace, const string &replaceBy)
{

	string::size_type posToRepleace = word.find(toReplace);
	while(posToRepleace != string::npos)
	{
		string tmpWord = word;
		if (posToRepleace > 0)
		{
			word = tmpWord.substr(0, posToRepleace);
			word += replaceBy;
			word += tmpWord.substr(posToRepleace + toReplace.size(), tmpWord.size() - 1);
		}
		else
		{
			word = replaceBy;
			word += tmpWord.substr(posToRepleace + toReplace.size(), tmpWord.size() - 1);
		}
		posToRepleace = word.find(toReplace);
	}
}

string intToString( int entero )
{
    std::stringstream cadena("");
    cadena << entero;
    return cadena.str();
}

void parsearDatos(const string &funcion, long int &dr, long int &dw, long int &d1mr, long int &d1mw)
{
	string grep("grep " + funcion + " " + FILE_OUTPUT_CGANNOTATE + " > " + FILE_OUTPUT_GREP);
	system(grep.c_str());
	std::ifstream fileGrep;
	fileGrep.open(FILE_OUTPUT_GREP);
	if (!fileGrep.good())
	{
		std::cerr << "No se pudo parsear la salida del cachegrind\n" << std::endl;
		return;
	}
	char buffer[SIZE_BUFFER];
	memset(buffer, '\0',SIZE_BUFFER);
	fileGrep.getline(buffer, SIZE_BUFFER);
	if(strlen(buffer)==0)
	{
		fileGrep.close();
		std::cerr << "No se pudo parsear la salida del cachegrind\n" << std::endl;
	}
	string word(buffer);
	int posDesde = 0, posHasta = 0;
	posDesde = word.find_first_not_of(" ", posDesde);
	posHasta = word.find(" ", posDesde);
	string strDr = word.substr(posDesde, posHasta-posDesde);
	replaceText(strDr, ",", "");
	dr = atol(strDr.c_str());

	posDesde = word.find_first_not_of(" ", posHasta);
	posHasta = word.find(" ", posDesde);
	string strDw = word.substr(posDesde, posHasta-posDesde);
	replaceText(strDw, ",", "");
	dw = atol(strDw.c_str());

	posDesde = word.find_first_not_of(" ", posHasta);
	posDesde = word.find(" ", posDesde);
	string strD1mr = word.substr(posDesde, posHasta-posDesde);
	replaceText(strD1mr, ",", "");
	d1mr = atol(strD1mr.c_str());

	posDesde = word.find_first_not_of(" ", posHasta);
	posDesde = word.find(" ", posDesde);
	string strD1mw = word.substr(posDesde, posHasta-posDesde);
	replaceText(strD1mw, ",", "");
	d1mw = atol(strD1mw.c_str());
	fileGrep.close();
}

int tamanioBloque(char *datosCache)
{
	string cachegrind(CACHEGRIND);
	if(datosCache != NULL)
		cachegrind.append(datosCache);
	cachegrind.append(" ./");
	cachegrind.append(TAMANIO_BLOQUE);
	system(cachegrind.c_str());

	string cgannotate(CG_ANNOTATE);
	cgannotate.append(TAMANIO_BLOQUE);
	cgannotate.append(".cpp");
	cgannotate.append(" > ");
	cgannotate.append(FILE_OUTPUT_CGANNOTATE);
	system(cgannotate.c_str());

	long int dr=0, dw=0, d1mr=0, d1mw=0;
	string fileFuente(TAMANIO_BLOQUE);
	fileFuente.append(".cpp:");
	fileFuente.append(TAMANIO_BLOQUE);
	parsearDatos(fileFuente, dr, dw, d1mr, d1mw);
	int sizeBloque = 0;
	if(dw>0  && d1mw>0)
		sizeBloque = dw/d1mw;
	return sizeBloque;
}

int tamanioCache(char *datosCache, int tamanioBloque)
{
	int n = 128;
	long int dr=0, dw=0, d1mr=0, d1mw=0;
	while(d1mw <= n)
	{
		n = n*2;
		string cachegrind(CACHEGRIND);
		if(datosCache != NULL)
			cachegrind.append(datosCache);
		cachegrind.append(" ./");
		cachegrind.append(TAMANIO_CACHE);
		cachegrind.append(" " + intToString(tamanioBloque) + " " + intToString(n));
		system(cachegrind.c_str());

		string cgannotate(CG_ANNOTATE);
		cgannotate.append(TAMANIO_CACHE);
		cgannotate.append(".cpp");
		cgannotate.append(" > ");
		cgannotate.append(FILE_OUTPUT_CGANNOTATE);
		system(cgannotate.c_str());

		string fileFuente(TAMANIO_CACHE);
		fileFuente.append(".cpp:");
		fileFuente.append(TAMANIO_CACHE);
		parsearDatos(fileFuente, dr, dw, d1mr, d1mw);
	}
	return (n/2 * tamanioBloque);
}

int cantidadVias(char *datosCache, int sizeCache, int sizeBloque)
{
	int n = 1;
	long int dr=0, dw=0, d1mr=0, d1mw=0;
	while(d1mw == 0)
	{
		string cachegrind(CACHEGRIND);
		if(datosCache != NULL)
			cachegrind.append(datosCache);
		cachegrind.append(" ./");
		cachegrind.append(CANT_VIAS);
		cachegrind.append(" " + intToString(n) + " " + intToString(sizeCache) + " " + intToString(sizeBloque));
		system(cachegrind.c_str());

		string cgannotate(CG_ANNOTATE);
		cgannotate.append(CANT_VIAS);
		cgannotate.append(".cpp");
		cgannotate.append(" > ");
		cgannotate.append(FILE_OUTPUT_CGANNOTATE);
		system(cgannotate.c_str());

		string fileFuente("'vector\\[j\\]\\[0\\]'");
		parsearDatos(fileFuente, dr, dw, d1mr, d1mw);
		n = n*2;
	}
	return (n/4);
}

int main(int argc, char* argv[])
{

	int siguiente_opcion = 0;

	/* Una cadena que lista las opciones cortas validas */
	const char* const op_cortas = "hVd:" ;

	/* Una estructura de varios arrays describiendo los valores largos */
	const struct option op_largas[] =
	{
			{ "help",         0,  NULL,   'h'},
			{ "version",       0,  NULL,   'V'},
			{ "D1",       1,  NULL,   'd'},
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

			case 'd' : /* --D1 */
				break;

			case '?' : /* opcion no valida */
				imprime_uso(stdout);
				exit(EXIT_SUCCESS);

			case -1 : /* No hay mas opciones */
				break;

			default : /* Algo mas? No esperado. Abortamos */
				abort();
			}
	}


	int sizeBloque = 0, sizeCache = 0, vias = 0;
	char *datosCache = NULL;
	if(argc > 1)
		datosCache = argv[1];
	sizeBloque = tamanioBloque(datosCache);
	sizeCache = tamanioCache(datosCache, sizeBloque);
	vias = cantidadVias(datosCache, sizeCache, sizeBloque);
	remove(FILE_OUTPUT_VALGRIND);
	remove(FILE_OUTPUT_CACHEGRIND);
	remove(FILE_OUTPUT_CGANNOTATE);
	remove(FILE_OUTPUT_GREP);
	std::cout << "Cache de datos L1:" << std::endl;
	std::cout << "#Vias: " << vias << " Vias" << std::endl;
	std::cout << "Tamaño: " << sizeCache << " Bytes"<< std::endl;
	std::cout << "Tamaño de bloque: " << sizeBloque << " Bytes"<< std::endl;

	return 0;
}
