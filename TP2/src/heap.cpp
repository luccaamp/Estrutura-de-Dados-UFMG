#include "../include/heap.hpp"
#include <stdexcept>

Heap::Heap(int size) {
    if (size <= 0) {
        throw std::invalid_argument("O tamanho do Heap deve ser maior que zero.");
    }

    vertice = new Tupla[size];
    tamanho = 0;
}

Heap::~Heap() {
    delete[] vertice;
}

bool Heap::Condicao(Tupla t1, Tupla t2) {
    if (t1.cor > t2.cor) {
        return true;
    };

    if ((t1.cor == t2.cor) && (t1.chave > t2.chave)) {
        return true;
    }

    return false;
}

void Heap::Troca(Tupla& t1, Tupla& t2) {
    Tupla temp = t1;
    t1 = t2;
    t2 = temp;
}

bool Heap::Vazio() {
    return tamanho == 0;
}

int Heap::GetAncestral(int position) {
    return (position - 1) / 2;
}

int Heap::GetSucessorEsq(int position) {
    return 2 * position + 1;
}

int Heap::GetSucessorDir(int position) {
    return 2 * position + 2;
}

void Heap::Inserir(Tupla t) {
    if (Vazio()) {
        vertice[0] = t;
        tamanho++;
        return;
    }

    vertice[tamanho] = t;
    tamanho++;

    int i = tamanho - 1;

    while (i != 0 && (Condicao(vertice[GetAncestral(i)], vertice[i]))) {
        Troca(vertice[i], vertice[GetAncestral(i)]);
        i = GetAncestral(i);
    }
}

Tupla Heap::Remover() {
    if (tamanho < 0) {
        std::cerr << "Não tem como remover elemento, o Heap está vazio" << std::endl;
        exit(1);
    }

    Tupla raiz = vertice[0];
    vertice[0] = vertice[tamanho - 1];
    tamanho--;

    int i = 0;
    while (i < tamanho) {
        int menor = i;

        if (GetSucessorEsq(i) < tamanho && Condicao(vertice[menor], vertice[GetSucessorEsq(i)])) {
            menor = GetSucessorEsq(i);
        }
        if (GetSucessorDir(i) < tamanho && Condicao(vertice[menor], vertice[GetSucessorDir(i)])) {
            menor = GetSucessorDir(i);
        }

        if (menor == i) {
            break;
        }

        Troca(vertice[i], vertice[menor]);
        i = menor;
    }

    return raiz;
}
