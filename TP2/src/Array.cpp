#include <iostream>
#include "../include/Array.hpp"

Array::Array(int size) : _tamanho(0){
    _array = new Vertice[size];
    _capacidade = size;
}

Array::~Array() {
    remover_tudo();
}

bool Array::esta_vazio() {
    return _tamanho == 0;
}

void Array::insert(int indice, int chave) {
    _array[indice].chave = chave;
    _tamanho++;
}

void Array::insert_cor(int chave, int cor) {
    _array[chave].cor = cor;
}

void Array::remover_tudo() {
    if (!esta_vazio()) {
        delete[] _array;
        _array = nullptr;
        _tamanho = 0;
        _capacidade = 0;
    }
}

void Array::print_chaves() {
    for (int i = 0; i < _tamanho; ++i) {
        std::cout << _array[i].chave << " ";
    }
}

void Array::print() {
    if (!esta_vazio()) {
        for (int i = 0; i < _tamanho; ++i) {
            std::cout << "Chave: " << _array[i].chave << " Cor: " << _array[i].cor << std::endl;
        }
        std::cout << std::endl;
    } 
    else {
        std::cout << "Array vazio." << std::endl;
    }
}

int Array::get_tamanho_maximo() {
    return _capacidade;
}

int Array::get_tamanho_atual() {
    return _tamanho;
}

void Array::trocar(int i, int j) {
    if(i == j){
        return;
    }
    Vertice temp = _array[i];
    _array[i] = _array[j];
    _array[j] = temp;
}

void Array::BubbleSort() { 
    // Algoritmo Bubble Sort
    for (int i = 0; i < _tamanho - 1; ++i) {
        for (int j = 0; j < _tamanho - i - 1; ++j) {
            if (_array[j].cor > _array[j + 1].cor) {
                // Troca os elementos se estiverem fora de ordem
                trocar(j, j + 1);
            } else if (_array[j].cor == _array[j + 1].cor && _array[j].chave > _array[j + 1].chave) {
                // Se as cores são iguais, compara as chaves
                trocar(j, j + 1);
            }
        }
    }
}

void Array::SelectionSort() {
    int i, j, min_idx;

    // Percorre todo o array
    for (i = 0; i < _tamanho - 1; i++) {
        // Encontra o índice do menor elemento no restante do array
        min_idx = i;
        for (j = i + 1; j < _tamanho; j++) {
            // Compara cor e, em caso de igualdade, compara chave
            if (_array[j].cor < _array[min_idx].cor ||
                (_array[j].cor == _array[min_idx].cor && _array[j].chave < _array[min_idx].chave)) {
                min_idx = j;
            }
        }

        // Troca o elemento encontrado com o primeiro elemento não ordenado
        trocar(i, min_idx);
    }
}

void Array::InsertionSort() {
    int i, j;
    Vertice aux;

    for (i = 1; i < _tamanho; i++) {
        aux = _array[i];
        j = i - 1;

        // Move os elementos do array[0..i-1] que são maiores que a chave
        // para uma posição à frente de sua posição atual
        while (j >= 0 && (_array[j].cor > aux.cor ||
                          (_array[j].cor == aux.cor && _array[j].chave > aux.chave))) {
            _array[j + 1] = _array[j];
            j = j - 1;
        }
        _array[j + 1] = aux;
    }
}

// Quicksort

void Array::Particao(int Esq, int Dir, int *i, int *j) {
    Vertice x, w;
    *i = Esq;
    *j = Dir;
    x = _array[(*i + *j) / 2]; /* obtem o pivo x */
    do {
        while (_array[*i].cor < x.cor || (x.cor == _array[*i].cor && x.chave > _array[*i].chave)) (*i)++;
        while (_array[*j].cor > x.cor || (x.cor == _array[*j].cor && x.chave < _array[*j].chave)) (*j)--;
        if (*i <= *j) {
            w = _array[*i];
            _array[*i] = _array[*j];
            _array[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Array::Ordena(int Esq, int Dir) {
    int i, j;
    Particao(Esq, Dir, &i, &j);
    if (Esq < j) Ordena(Esq, j);
    if (i < Dir) Ordena(i, Dir);
}

void Array::Quicksort() {
    Ordena(0, _tamanho - 1);
}


// Mergesort

void Array::Mergesort() {
    Mergesort(0, _tamanho - 1);
}

void Array::Mergesort(int esq, int dir) {
    if (esq < dir) {
        int meio = (esq + dir) / 2;
        Mergesort(esq, meio);
        Mergesort(meio + 1, dir);
        Merge(esq, meio, dir);
    }
}

void Array::Merge(int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    Vertice *L = new Vertice[n1];
    Vertice *R = new Vertice[n2];

    // Copia os elementos para os arrays temporários L[] e R[]
    for (int i = 0; i < n1; i++)
        L[i] = _array[esq + i];
    for (int j = 0; j < n2; j++)
        R[j] = _array[meio + 1 + j];

    // Junta os arrays temporários de volta ao array principal
    int i = 0;
    int j = 0;
    int k = esq;
    while (i < n1 && j < n2) {
        if (L[i].cor <= R[j].cor) {
            _array[k] = L[i];
            i++;
        } else {
            _array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        _array[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        _array[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void Array::Heapsort() {
    // Crie uma instância do Heap com o tamanho desejado
    Heap heap(_tamanho); 

    // Insira as tuplas no heap
    for(int i=0; i< _tamanho; i++){
        Tupla t = {_array[i].chave, _array[i].cor};
        heap.Inserir(t);
    }

    // Remova e imprima as tuplas do heap em ordem
    while (!heap.Vazio()) {
        Tupla temp = heap.Remover();
        std::cout << temp.chave << " ";
    }
}

void Array::Meu_metodo_de_ordenacao() {
    bool troca = true;
    int inicio = 0;
    int fim = _tamanho - 1;

    while (troca) {
        // Fase da esquerda para a direita (como no Bubble Sort)
        troca = false;
        for (int i = inicio; i < fim; ++i) {
            if (_array[i].cor > _array[i + 1].cor || 
                (_array[i].cor == _array[i + 1].cor && _array[i].chave > _array[i + 1].chave)) {
                trocar(i, i + 1);
                troca = true;
            }
        }

        // Se não houve trocas, o array está ordenado
        if (!troca) {
            break;
        }

        // Atualiza o ponto de parada à esquerda
        fim--;

        // Fase da direita para a esquerda
        troca = false;
        for (int i = fim - 1; i >= inicio; --i) {
            if (_array[i].cor > _array[i + 1].cor || 
                (_array[i].cor == _array[i + 1].cor && _array[i].chave > _array[i + 1].chave)) {
                trocar(i, i + 1);
                troca = true;
            }
        }

        // Atualiza o ponto de parada à direita
        inicio++;
    }
}
