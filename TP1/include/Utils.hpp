#ifndef UTILS_H
#define UTILS_H

#include "../include/Pilha.hpp"
#include "../include/Vector.hpp"

#include <iostream>
#include <string>
#include <getopt.h>
#include <stdlib.h>
#include <sstream>

inline std::string tirar_espacos(std::string formula){
    std::string saida;
    for (char c : formula) {
        if (c != ' ') {
            saida += c;
        }
    }
    return saida;
};

inline std::string substituir_valores(std::string formula, std::string valores){
    valores = tirar_espacos(valores);

    // Valoração inválida 
    for(char c : valores){
        if (c != '0' && c != '1') {
            throw std::invalid_argument("String de valores contém caracteres inválidos (esperados '0' ou '1')");
        }
    }
    
    std::string saida;
    for (std::size_t i=0; i < formula.length(); i++) {
        char c = formula[i];

        // Verifica se o caractere é um número 
        if (isdigit(c) != 0) {
            int indice = c - '0';

            // Verifica se o próximo também é um número
            if ((i + 1 < formula.length()) && isdigit(formula[i + 1])) {
                // Se o próximo caractere também for um dígito, considera os dois com uma única variável
                indice = indice * 10 + (formula[i + 1] - '0');
                i++;  //  Pular o próximo dígito
            } 
            saida += valores[indice];
        }
        else{
            saida += c;
        }
    }
    return saida;
};


// Ordem de precedência dos operadores lógicos
inline int ordem(char c){
    if (c == '~')
        return 3;
    else if (c == '&')
        return 2;
    else if (c == '|')
        return 1;
    else
        return -1;
}

// Expressão Infixa para Postfixa
inline std::string pos_fixado(std::string formula){
    Pilha p;
    std:: string result;

    for(char c : formula){
        // Se o caractere for um número acrescenta na string
        if(isdigit(c) != 0){  
            result += c;
        }
        // Se o caractere for '(' acrescenta na pilha
        else if(c == '('){   
            p.insert(c);
        }
        else if(c == '~'){
            p.insert(c);
        }
        // Se o caractere for ')' encontra o '(' correspondente
        else if(c == ')'){   
            // Adiciona operadores na string até encontrar '(', remove operador da pilh
            while(p.get_topo() != '('){
                result += p.get_topo();  
                p.pop();                 
            }
            p.pop(); // Remove '(' correspondente da pilha
        }
        else{
            if(!p.isEmpty()){ 
                // Adiciona operadores restantes na string, remove operadores da pilha
                while((!p.isEmpty()) && (ordem(c) <= ordem(p.get_topo())) != 0){
                    result += p.get_topo();   
                    p.pop();                  
                }  
            }
            p.insert(c); // Insere o operador atual na pilha
        }  
    }

    // Adiciona operadores restantes na string, remove operadores da pilha
    while(!p.isEmpty()){
        result += p.get_topo(); 
        p.pop();    
    }
    return result;
};

inline bool valor_operacao_logica(char op, bool operacao1, bool operacao2){
    if (op == '&')
        return operacao1 && operacao2;
    else if (op == '|')
        return operacao1 || operacao2;
    else if (op == '~')
        return !operacao1;
    else
        throw std::invalid_argument("Operador inválido");
}

// Avaliação da expressão Postfixa
inline bool avaliar(std::string formula, std::string valores){
    formula = pos_fixado(substituir_valores(tirar_espacos(formula), valores));
    Pilha p;

    for (char c : formula){

        if (c == '0' || c == '1') {
            p.insert(c);
        } 
        
        else if (c == '&' || c == '|' || c == '~') {
            if (c == '~') {
                if (p.isEmpty()) {
                    throw std::invalid_argument("Operador NOT sem operando");
                }
                char operacao = p.get_topo();
                p.pop();
                p.insert(valor_operacao_logica(c, operacao == '0' ? false : true, false) ? '1' : '0');
            } 
            else {
                if (p.isEmpty()) {
                    throw std::invalid_argument("Operador " + std::string(1, c) + " sem operando esquerdo");
                }

                char operacao2 = p.get_topo();
                p.pop();

                if (p.isEmpty()) {
                    throw std::invalid_argument("Operador " + std::string(1, c) + " sem operando direito");
                }

                char operacao1 = p.get_topo();
                p.pop();
                p.insert(valor_operacao_logica(c, operacao1 == '0' ? false : true, operacao2 == '0' ? false : true) ? '1' : '0');
            }
        } 
        
        else {
            throw std::invalid_argument("Caractere inválido na expressão lógica: " + std::string(1, c));
        }
    }
    
    if (p.get_tamanho() != 1) {
        std::cout << "tamanho = " << p.get_tamanho() << std::endl;
        throw std::invalid_argument("Expressão lógica mal formada");
    }

    return p.get_topo() == '0' ? false : true;
}

