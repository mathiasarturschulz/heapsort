# heapsort

Implementação do algoritmo de ordenação heapsort na versão sequencial e paralela

Escrever um ShortPaper (4 páginas) somente focando nos seguintes dados:

 - Apresentar a configuração do equipamento que vocês fizeram os testes;
 - Apresentar os tempos e gráficos;
 - Apresentar os cálculos de speedup (verificar nos artigos, caso não tenha pesquisar sobre speedup);

## Compilando e executando os arquivos

### Compilando o heapsort serial

`gcc src/serial.c -o bin/serial`

### Compilando o heapsort paralelo

`gcc src/parallel.c -o bin/parallel -fopenmp`

`-fopenmp` => Realiza a vinculação entre os arquivos compilados do projeto com a biblioteca omp
