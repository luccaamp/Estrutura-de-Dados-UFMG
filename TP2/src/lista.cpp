#include <iostream>
#include <string>
#include <stdexcept>

#include "../include/lista.hpp"

ListaEncadeada::ListaEncadeada() {
  _tamanho = 0;
  _inicio = nullptr;
  _fim = nullptr;
}

ListaEncadeada::~ListaEncadeada() {
  //std::cout << "Deletando ListaEncadeada" << std::endl;
  while(_inicio != NULL){
    Node *temp = _inicio;
    _inicio = _inicio->prox;
    delete temp;
  }
  _fim = nullptr;
  _tamanho = 0;
}

bool ListaEncadeada::esta_vazio(){
  return _tamanho == 0;
}

unsigned int ListaEncadeada::get_tamanho() {
  return _tamanho;
}

void ListaEncadeada::insere_fim(int item){
  Node *novo_no = new Node{item, nullptr};

  if (_tamanho == 0) {
    _inicio = novo_no;
    _fim = novo_no;
  } 
  else {
    _fim->prox = novo_no;
  }

  _fim = novo_no;
  _tamanho++;
}


void ListaEncadeada::insere_posicao(int item, unsigned int posicao) {
  // Verifica se a posição fornecida é válida
  if (posicao > _tamanho) {
    throw std::out_of_range("Posição inválida para inserção na lista. Função: ListaEncadeada::insere_posicao");
  }

  // novo_no->dados = item;
  // novo_no->prox = nullptr;
  Node *novo_no = new Node{item, nullptr};

  if (posicao == 0) {
        // Se a posição for 0, insira o novo nó como o primeiro da lista.
        novo_no->prox = _inicio;
        _inicio = novo_no;

        if (_tamanho == 0) {
            // Se a lista estava vazia, atualize também o ponteiro para o fim.
            _fim = novo_no;
        }
    } else {
        // Se a posição não for 0, percorra a lista até encontrar a posição desejada.
        Node *anterior = nullptr;
        Node *atual = _inicio;
        for (unsigned int i = 0; i < posicao; i++) {
            anterior = atual;
            atual = atual->prox;
        }

        // Insira o novo nó entre o nó anterior e o nó atual.
        anterior->prox = novo_no;
        novo_no->prox = atual;

        if (posicao == _tamanho) {
            // Se a posição for igual ao tamanho atual, atualize o ponteiro para o fim.
            _fim = novo_no;
        }
    }
    _tamanho++;
}

int ListaEncadeada::get_item_em(unsigned int pos) {
  // Verifica se a posição fornecida é válida
  if (pos >= _tamanho) {
    throw std::out_of_range("Posição inválida para recuperação do item na lista. Função: ListaEncadeada::get_item_em");
  }

  Node *aux = _inicio;
  while (pos > 0) {
    aux = aux->prox;
    pos--;
  }
  return aux->dados;
}

void ListaEncadeada::remove_posicao(unsigned int pos) {
  // Verifica se a posição fornecida é válida
  if (pos >= _tamanho) {
    throw std::out_of_range("Posição inválida para remoção da lista. Função: ListaEncadeada::remove_posicao");
  }

  // Inicializa ponteiros
  Node *anterior = nullptr;
  Node *aux = _inicio;

  // Percorre a lista até encontrar a posição desejada
  while (pos > 0) {
    anterior = aux;
    aux = aux->prox;
    pos--;
  }

  // Remove o nó na posição desejada
  if (anterior != nullptr) {
    // Se existe um nó anterior, ajusta o ponteiro para ignorar o nó removido
    anterior->prox = aux->prox;
  } 
  else {
    // Se não existe um nó anterior, o nó removido é o primeiro da lista
    _inicio = aux->prox;
  }
  
  _tamanho--;
}

void ListaEncadeada::remove_tudo(){
  while (_inicio != nullptr) {
    Node *temp = _inicio;
    _inicio = _inicio->prox;
    delete temp;
    _tamanho--;
  }
  _fim = nullptr;
}

void ListaEncadeada::imprimir() {
  std::cout << "[";
  for (Node *tmp = _inicio; tmp != nullptr; tmp=tmp->prox) {
    std::cout << tmp->dados;
    if (tmp->prox != nullptr) {
      std::cout << ", "; // Só imprime a vírgula se não for o último elemento
    }
  }
  std::cout << "]" << std::endl;
}

bool ListaEncadeada::contem(int valor){
  Node* atual = _inicio; // Comece a busca do primeiro nó

    // Percorra a lista enquanto não chegar ao final
    while (atual != nullptr) {
        if (atual->dados == valor) {
            return true; // Encontrou o valor na lista
        }
        atual = atual->prox; // Avança para o próximo nó
    }

    // Se chegou até aqui, o valor não foi encontrado na lista
    return false;
}

std::string ListaEncadeada::retornar_lista() {
  std::string resultado = "[";
  for (Node *tmp = _inicio; tmp != nullptr; tmp=tmp->prox) {
    resultado += std::to_string(tmp->dados);
    if (tmp->prox != nullptr) {
      resultado += " "; // Só imprime a vírgula se não for o último elemento
    }
  }
  resultado += "]";
  return resultado;
}
