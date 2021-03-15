#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <omp.h>

#define NUM_THREADS 64
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
      printf("\n ORDENACAO USANDO HEAPSORT PARALELO");
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
				
				//Coleta o tempo inicial da execução do algoritmo
				double tempo_inicial = omp_get_wtime();

				//Realiza a chamada do algoritmo de ordenação paralelizado
				heap_sort(vetor, tamanho_vetor);
				
				//Coleta o tempo inicial da execução do algoritmo
				double tempo_final = omp_get_wtime();
			
				//Realiza o calculo do tempo total de execução do algoritmo em segundos
				double tempo_total = tempo_final - tempo_inicial;
				printf("Heapsorte paralelo executado em %g segundos\n", tempo_total);
				
				//Realiza a soma do tempo de execução total do algoritmo
				tempo_medio += tempo_total;
			}

			//Calcula o tempo médio de execução em relação ao número de repetições
			tempo_medio /= NUM_REP;

			printf("\nTamanho do Vetor = %d\n", tamanho_vetor);
			printf("\nNumero de Threads = %d\n", NUM_THREADS);
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

//Realiza o processo de ordenação de maneira paralelizada
void heap_sort(int *vet, int N)
{
	#pragma omp parallel num_threads(NUM_THREADS) shared(vet, N)
	{
		int i, aux;
		
		//Primeiro cria-se o vetor heap a partir dos dados, pegando 
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
}

//Transforma o vetor informado em um vetor heap
void cria_heap(int *vet, int i, int f)
{
	int aux = vet[i];
	int j = i * 2 + 1;
	
	while (j <= f)
	{
		if (vet[j] < vet[j+1])
		{
			j = j + 1;
		}
		
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

	vet[i] = aux;	
}