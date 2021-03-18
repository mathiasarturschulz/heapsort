#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<assert.h>
#include<omp.h>

#define NUM_REP 100

void heap_sort_serial(int *vet, int N);
void cria_heap_serial(int *vetor, int i, int f);

void heap_sort_paralelo(int *vet, int N, int NUM_THREADS);
void cria_heap_paralelo(int *vetor, int i, int f);

int main()
{
	int *vetor;
    int NUM_THREADS = 2;

    // define se os vetores serão aleatórios (1) ou inversos (0)
    int aleatorio = 0;

    // define o tamanho do vetor
    int tamanho_vetor = 10000;
    // int tamanho_vetor = 100000;
    // int tamanho_vetor = 1000000;
    // int tamanho_vetor = 10000000;

    printf("\nOrdenação utilizando Heapsort serial e paralelo ");

    vetor = calloc(tamanho_vetor, sizeof(unsigned int));
    srand(time(NULL));

    for (int i = NUM_THREADS; i <= 256; i*=2) {
        NUM_THREADS = i;
        // printf("\n\nthread: %i", NUM_THREADS);

        // Gera o vetor a ser ordenado (Aleatorio ou Inverso)
        if (aleatorio) {
            for (int i  = 0; i < tamanho_vetor; i++) {
                vetor[i] = rand() % (tamanho_vetor * 2);
            }
        } else {
            for (int i = tamanho_vetor-1; i >= 0; i--) {
                vetor[i] = tamanho_vetor - i;
            }
        }
        // Apresenta o vetor gerado
        // for (int i  = 0; i < tamanho_vetor; i++) {
        //     printf(" | %i", vetor[i]);
        // }
        // printf(" | \n");

        //
        //
        // HEAPSORT - SERIAL

        // Inicia a contagem do tempo de execução
        clock_t tempo_uso = clock();

        // Realiza a chamada do algoritmo de ordenação sequencial
        heap_sort_serial(vetor, tamanho_vetor);

        // Obtem o tempo final, após o termino da ordenação do vetor
        tempo_uso = clock() - tempo_uso;

        // Realiza o calculo do tempo de execução do algoritmo em segundos
        double tempo_exec_serial = ((double) tempo_uso) / CLOCKS_PER_SEC;
        // printf("\nHeapsort serial: %g ", tempo_exec_serial);

        //
        //
        // HEAPSORT - PARALELO

        // Coleta o tempo inicial da execução do algoritmo
        double tempo_inicial = omp_get_wtime();

        // Realiza a chamada do algoritmo de ordenação paralelizado
        heap_sort_paralelo(vetor, tamanho_vetor, NUM_THREADS);

        // Coleta o tempo inicial da execução do algoritmo
        double tempo_final = omp_get_wtime();

        // Realiza o calculo do tempo total de execução do algoritmo em segundos
        double tempo_total_paralelo = tempo_final - tempo_inicial;
        // printf("\nHeapsort paralelo: %g ", tempo_total_paralelo);

        // speedup = tempo de execução do algoritmo serial / tempo de execução do algoritmo paralelo
        double speedup = tempo_exec_serial / tempo_total_paralelo;
        printf("\n%f", speedup);
    }

    printf("\nTamanho do Vetor = %d\n", tamanho_vetor);
}

// Realiza a ordenação do vetor através do algoritmo Heapsort
void heap_sort_serial(int *vet, int N)
{
	int i, aux;

	// Primeiro crio o vetor heap a partir dos meus dados, pegando
	// o vetor do meio pra frente e tranformando-o em um heap
	for ( i = (N -1)/2; i >= 0; i--) {
		cria_heap_serial(vet, i, N-1);
	}

	// Pega o maior maior elemento da heap, que se encontra no topo da arvore,
	// e coloca na ultima posição do vetor em seguida reestrutura toda a heap,
	// sem considerar a ultima posição do vetor e realiza todo o processo
	// novamente até que o vetor esteja ordenado
	for ( i = N-1; i >= 1; i--) {
		aux = vet[0];
		vet[0] = vet[i];
		vet[i] = aux;

		cria_heap_serial(vet, 0, i-1);
	}
}

// Transforma um dado vetor em um vetor heap
void cria_heap_serial(int *vet, int i, int f)
{
	// Armazena a primeira posição do vetor, que é considerado o nó pai
	int aux = vet[i];
	// Calcula o primeiro filho e armazena na variavel j
	int j = i * 2 + 1;

	// Verifica se o fiho é menor ou igual a ultima posição do vetor
	while (j <= f) {
		if (j < f) {
			// Compara qual o maior filho, do pai armazenado na
			// variavel aux, e armazena na variavel j o maior
			if (vet[j] < vet[j+1]) {
				j = j + 1;
			}
		}

		// Ve se o filho na posição vet[j], é maior que o pai, caso for,
		// tranforma o filho no pai, e calcula seu próximo filho,
		// senão encerra o j para sair do laço While
		if ( aux < vet[j] ) {
			vet[i] = vet[j];
			i = j;
			j = 2 * i + 1;
		} else {
			j = f + 1;
		}
	}

	// No fim o antigo pai, ocupa o lugar do último filho analisado
	vet[i] = aux;
}

// Realiza o processo de ordenação de maneira paralelizada
void heap_sort_paralelo(int *vet, int N, int NUM_THREADS)
{
	#pragma omp parallel num_threads(NUM_THREADS) shared(vet, N)
	{
		int i, aux;

		// Primeiro cria-se o vetor heap a partir dos dados, pegando
		// o vetor do meio pra frente e tranformando-o em um heap
		for ( i = (N -1)/2; i >= 0; i--) {
			cria_heap_paralelo(vet, i, N-1);
		}

		// Pega o maior maior elemento da heap, que se encontra no topo da arvore,
		// e coloca na ultima posição do vetor em seguida reestrutura toda a heap,
		// sem considerar a ultima posição do vetor e realiza todo o processo
		// novamente até que o vetor esteja ordenado
		for ( i = N-1; i >= 1; i--) {
			aux = vet[0];
			vet[0] = vet[i];
			vet[i] = aux;

			cria_heap_paralelo(vet, 0, i-1);
		}
	}
}

// Transforma o vetor informado em um vetor heap
void cria_heap_paralelo(int *vet, int i, int f)
{
	int aux = vet[i];
	int j = i * 2 + 1;

	while (j <= f) {
		if (vet[j] < vet[j+1]) {
			j = j + 1;
		}

		if ( aux < vet[j] ) {
			vet[i] = vet[j];
			i = j;
			j = 2 * i + 1;
		} else {
			j = f + 1;
		}
	}

	vet[i] = aux;
}
