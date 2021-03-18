#!/bin/bash

echo "Compilando e executando o arquivo main!"

gcc src/main.c -o bin/main

./bin/main

# echo "Compilando e executando o arquivo $1!"

# if [ $1 = "serial" ]
# then
#     echo "Serial"
#     gcc src/"$1".c -o bin/"$1"
#     ./bin/"$1"
# elif [ $1 = "paralelo" ]
# then
#     echo "Paralelo"
#     gcc src/$1.c -o bin/$1 -fopenmp
#     ./bin/"$1"
# else
#     echo "Nome de arquivo inválido"
# fi
