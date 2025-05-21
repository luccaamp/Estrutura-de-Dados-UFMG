#ifndef LISTA_ADJACENCIA_HPP
#define LISTA_ADJACENCIA_HPP

#include "../include/lista.hpp"

struct Node_Ajc {
  ListaEncadeada lista; // lista de vizinhos do vértice 
  int chave;            // identificação de um vértice, "nome" dele
  int cor;  
  Node_Ajc *prox;
};

class ListaAdjacencia {
  private:
    int _tamanho;
    Node_Ajc* _comeco;
    Node_Ajc* _final;
  public:
    /* 
     * @brief Construtor da ListaAdjacencia.
     */
    ListaAdjacencia();

    /* 
     * @brief Construtor da ListaAdjacencia.
     */
    ~ListaAdjacencia();

    /* 
     * @brief Retorna se a lista está vazia, 1 -> está , 0 -> não está.
     */
    bool esta_vazio();

    /* 
     * @brief Cria um novo Node na ListaAdjacencia.
     */
    void insert();

    /* 
     * @brief No node da chave, insere index na sua lista interna.  
     */
    void insert(int chave, int index);

    /* 
     * @brief Insere cor no Node da chave.  
     */
    void insert_cor(int chave, int cor);

    /*
     * @brief Limpa a lista.
     */
    void remover_tudo();

    /*
     * @brief Printa a lista. Mostrando Chave, Cor e Lista Interna.
     */
    void print();

    /*
     * @brief Printa somente as chaves (nomes) da lista.
     */
    void print_chaves();

    /*
     * @brief Retorna o tamanho da lista.
     */    
    int get_size();

    /*
     * @brief Retorna o primeiro Node da lista.
     */  
    Node_Ajc* get_primeiro_elemento();

    /*
     * @brief Retorna o último Node da lista.
     */  
    Node_Ajc* get_ultimo_elemento();

    /*
     * @brief Retorna o Node na posição índice da lista.
     */
    Node_Ajc* get_elemento_em(int indice);

    /*
     * @brief Troca o Node da chave1 pelo Node da chave2 da lista.
     */
    void trocar_nos(int chave1, int chave2);

    /*
     * @brief Troca o Node da posição i com o Node da posição j da lista.
     */
    void trocar_nos_das_posicoes(int i, int j);

    /*
     * @brief O Node da posição i recebe o Node NO
     */
    void recebe(int i, Node_Ajc* NO);
};

#endif