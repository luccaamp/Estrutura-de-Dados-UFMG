#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <string>

struct Tupla {
  std::string combinacao;
  int flag;
  Tupla *prox;
};

class Vector {
  private:
    int _tamanho;
    Tupla *_inicio;
    Tupla *_fim;
  public:
    Vector();

    ~Vector();

    bool esta_vazio();

    int get_tamanho();

    void insere_fim(Tupla tupla);

    void insere_posicao(Tupla tupla, int posicao);
    
    int get_flag_em(int pos);

    std::string get_combinacao_em(int pos);

    Tupla& get_elemento_em(int pos);

    void remove_posicao(int pos);

    void remove_tudo();

    void imprimir();
};

#endif
