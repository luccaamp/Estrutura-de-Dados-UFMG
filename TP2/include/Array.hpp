#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "../include/heap.hpp"
#include <iostream>

struct Vertice {
    int chave; // identificação de um vértice, "nome" dele
    int cor;  
    Vertice *prox;
    
    // Adicionando um construtor para inicializar os membros
    Vertice() : chave(0), cor(0), prox(nullptr) {}
};

class Array {
  private:
    Vertice* _array;
    int _tamanho;
    int _capacidade;
  public:
    /* 
     * @brief Construtor do Array.
     */
    Array(int size);

    /* 
     * @brief Construtor do Array.
     */
    ~Array();

    /* 
     * @brief Retorna se o Array está vazio, 1 -> está , 0 -> não está.
     */
    bool esta_vazio();

    /* 
     * @brief Cria um novo vértice no Array.
     */
    void insert();

    /* 
     * @brief No vértice da chave, insere index na sua lista interna.  
     */
    void insert(int chave, int index);

    /* 
     * @brief Insere cor no vértice da chave.  
     */
    void insert_cor(int chave, int cor);

    /* 
     * @brief Insere a lista de vizinhos da chave/vértice.  
     */
    void inserir_vizinho(int chave, int vizinho);

    /*
     * @brief Limpa o Array.
     */
    void remover_tudo();

    /*
     * @brief Printa o Array. Mostrando Chave, Cor e Lista Interna.
     */
    void print();

    /*
     * @brief Printa somente as chaves (nomes) do Array.
     */
    void print_chaves();

    /*
     * @brief Retorna o tamanho fixo do Array.
     */    
    int get_tamanho_maximo();

    /*
     * @brief Retorna o tamanho atual do Array.
     */    
    int get_tamanho_atual();

    /*
     * @brief Troca o item da posição i pelo intem da posição
     * j, e vice-versa.
     */
    void trocar(int i, int j);

    // Algoritmos de Ordenação:

    void BubbleSort(); 

    void SelectionSort();

    void InsertionSort();

    void Quicksort();
    void Particao(int Esq, int Dir, int *i, int *j);
    void Ordena(int Esq, int Dir);

    void Mergesort();
    void Mergesort(int esq, int dir);
    void Merge(int esq, int meio, int dir);

    void Heapsort(); 
    void Constroi();
    void Refaz(int Esq, int Dir);

    void Meu_metodo_de_ordenacao();
};

#endif