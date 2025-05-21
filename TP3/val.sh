#!/bin/bash

# Compile o código com make
make all

# Diretório onde estão as entradas e saídas esperadas
entrada_dir="./entrada"
saida_esperada_dir="./saidas"

# Nome do executável do seu programa
programa="./bin/tp3.out"

# Verifica se um argumento foi fornecido na linha de comando
if [ $# -ne 1 ]; then
    echo "Uso: $0 <caso_de_teste>"
    exit 1
fi

caso_de_teste="$1"  # Obtém o caso de teste a partir do argumento

# Verifica se o caso de teste existe
if [ ! -f "$entrada_dir/$caso_de_teste" ]; then
    echo "Caso de teste '$caso_de_teste' não encontrado em '$entrada_dir'."
    exit 1
fi

entrada="$entrada_dir/$caso_de_teste"
saida_esperada="$saida_esperada_dir/$caso_de_teste"

# Executa o programa com o caso de teste especificado e redireciona a saída para um arquivo temporário
./bin/tp3.out < "$entrada" > output.tmp

# Imprime o output gerado pelo programa
echo "Output gerado pelo programa:"
cat "output.tmp"

# Compara a saída gerada com a saída esperada
if diff -q output.tmp "$saida_esperada"; then
    echo "Caso $caso_de_teste: SUCESSO"
else
    echo "Caso $caso_de_teste: FALHA"
fi

# Execute o Valgrind para verificar erros de memória no caso de teste selecionado
valgrind --tool=memcheck --leak-check=yes --track-origins=yes --show-leak-kinds=all --verbose -s ./bin/tp3.out < "$entrada"

# Remove o arquivo temporário
rm output.tmp
