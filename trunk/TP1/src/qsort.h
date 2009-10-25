#ifndef __QSORT_H__
#define __QSORT_H__

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

void quicksort(char** izq, char** der, int num)
{
	if(der<izq) return;
	char* pivot=*izq;
	char** ult=der;
	char** pri=izq;

	while(pri<ult)
	{
		while(pri<ult+1 && !esMayor(*pri,pivot,num))
			pri++;
		while(ult>pri-1 && esMayor(*ult,pivot,num))
			ult--;
		if(pri<ult)
			swap(pri,ult);
	}
	swap(izq,ult);
//	int* puntUlt = ult - 1;
	quicksort(izq,ult -1,num);
//	puntUlt = ult + 1;
	quicksort(ult + 1,der,num);
}



//int main(){
//	int N = 7;
//	char* array[N];
//
//	int i = 0;
//	array[i++] = "1";
//	array[i++] = "7";
//	array[i++] = "8";
//	array[i++] = "256";
//	array[i++] = "5";
//	array[i++] = "4";
//	array[i++] = "10";
//
//	char** finArray = (array + N - 1);
//	quicksort(array, finArray, 0);
//
//	printf("------------ Corriendo ordenado alfab�ticamente--------------  \n");
//
//	for (i = 0; i < N; i++){
//		printf("%s \n", array[i]);
//	}
//
//	printf("\n------------ Corriendo ordenado num�ricamente--------------  \n");
//
//	quicksort(array, finArray, 1);
//
//	for (i = 0; i < N; i++){
//		printf("%s \n", array[i]);
//	}
//
//	return 0;
//}


#endif
