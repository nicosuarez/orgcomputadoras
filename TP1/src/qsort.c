#include "qsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void swap(char** a, char** b)
{
	char* temp=*a;
	*a=*b;
	*b=temp;
}

int esMayor (char* x, char* y, int num){
	if (num){
		return atoi(x) > atoi(y);
	} else {
		return strcmp(x , y) > 0;
	}
}

void quickSort(char** izq, char** der, int num)
{
    char *pivote;
    char **inf, **sup;
    int comp;
    if(izq >= der)
        return;
    pivote = *der;
    sup = der;
    inf = izq-1;
    while(1)
    {
        do
        {
            inf++;
            comp = esMayor(pivote, *inf, num);
        }while(comp>0);

        do
        {
            sup--;
            comp = esMayor(*sup, pivote, num);
            if(sup==izq)
                break;
        }while(comp>0);
        if(inf >= sup)
            break;
        swap(inf, sup);
    }

    swap(inf, der);

    if (inf == sup){
    	inf++;
    }

    quickSort(izq, sup, num);
    quickSort(inf, der, num);
}
