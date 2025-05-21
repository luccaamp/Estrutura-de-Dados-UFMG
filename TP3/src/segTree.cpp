#include "segTree.hpp"

Matriz::Matriz(long long a, long long b, long long c, long long d) {
  dado[0][0] = a;
  dado[0][1] = b;
  dado[1][0] = c;
  dado[1][1] = d;
}

Matriz::Matriz() {
  dado[0][0] = dado[1][1] = 1;
  dado[0][1] = dado[1][0] = 0;
}

void Matriz::print() {
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      std::cout << dado[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

SegTree::SegTree(int n) {
  if (n <= 0) {
    throw std::invalid_argument("O tamanho da SegTree deve ser maior que zero.");
  }
  
  segTree = new Matriz[4 * n];
  _identidade = Matriz(1, 0, 0, 1);
  _tamanho = n;
}

SegTree::~SegTree() {
  delete[] segTree;
}

void SegTree::build(int posicao, int inicio, int fim) {
  if (posicao < 0 || posicao >= 4 * _tamanho || inicio > fim || inicio < 0 || fim >= _tamanho) {
    throw std::out_of_range("Índices ou tamanhos fora dos limites ao construir a SegTree.");
  }
  // Folha recebe matriz identidade
  if (inicio == fim){
    segTree[posicao] = _identidade;
  }
  else {
    int meio = (inicio + fim) / 2;
    build(2 * posicao, inicio, meio); // Cria nodes filhos esquerda
    build(2 * posicao + 1, meio + 1, fim); // Cria nodes filhos direita
    segTree[posicao] = multiplicar(segTree[2 * posicao], segTree[2 * posicao + 1]);
  }
}

Matriz SegTree::update(int indice, Matriz novaMatriz, int posicao, int inicio, int fim) {
  if (posicao < 0 || posicao >= 4 * _tamanho || inicio > fim || inicio < 0 || fim >= _tamanho ||
      indice < 0 || indice >= _tamanho) {
    throw std::out_of_range("Índices ou tamanhos fora dos limites ao atualizar a SegTree.");
  }
  
  // Não está dentro do intervalo
  if (indice < inicio || indice > fim){
    return segTree[posicao];
  }
  // Node recebe o valor da nova matriz
  if (inicio == fim){
    return segTree[posicao] = novaMatriz;
  }

  int meio = (inicio + fim) / 2;

  // Atualiza os nodes acima do node informado
  return segTree[posicao] = multiplicar(update(indice, novaMatriz, 2 * posicao, inicio, meio),
                                        update(indice, novaMatriz, 2 * posicao + 1, meio + 1, fim));
}

Matriz SegTree::query(int posicao, int t0, int td, int inicio, int fim) {
  if (posicao < 0 || posicao >= 4 * _tamanho || inicio > fim || inicio < 0 || fim >= _tamanho ||
      t0 < 0 || td >= _tamanho) {
    throw std::out_of_range("Índices ou tamanhos fora dos limites ao consultar a SegTree.");
  }
  
  // Não está dentro do intervalo
  if (td < inicio || t0 > fim){
    return _identidade;
  }
  
  // Totalmente dentro do intervalo
  if (t0 <= inicio && fim <= td){
    return segTree[posicao];
  }

  int meio = (inicio + fim) / 2;

  // Consulta de um intervalo de nodes parcialmente inserido no intervalo total
  return multiplicar(query(2 * posicao, t0, td, inicio, meio),
                    query(2 * posicao + 1, t0, td, meio + 1, fim));
}

Matriz SegTree::multiplicar(Matriz a, Matriz b) {
  Matriz res;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      res.dado[i][j] = 0;
      for (int k = 0; k < 2; ++k) {
        res.dado[i][j] += (a.dado[i][k] * b.dado[k][j]) % (int)(1e8);
        res.dado[i][j] %= (int)(1e8);
      }
    }
  }
  
  return res;
}

int SegTree::get_size(){
  return _tamanho;
}
  
void SegTree::print_node(int posicao){
  segTree[posicao].print();
}


// Apenas para conferir os TEST_CASE:

std::string SegTree::print_node_test(int posicao){
  return segTree[posicao].print_string();
}

std::string Matriz::print_string() {
  std::string resposta;

  for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
          resposta += std::to_string(dado[i][j]) + " ";
      }
  }

  return resposta;
}
