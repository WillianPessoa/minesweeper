typedef struct _TEMPO{
	int segundos;
	int minutos;
	int horas;
}TEMPO;

time_t tempoInicial(void)
{
	time_t tempo_i;  //cria uma variavel do tipo time_t;
	tempo_i = time(NULL); //alimenta a variavel tempo_i com Null para poder a contar;
	return tempo_i; //retorna o valor de tempo_i;
}

void tempoFinal(time_t t1) //como as funcoes de tempo vao estar seguidas, precisa-se guardar o tempo inicial e juntar com
{	//o tempo final, para poder pegar a diferenca. a funcao tempoFinal recebe uma variavel t1 do tipo time_t ;
	int segundos,aux1,aux2; 
	TEMPO tempo_total;
	time_t tempo_f;			//cria uma variavel tempo_f do tipo time_t;
	tempo_f = time(NULL);
	segundos = difftime(tempo_f,t1); //diferenca de tempo. Retorna um tempo em segundos do tipo int;
	if (segundos>60) //verifica se o jogo possui mais de um minuto de duracao;
	{
		aux1 = (int)segundos/60; //parte inteira da divisao de segundos por 60 (minutos);
		tempo_total.segundos = segundos%60; //resto da divisao de segundos por 60;
		tempo_total.minutos = aux1; //acrescenta 1 minuto;
		if (tempo_total.minutos > 60) //verifica se o jogo possui mais de uma hora de duracao;
		{
			aux2 = (int)tempo_total.minutos / 60; //parte inteira da divisao de minutos por 60 (horas);
			tempo_total.minutos %= 60; //resto da divisao por 60;
			tempo_total.horas = aux2;
		}
		else tempo_total.horas = 0; //caso a duracao nao tenha mais que 1 hora;
			
	}
	else //caso nao precise converter os segundos para minutos;
	{
		tempo_total.segundos = segundos;
		tempo_total.minutos = 0;
		tempo_total.horas = 0;
	}	
	printf("O tempo de duracao total foi de %2d:%2d:%2d\n",tempo_total.horas,tempo_total.minutos,tempo_total.segundos);
}