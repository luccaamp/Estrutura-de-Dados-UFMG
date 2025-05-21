#include "../include/Pilha.hpp"
#include <stdexcept>

Pilha::Pilha(){
    _tamanho = 0;
    _topo = nullptr;
};

Pilha::~Pilha(){
    while(!isEmpty()){
        Node* temp = _topo;
        _topo = _topo->prox;
        delete temp;
    }
};

int Pilha::get_tamanho() const{
    return _tamanho;
};

void Pilha::pop(){
    if(isEmpty()){
        throw std::runtime_error("A pilha está vazia. Não é possível executar a função pop");
    }
    Node* temp = _topo;
    _topo = _topo->prox;
    --_tamanho;
    delete temp;
};

void Pilha::insert(char c){
    // Tratar o caso da pilha passar limite   
    if(_tamanho > TAMANHO_MAXIMO){
        throw std::runtime_error("A pilha ultrapassou seu limite");
    }

    Node *novo_no = new Node{c, nullptr};
    novo_no->prox = _topo;
    _topo = novo_no;
    _tamanho++;
};

// Retorna 1 se está vazia, 0 se não está 
bool Pilha::isEmpty(){
    return _topo == nullptr;
};

void Pilha::print() const{
    std::cout << "[";
    for (Node *tmp = _topo; tmp != nullptr; tmp=tmp->prox) {
        std::cout <<  tmp->dado << " ";
    }
    std::cout << "]" << std::endl;
};

std::string Pilha::imprimir() const {
    std::string resultado = "[";
    for (Node *tmp = _topo; tmp != nullptr; tmp = tmp->prox) {
        resultado += tmp->dado;
        if (tmp->prox != nullptr) {
            resultado += " ";
        }
    }
    resultado += "]";
    return resultado;
}

char Pilha::get_topo(){
    if (!Pilha::isEmpty()) {
        return _topo->dado;
    } else {
        throw std::runtime_error("A pilha está vazia. Não existe topo para retornar.");
    }
};