#include<stdio.h>
#include<time.h>
#include "tempo.h"
int main(void)
{
	time_t t1;
	t1 = tempoInicial();
	printf("Entre com alguma tecla para saber o tempo de execucao.\n");
	getchar();
	tempoFinal(t1);
	return 0;
}
