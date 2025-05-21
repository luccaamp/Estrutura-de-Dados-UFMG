#ifndef PILHA_H
#define PILHA_H

#include <iostream>

struct Node{
    char dado;
    Node* prox;
};

class Pilha{
    private:
        unsigned int TAMANHO_MAXIMO = 1000000;  
        unsigned int _tamanho;
        Node* _topo;
    public:
        /*
        * @brief Construtor
        */
        Pilha();

        /*
        * @brief Destrutor
        */
        ~Pilha();

        /*
        * @brief Pega o tamanho
        */
        int get_tamanho() const;

        /*
        * @brief Tira ultimo elemento
        */
        void pop();

        /*
        * @brief Insere elemento no final da pilha
        */ 
        void insert(char c);

        /*
        * @brief Verifica estado da pilha
        */
        bool isEmpty();

        /*
        * @brief Imprime a pilha
        */
        void print() const;

        /*
        * @brief Retorna e imprime a pilha (para usar em teste case)
        */
        std::string imprimir() const;

        /*
        * @brief Retorna topo da pilha
        */
        char get_topo();
};

#endif