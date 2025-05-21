#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>

struct Tupla {
    int chave; // "nome" do vértice
    int cor;
};

class Heap {
    private:
        int tamanho;
        Tupla* vertice;
    public:
        /* 
         * @brief Construtor do Heap. 
         */
        Heap(int size);

        /* 
         * @brief Destrutor do Heap.
         */
        ~Heap();

        /* 
         * @brief Verifica se existe as condições para troca
         * dos vértices.
         */
        bool Condicao(Tupla t1, Tupla t2);

        /*
        * @brief Troca a Tupla t1 pela Tupla t2 da lista.
        */
        void Troca(Tupla& t1, Tupla& t2);

        /* 
        * @brief Retorna se o heap está vazio. 1 -> está , 0 -> não está.
        */
        bool Vazio();

        /* 
        * @brief Retorna a posição do ancestral de uma Tupla específica no Heap. 
        */
        int GetAncestral(int position);

        /* 
        * @brief Retorna a posição do sucessor esquerdo de uma Tupla específica no Heap.
        */
        int GetSucessorEsq(int position);

        /* 
        * @brief Retorna a posição do sucessor direito de uma Tupla específica no Heap.
        */
        int GetSucessorDir(int position);

        /* 
        * @brief Insere um elemento no Heap e reorganiza a estrutura para manter a propriedade do Heap. 
        */
        void Inserir(Tupla t);

        /* 
        * @brief Remove o elemento de maior prioridade (raiz) do Heap e reorganiza a estrutura para mantê-lo um Heap válido.
        */
        Tupla Remover();
};

#endif  