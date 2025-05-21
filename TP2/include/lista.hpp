#ifndef LISTA_HPP
#define LISTA_HPP

#include <string>

struct Node {
  int dados;
  Node *prox;
};

class ListaEncadeada {
  private:
    unsigned int _tamanho;
    Node *_inicio;
    Node *_fim;
  public:
    /* 
     * @brief Construtor da lista.
     */
    ListaEncadeada();

    /* 
     * @brief Destrutor da lista.
     */
    ~ListaEncadeada();

    /* 
     * @brief Retorna se a lista está vazia, 1 -> está , 0 -> não está.
     */
    bool esta_vazio();

    /* 
     * @brief Retorna o tamanho da lista. Sempre começa com zero.
     */
    unsigned int get_tamanho();

    /*
     * @brief Insere um item no fim da lista.
     */
    void insere_fim(int item);

    /*
     * @brief Insere um item em uma posição da lista.
     */
    void insere_posicao(int item, unsigned int posicao);
    
    /*
     * @brief Retorna o item da lista na posição dada.
     */
    int get_item_em(unsigned int pos);

    /*
     * @brief Remove o item da lista na posição dada.
     */
    void remove_posicao(unsigned int pos);

    /*
     * @brief Limpa a lista.
     */
    void remove_tudo();

    /*
     * @brief Printar a lista.
     */
    void imprimir();

    /*
     * @brief Verifica se existe o valor na lista.
     */
    bool contem(int valor);

    /*
     * @brief Retorna a lista como string. Usado pra comparar em test case.
     */
    std::string retornar_lista();
};

#endif
