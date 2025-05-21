#!/bin/bash

# Executar make all
make all

# Loop para executar o código com todos os casos de teste
for file in ./entrada/*.txt; do
    echo "Running test case: $file"
    ./bin/tp3.out < "$file" >> tempo.txt
done

echo "Testes concluídos. Resultados salvos em tempo.txt."