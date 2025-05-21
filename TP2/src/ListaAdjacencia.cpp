#include <iostream>
#include <string>
#include <stdexcept>

#include "../include/ListaAdjacencia.hpp"

ListaAdjacencia::ListaAdjacencia(){
    _tamanho = 0;
    _comeco = nullptr;
    _final = nullptr;
}

ListaAdjacencia::~ListaAdjacencia(){
    //std::cout << "Deletando ListaAdjacencia" << std::endl;
    remover_tudo();
}

bool ListaAdjacencia::esta_vazio() {
    return _tamanho == 0;
}

void ListaAdjacencia::insert() {
    // se a lista estiver vazia: cria um novo nó '_comeco' e '_final' 
    // com uma chave 0, e uma lista interna vazia 
    if(esta_vazio()){
        _final = _comeco = new Node_Ajc{ListaEncadeada(), 0, 0, nullptr};
        ++_tamanho;
        return;
    }

    // se não estiver vazia: cria um novo nó '_final' com uma chave igual 
    // a do último elemento mais um, e uma lista interna vazia
    Node_Ajc* novo_no = new Node_Ajc{ListaEncadeada(), _final->chave+1, 0, nullptr};

    _final->prox = novo_no;
    _final = novo_no;
    ++_tamanho;
}

void ListaAdjacencia::insert(int chave, int index) {
    // Verifique se a chave é válida
    if (chave < 0) {
        throw std::invalid_argument("Chave inválida para inserção na lista interna.");
    }

    Node_Ajc* temp = _comeco;
    while (temp->chave != chave) {
        temp = temp->prox;
    }

    // Verifique se a chave foi encontrada
    if (temp == nullptr) {
        throw std::invalid_argument("Chave não encontrada na lista principal.");
    }

    temp->lista.insere_fim(index);
}

void ListaAdjacencia::insert_cor(int chave, int cor){
    // Verifique se a chave é válida
    if (chave < 0) {
        throw std::invalid_argument("Chave inválida para inserção de cor na lista principal.");
    }

    Node_Ajc* temp = _comeco;
    while (temp->chave != chave) {
        temp = temp->prox;
    }

    // Verifique se a chave foi encontrada
    if (temp == nullptr) {
        throw std::invalid_argument("Chave não encontrada na lista principal.");
    }

    temp->cor = cor;
}

void ListaAdjacencia::remover_tudo() {
    Node_Ajc* temp = _comeco;
    while (_comeco != nullptr) {
        _comeco = _comeco->prox;

        temp->lista.remove_tudo();
        delete temp;

        temp = _comeco;
    }

    _comeco = _final = nullptr;
    _tamanho = 0;
}

void ListaAdjacencia::print() {
    Node_Ajc* temp = _comeco;

    while (temp != nullptr) {
        std::cout << "Chave: " << temp->chave << ", Cor: " << temp->cor << ", Lista interna: ";
        temp->lista.imprimir();
        std::cout << "" << std::endl;
        temp = temp->prox;
    }
}

void ListaAdjacencia::print_chaves() {
    Node_Ajc* temp = _comeco;

    while (temp != nullptr) {
        std::cout << temp->chave << " ";
        temp = temp->prox;
    }
    //std::cout << std::endl; // JOGAR FORA
}

int ListaAdjacencia::get_size() {
    return _tamanho;
}

Node_Ajc* ListaAdjacencia::get_primeiro_elemento() {
    return _comeco;
}

Node_Ajc* ListaAdjacencia::get_ultimo_elemento() {
    return _final;
}

Node_Ajc* ListaAdjacencia::get_elemento_em(int indice){
    // Verifique se o índice está dentro dos limites da lista
    if (indice < 0 || indice >= _tamanho) {
        throw std::out_of_range("Índice fora dos limites da lista principal.");
    }

    Node_Ajc* temp = _comeco;

    while(indice > 0){
        temp = temp->prox;
        indice--;
    }

    return temp;
}

void ListaAdjacencia::trocar_nos(int chave1, int chave2) {
    if (chave1 == chave2) {
        // Não é necessário trocar nós idênticos
        return;
    }

    Node_Ajc* prev1 = nullptr;
    Node_Ajc* prev2 = nullptr;
    Node_Ajc* node1 = _comeco;
    Node_Ajc* node2 = _comeco;

    // Encontre os nós com as chaves especificadas e seus nós anteriores
    while (node1 != nullptr && node1->chave != chave1) {
        prev1 = node1;
        node1 = node1->prox;
    }
    
    while (node2 != nullptr && node2->chave != chave2) {
        prev2 = node2;
        node2 = node2->prox;
    }

    // Verifique se ambos os nós foram encontrados
    if (node1 == nullptr || node2 == nullptr) {
        std::cout << "Pelo menos uma das chaves não foi encontrada na lista." << std::endl;
        return;
    }

    // Atualize os ponteiros para trocar os nós
    if (prev1 != nullptr) {
        prev1->prox = node2;
    } else {
        _comeco = node2;
    }

    if (prev2 != nullptr) {
        prev2->prox = node1;
    } else {
        _comeco = node1;
    }

    Node_Ajc* temp = node1->prox;
    node1->prox = node2->prox;
    node2->prox = temp;
}

void ListaAdjacencia::trocar_nos_das_posicoes(int i, int j) {
    if (i == j) {
        // Não é necessário trocar nós na mesma posição
        return;
    }

    Node_Ajc* prev1 = nullptr;
    Node_Ajc* prev2 = nullptr;
    Node_Ajc* node1 = _comeco;
    Node_Ajc* node2 = _comeco;

    int indice = 0;

    // Encontre os nós nas posições `i` e `j` e seus nós anteriores
    while (node1 != nullptr && indice != i) {
        prev1 = node1;
        node1 = node1->prox;
        indice++;
    }

    indice = 0;

    while (node2 != nullptr && indice != j) {
        prev2 = node2;
        node2 = node2->prox;
        indice++;
    }

    // Verifique se ambos os nós foram encontrados
    if (node1 == nullptr || node2 == nullptr) {
        std::cout << "Pelo menos uma das posições não foi encontrada na lista." << std::endl;
        return;
    }

    // Atualize os ponteiros para trocar os nós
    if (prev1 != nullptr) {
        prev1->prox = node2;
    } else {
        _comeco = node2;
    }

    if (prev2 != nullptr) {
        prev2->prox = node1;
    } else {
        _comeco = node1;
    }

    Node_Ajc* temp = node1->prox;
    node1->prox = node2->prox;
    node2->prox = temp;
}

void ListaAdjacencia::recebe(int i, Node_Ajc* NO) {
    // Verifique se o índice está dentro dos limites da lista
    if (i < 0 || i >= _tamanho) {
        throw std::out_of_range("Índice fora dos limites da lista principal.");
    }

    // Encontre o nó na posição `i`
    Node_Ajc* temp = _comeco;
    for (int index = 0; index < i; index++) {
        temp = temp->prox;
    }

    // Copie o nó NO para o nó encontrado
    // não foi copiado a lista porque foi usado apenas para ordenar os vértices 
    temp->chave = NO->chave; // Copie a chave
    temp->cor = NO->cor;     // Copie a cor
}