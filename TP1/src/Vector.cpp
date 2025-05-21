#include <iostream>
#include <string>

#include "../include/Vector.hpp"

Vector::Vector() {
    _tamanho = 0;
    _inicio = nullptr;
    _fim = nullptr;
}

Vector::~Vector() {
    //std::cout << "Deletando Vector" << std::endl;
    remove_tudo();
}

bool Vector::esta_vazio(){
    return _tamanho == 0;
}

int Vector::get_tamanho() {
    return _tamanho;
}

void Vector::insere_fim(Tupla tupla){
    Tupla *nova_tupla = new Tupla{tupla.combinacao, tupla.flag, nullptr};

    if (_tamanho == 0) {
        _inicio = nova_tupla;
        _fim = nova_tupla;
    } 
    else {
        _fim->prox = nova_tupla;
    }

    _fim = nova_tupla;
    _tamanho++;
}


void Vector::insere_posicao(Tupla tupla, int posicao) {
    if (posicao > _tamanho) {
        std::cout << "Função: Vector::insere_posicao, erro: pos >= tamanho" << std::endl;
        return;
    }

    Tupla *nova_tupla = new Tupla{tupla.combinacao, tupla.flag, nullptr};

    if (posicao == 0) {
        // Se a posição for 0, insira o novo nó como o primeiro da lista.
        nova_tupla->prox = _inicio;
        _inicio = nova_tupla;

        if (_tamanho == 0) {
            // Se a lista estava vazia, atualize também o ponteiro para o fim.
            _fim = nova_tupla;
        }
    } else {
        // Se a posição não for 0, percorra a lista até encontrar a posição desejada.
        Tupla *anterior = nullptr;
        Tupla *atual = _inicio;
        for (int i = 0; i < posicao; i++) {
            anterior = atual;
            atual = atual->prox;
        }

        // Insira o novo nó entre o nó anterior e o nó atual.
        anterior->prox = nova_tupla;
        nova_tupla->prox = atual;

        if (posicao == _tamanho) {
            // Se a posição for igual ao tamanho atual, atualize o ponteiro para o fim.
            _fim = nova_tupla;
        }
    }
    _tamanho++;
}


void Vector::remove_posicao(int pos) {
    if (pos >= _tamanho) {
        std::cout << "Função: Vector::remove_posicao, erro: pos >= tamanho" << std::endl;
        return;
    }

    Tupla *anterior = nullptr;
    Tupla *aux = _inicio;

    if (pos == 0) {
        _inicio = aux->prox;
        if (_inicio == nullptr) {
        _fim = nullptr;
        }
        delete aux;
    } else {
        while (pos > 0) {
        anterior = aux;
        aux = aux->prox;
        pos--;
        }

        anterior->prox = aux->prox;
        if (aux == _fim) {
        _fim = anterior;
        }
        delete aux;
    }

    _tamanho--;
}

void Vector::remove_tudo(){
    while (_inicio != nullptr) {
        Tupla *temp = _inicio;
        _inicio = _inicio->prox;
        delete temp;
        _tamanho--;
    }
    _fim = nullptr;
}

int Vector::get_flag_em(int pos) {
    Tupla *aux = _inicio;
    while (pos > 0) {
        aux = aux->prox;
        pos--;
    }
    return aux->flag;
}

std::string Vector::get_combinacao_em(int pos) {
    Tupla *aux = _inicio;
    while (pos > 0) {
        aux = aux->prox;
        pos--;
    }
    return aux->combinacao;
}

Tupla& Vector::get_elemento_em(int pos) {
    if (pos >= _tamanho) {
        throw std::out_of_range("Função: 'Vector::get_elemento_em'. Posição fora dos limites do Vector");
    }

    Tupla *aux = _inicio;
    for (int i = 0; i < pos; i++) {
        aux = aux->prox;
    }

    return *aux;
}

void Vector::imprimir() {
    std::cout << "[";
    for (Tupla *tmp = _inicio; tmp != nullptr; tmp=tmp->prox) {
        std::cout << "{(" << tmp->combinacao << ")," << tmp->flag << "} ";
        if (tmp->prox != nullptr) {
        std::cout << ", "; // Só imprime a vírgula se não for o último elemento
        }
    }
    std::cout << "]" << std::endl;
}