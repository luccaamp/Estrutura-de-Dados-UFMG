#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../include/lista.hpp"
#include "../include/ListaAdjacencia.hpp"

struct Item {
    int Chave;
    int Cor; 
};

class Grafo{
    private:
        ListaAdjacencia vertices;
    public:
        /* 
         * @brief Construtor do Grafo. 
         */
        Grafo();

        /* 
         * @brief Destrutor do Grafo.
         */
        ~Grafo();

        /* 
         * @brief Cria um novo Node na lista de vértices.
         */
        void Insere_Vertice();

        /* 
         * @brief Insere aresta W na lista de vizinhos do vértice V.
         */
        void Insere_Aresta(int v, int w);

        /* 
         * @brief Insere Cor no vértice V.
         */
        void Insere_Cor(int v, int cor);

        /* 
         * @brief Retorna o tamanho da lista de vértices.
         */
        int Quantidade_Vertices();

        /* 
         * @brief Retorna a soma da quantidade de vizinhos de cada vértice
         * dividido por 2, pois é um grafo não direcionado.
         */
        int Quantidade_Arestas();

        /* 
         * @brief Menor número de arestas que saem de qualquer vértice no grafo.
         */
        int Grau_Minimo();

        /* 
         * @brief Maior número de arestas que saem de qualquer vértice no grafo.
         */
        int Grau_Maximo();

        /*  
         * @brief Imprime a lista de vértices.
         */
        void Imprime_Vizinhos(void);

        /*  
         * @brief Verifica se tem uma aresta entre cada par de vértices.
         */
        bool EhCompleto();

        /*  
         * @brief Verifica se existe o vértice j na lista de vizinhos do vértice i.
         */
        bool Existe_Aresta(int i, int j);

        /*  
         * @brief Verifica se é uma coloração gulosa: uma cor 
         * possui vizinhos com todas as cores menores que ela;
         * não existem vértices com cores iguais conectados.
         */
        bool EhColoracaoGulosa();

        /*  
         * @brief Printa os "nomes"/chaves dos vértices na lista de adjacencia.
         */
        void Printar_chaves();


        // Métodos de Ordenação:

        void OrdenarPorCorCrescente();

        void BubbleSort(); 

        void SelectionSort(); //NÃO ESTÁVEL

        void InsertionSort();

        void Quicksort(); //NÃO ESTÁVEL
        void Particao(int Esq, int Dir, int *i, int *j);
        void Ordena(int Esq, int Dir);

        void Mergesort();
        void Mergesort(int esq, int dir);
        void Merge(int esq, int meio, int dir);

        void Heapsort(); //NÃO ESTÁVEL
        void Constroi(Item *A, int n);
        void Refaz(int Esq, int Dir, Item *A);

        void Meu_metodo_de_ordenacao();
};

#endif