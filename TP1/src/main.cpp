#include "../include/Utils.hpp"

#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    bool printar = false;

    char option;
    std::string formula;
    std::string valores;

    bool achar_valor = false;
    bool validade = false;

    // Usando getopt para analisar as opções de linha de comando
    while ((option = getopt(argc, argv, "as")) != -1) {
        switch (option) {
            case 'a':
                achar_valor = true;
                break;
            case 's':
                validade = true;
                break;
            default:
                std::cerr << "Uso: " << argv[0] << " [-a | -s] fórmula lógica" << std::endl;
                return 1;
        }
    }

    // Verifique se foi pedido mais de um problema
    if (achar_valor && validade) {
        std::cerr << "Você deve especificar apenas uma opção de problema." << std::endl;
        std::cerr << "-a -> achar valor da expressão" << std::endl;
        std::cerr << "-s -> satisfabilidade da expressão" << std::endl;
        return 1;
    }

    // Verifique se tem apenas 2 strings depois da opção               
    if(optind + 2 != argc){
        std::cerr << "opção de problema: " << std::endl;
        std::cerr << "-a -> achar valor da expressão" << std::endl;
        std::cerr << "-s -> satisfabilidade da expressão" << std::endl;
        std::cerr << "Uso: " << argv[0] << " [-a | -s] formula_logica" << std::endl;
    }

    // Armazenar fórmula lógica e valores das variáveis
    formula = argv[optind];  
    valores = argv[optind+1]; 

    if (formula.size() > 1e6) {
        std::cerr << "Erro: A fórmula lógica excede o tamanho máximo permitido." << std::endl;
        return 1;
    }

    if (valores.size() > 100) {
        std::cerr << "Erro: A string de valores excede o tamanho máximo permitido." << std::endl;
        return 1;
    }
    
    if(printar == true){
        std::cout << "opção = " << argv[1] << std::endl;
        std::cout << "fórmula lógica = " << formula << std::endl;
        std::cout << "valores = " << valores << std::endl;
    }
    
    if(achar_valor == true){
        if(printar == true){
            // Remover espaços em branco
            std::string formula_corrigida = tirar_espacos(formula);
            std::cout << "fórmula sem espaços em branco = " << tirar_espacos(formula) << std::endl;

            // Substituir valoração para as variáveis presentes na fórmula
            std::string formula_substituida = substituir_valores(formula_corrigida, valores);
            std::cout << "substituindo valores = " << formula_substituida << std::endl;

            // Pós-fixado 
            std::string resultado = pos_fixado(formula_substituida);
            std::cout << "pos_fixado = " << resultado << std::endl;
        }

        // Valor
        std::cout << avaliar(formula, valores) << std::endl;
    }
    else if(validade == true){
        satisfaz(formula, valores);
    }
    else {
        std::cerr << "Opcao invalida: " << argv[1] << std::endl;
    }

    return 0;
};