#ifndef SEGTREE_HPP
#define SEGTREE_HPP

#include <iostream>
#include <string>
#include <stdexcept>

struct Matriz {
  long long dado[2][2]; //matriz 2 por 2

  // Construtor para inicializar as posições
  Matriz(long long a, long long b, long long c, long long d);

  // Construtor para inicializar a matriz identidade
  Matriz();

  void print();

  std::string print_string();
};

class SegTree {
  private:
    Matriz* segTree;
    Matriz _identidade;  // Matriz identidade
    int _tamanho;
  public:
    /* 
     * @brief Construtor da SegTree.
     */
    SegTree(int n);

    /* 
     * @brief Destrutor da SegTree.
     */
    ~SegTree();

    /* 
     * @brief Cria a SegTree com todos os nodes possuindo as matrizes identidade 2 por 2.
     */
    void build(int posicao, int inicio, int fim);

    /* 
     * @brief Atualiza o node específico com a matriz dada
     */
    Matriz update(int indice, Matriz novaMatriz, int posicao, int inicio, int fim); 

    /* 
     * @brief Realiza a consulta de um intervalo informado.
     */
    Matriz query(int posicao, int t0, int td, int inicio, int fim);  // Query a range of leaf nodes

    /* 
     * @brief Faz a multilplicação da matriz 'a' pela 'b'.
     */
    Matriz multiplicar(Matriz a, Matriz b);

    /* 
     * @brief Retorna o tamanho da SegTree.
     */
    int get_size();

    /* 
     * @brief Pinta a matriz da posição específica da SegTree.
     */
    void print_node(int posicao);

    // Apenas para conferir os TEST_CASE:
    std::string print_node_test(int posicao);
};

#endif