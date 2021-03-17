# heapsort

Implementação do algoritmo de ordenação heapsort na versão sequencial e paralela

https://docs.google.com/document/d/1wMSbRwEOO3c-ChC4B-BmVJSOk6ZajsHD/edit

## Compilando os arquivos

### Compilando o heapsort serial

`gcc src/serial.c -o bin/serial`

### Compilando o heapsort paralelo

`gcc src/parallel.c -o bin/parallel -fopenmp`

`-fopenmp` => Realiza a vinculação entre os arquivos compilados do projeto com a biblioteca omp

## Executando os arquivos

### Executando o heapsort serial

`./bin/serial`

### Executando o heapsort paralelo

`./bin/parallel`

## Shell script para compilar e executar um arquivo a partir do nome informado

Exemplo:

`./exec.sh serial`

Ou:

`./exec.sh parallel`
