#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define NUM_REP 100

void heap_sort(int *vet, int N);
void cria_heap(int *vetor, int i, int f);

int main()
{
   int *vetor, menu, tamanho_vetor, sair = 0, aleatorio = 0;
   double tempo_medio = 0.0;
   
   while (sair == 0)
   {
      printf("\n--------------------------------------\n");
      printf("\n ORDENACAO USANDO HEAPSORT SERIAL");
	  printf("\n 1-GERAR NOVO VETOR");
	  printf("\n 2-SAIR");
	  printf("\n >>>>>");
      printf("\n--------------------------------------\n");
      scanf("%d",&menu);
      system("cls");

      switch(menu)
	  {
		  case 1:
			printf("\nINSIRA O TAMANHO DO VETOR:\n");
            scanf("%d",&tamanho_vetor);
		  
            vetor = calloc(tamanho_vetor, sizeof(unsigned int));
			srand(time(NULL));

			for (int j = 0; j < NUM_REP; j++)
			{
				//Gera o vetor a ser ordenado (Aleatorio ou Inverso)
				if (aleatorio)
				{
				   for (int i  = 0; i < tamanho_vetor; i++)
				   {
					   vetor[i] = rand() % tamanho_vetor;
				   }
				}
				else
				{
				   for (int i = tamanho_vetor-1; i >= 0; i--)
				   {
					   vetor[i] = tamanho_vetor - i;
				   }
				}
				 
				//Inicia a contagem do tempo de execução
				clock_t tempo_uso = clock();

				//Realiza a chamada do algoritmo de ordenação sequencial				
				heap_sort(vetor, tamanho_vetor);

				//Obtem o tempo final, após o termino da ordenação do vetor
				tempo_uso = clock() - tempo_uso;
								
				//Realiza o calculo do tempo de execução do algoritmo em segundos
				double tempo_exec = ((double) tempo_uso) / CLOCKS_PER_SEC;
				printf("Heapsort serial executado em %g segundos\n", tempo_exec);

				//Realiza a soma do tempo de execução total do algoritmo
				tempo_medio += tempo_exec;
			}
			
			//Calcula o tempo médio de execução em relação ao número de repetições
			tempo_medio /= NUM_REP;

			printf("\nTamanho do Vetor = %d\n", tamanho_vetor);
			printf("\nTempo medio = %g segundos\n", tempo_medio);
                    
            system("pause");
            system("cls");
         break;
         
         case 2:
            printf("\nPrograma Finalizado!");
            sair=1;
            
         break;
            
      }
   }
}

//Realiza a ordenação do vetor através do algoritmo Heapsort
void heap_sort(int *vet, int N)
{
	int i, aux;
	
	//Primeiro crio o vetor heap a partir dos meus dados, pegando 
	//o vetor do meio pra frente e tranformando-o em um heap
	for ( i = (N -1)/2; i >= 0; i--)
	{
		cria_heap(vet, i, N-1);
	}
	
	//Pega o maior maior elemento da heap, que se encontra no topo da arvore, 
	//e coloca na ultima posição do vetor em seguida reestrutura toda a heap,
	//sem considerar a ultima posição do vetor e realiza todo o processo 
	//novamente até que o vetor esteja ordenado
	for ( i = N-1; i >= 1; i--)
	{
		aux = vet[0];
		vet[0] = vet[i];
		vet[i] = aux;
		
		cria_heap(vet, 0, i-1);
	}
}

//Transforma um dado vetor em um vetor heap
void cria_heap(int *vet, int i, int f)
{
	//Armazena a primeira posição do vetor, que é considerado o nó pai
	int aux = vet[i];
	//Calcula o primeiro filho e armazena na variavel j
	int j = i * 2 + 1;

	//Verifica se o fiho é menor ou igual a ultima posição do vetor
	while (j <= f)
	{
		if (j < f)
		{
			//Compara qual o maior filho, do pai armazenado na 
			//variavel aux, e armazena na variavel j o maior
			if (vet[j] < vet[j+1])
			{
				j = j + 1;
			}
		}
		
		//Ve se o filho na posição vet[j], é maior que o pai, caso for,
		//tranforma o filho no pai, e calcula seu próximo filho, 
		//senão encerra o j para sair do laço While
		if ( aux < vet[j] )
		{
			vet[i] = vet[j];
			i = j;
			j = 2 * i + 1;
		}
		else
		{
			j = f + 1;
		}
	}

	//No fim o antigo pai, ocupa o lugar do último filho analisado
	vet[i] = aux;
}