/*
 *
 *  FUNÇÕES PARA RESOLVER SATISFABILIDADE
 *
 */
 
// gerar todas as possiveis combinações de valores com os quantificadores 
void gerar_combinacoes(Vector &combinations, std::string &str, std::string::size_type index) {
    if (index == str.length()) {
        // Inicializa a flag como 0
        Tupla nova_tupla{str, 0}; // Precisa passar o null ????
        combinations.insere_fim(nova_tupla); 
        return;
    }

    if (str[index] == 'a' || str[index] == 'e') {
        str[index] = '0';
        gerar_combinacoes(combinations, str, index + 1);

        str[index] = '1';
        gerar_combinacoes(combinations, str, index + 1);

        // Restaura o caractere original para mais combinações
        str[index] = (str[index] == 'a') ? 'a' : 'e';
    } else {
        gerar_combinacoes(combinations, str, index + 1);
    }
}

std::string comparar_str(std::string s1, std::string s2){
    std::string result;
    
    int size_str = s1.length();
    
    // result é igual a string que tem 'a'
    for(int i = 0; i < size_str; i++){
        if(s1[i] == 'a'){
            result = s1;
        }
        else if(s2[i] == 'a'){
            result = s2;
        }
        else{
            result = s1;
        }
    }
    
    int x=0;
    // se uma string tiver 'a' e a outra '1', então aquela posição vira 'a'
    for (int i = 0; i < size_str; i++) {
        if ((s1[i] == 'a' && s2[i] == '1') || (s2[i] == 'a' && s1[i] == '1')) {
            result[i] = 'a';
            x++;
            break;
        }
    }
    
    // se uma string tiver um caractere diferente da outra na mesma posição
    // então na string result aquele caractere vira 'a'
    if(x == 0){
        for(int i = 0; i < size_str; i++){
            if(s1[i] != s2[i]){
                result[i] = 'a';
            }
        }
    }

    return result;
    //std::cout << "String s1: " << s1 << std::endl;
    //std::cout << "String s2: " << s2 << std::endl;
    //std::cout << "Resultado: " << result << std::endl;
}

void satisfaz(const std::string& formula, const std::string& valoracao){ 
    std::string inputString = valoracao;

    // gerar todas as possiblidades
    Vector vetor;

    gerar_combinacoes(vetor, inputString, 0);

    //vetor.imprimir();

    for (int i = 0; i < vetor.get_tamanho(); i++) {
        Tupla& tupla = vetor.get_elemento_em(i);

        int output = avaliar(formula, tupla.combinacao);
        tupla.flag = output;
        
        //std::cout << "Combinação: " << tupla.combinacao << " Resultado: " << tupla.flag << std::endl;
    }

    // Avaliar opções
    int i=0;
    while(vetor.get_tamanho() > 0){
        if (vetor.get_flag_em(i) == 1 && vetor.get_flag_em(i+1) == 1){
            std::string nova_string = comparar_str(vetor.get_combinacao_em(i), vetor.get_combinacao_em(i+1));

            Tupla tupla{nova_string, 1}; // (nova_string, true)
            vetor.insere_posicao(tupla, i);

            vetor.remove_posicao(i+1);
            vetor.remove_posicao(i+1);
        }

        else if (vetor.get_flag_em(i) == 0 && vetor.get_flag_em(i+1) == 0) {
            Tupla tupla{"0", 0};
            vetor.insere_posicao(tupla, i);

            vetor.remove_posicao(i+1);
            vetor.remove_posicao(i+1);
        } 

        else if (vetor.get_flag_em(i) == 1 && vetor.get_flag_em(i+1) == 0) {
            Tupla tupla{vetor.get_combinacao_em(i), 1};
            vetor.insere_posicao(tupla, i);

            vetor.remove_posicao(i+1);
            vetor.remove_posicao(i+1);
        } 

        else if (vetor.get_flag_em(i) == 0 && vetor.get_flag_em(i+1) == 1) {
            Tupla tupla{vetor.get_combinacao_em(i+1), 1};
            vetor.insere_posicao(tupla, i);

            vetor.remove_posicao(i+1);
            vetor.remove_posicao(i+1);
        }

        //vetor.imprimir();

        i += 1;
        if (i >= vetor.get_tamanho()) {
            i = 0;
        }

        if(vetor.get_tamanho() == 1){
            break;
        }
    }

    std::cout << vetor.get_flag_em(0) << " " << vetor.get_combinacao_em(0) << std::endl;

    std::cout << std::endl;
}

#endif
