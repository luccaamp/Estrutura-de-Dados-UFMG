#include "../include/graph.hpp"
#include "../include/lista.hpp"
#include "../include/ListaAdjacencia.hpp"

#include "../include/heap.hpp"

#include <iostream>
#include <string>
#include <limits>

Grafo::Grafo() {
    
}

Grafo::~Grafo() {
    
}

void Grafo::Insere_Vertice() {
    vertices.insert();
}

void Grafo::Insere_Aresta(int v, int w) {
    vertices.insert(v, w);
}

void Grafo::Insere_Cor(int v, int cor){
    vertices.insert_cor(v,cor);
}

int Grafo::Quantidade_Vertices() {
    return vertices.get_size();
}

int Grafo::Quantidade_Arestas() {
    int totalArestas = 0;
    Node_Ajc* temp = vertices.get_primeiro_elemento();
    while (temp != nullptr) {
        totalArestas += temp->lista.get_tamanho();
        temp = temp->prox;
    }
    return totalArestas / 2; // Dividido por 2, pois é um grafo não direcionado
}

int Grafo::Grau_Minimo() {
    int grauMinimo = std::numeric_limits<int>::max(); // Inicializa com o valor máximo possível
    for (Node_Ajc* temp = vertices.get_primeiro_elemento(); temp != nullptr; temp = temp->prox) {
        int grau = temp->lista.get_tamanho();
        if (grau < grauMinimo) {
            grauMinimo = grau;
        }
    }
    return grauMinimo;
}

int Grafo::Grau_Maximo() {
    int grauMaximo = 0;
    Node_Ajc* temp = vertices.get_primeiro_elemento();
    while (temp != nullptr) {
        int grau = temp->lista.get_tamanho();
        if (grau > grauMaximo) {
            grauMaximo = grau;
        }
        temp = temp->prox;
    }
    return grauMaximo;
}

void Grafo::Imprime_Vizinhos(void) {
    vertices.print();
}

bool Grafo::Existe_Aresta(int i, int j) {
    Node_Ajc* temp = vertices.get_primeiro_elemento();

    // Encontrar o vértice i na lista de adjacência
    while (temp != nullptr) {
        if (temp->chave == i) {
            // Verificar se o vértice j está na lista de vizinhos de i
            return temp->lista.contem(j);
        }
        temp = temp->prox;
    }

    // Se chegou até aqui, o vértice i não foi encontrado
    return false;
}

bool Grafo::EhCompleto() {
    int numVertices = Quantidade_Vertices();
    
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i != j && !Existe_Aresta(i, j)) {
                // Se não existe uma aresta entre o vértice i e j, o grafo não é completo
                return false;
            }
        }
    }
    return true; // Se todas as combinações de vértices tiverem arestas, o grafo é completo
}

bool Grafo::EhColoracaoGulosa() {
    Node_Ajc* temp = vertices.get_primeiro_elemento();

    while (temp != nullptr) {
        int Cor_Atual = temp->cor;

        int tamanho = temp->lista.get_tamanho();

        // Verificar se Cor_Atual é igual à cor do Vizinho i da lista de Vizinhos
        for (int i = 0; i < tamanho; i++) {
            int indice = temp->lista.get_item_em(i);

            Node_Ajc* vizinho = vertices.get_elemento_em(indice);

            if (vizinho != nullptr && Cor_Atual == vizinho->cor) {
                return false;
            }
        }

        if (Cor_Atual > 1) {
            for (int i = 1; i < Cor_Atual; i++) {
                bool encontrado = false; // Inicializa a flag para o número atual como não encontrado

                for (int j = 0; j < tamanho; j++) {

                    int indice = temp->lista.get_item_em(j);
                    Node_Ajc* vizinho = vertices.get_elemento_em(indice);

                    if (vizinho->cor == i) {
                        encontrado = true;
                        break; // Se o número for encontrado, não é necessário continuar a busca
                    }
                }

                if (!encontrado) {
                    return false;
                    break; // Se um número não for encontrado, não é necessário continuar verificando
                }
            }
        }
        temp = temp->prox;
    }

    return true;
}

void Grafo::Printar_chaves(){
    vertices.print_chaves();
}

void Grafo::OrdenarPorCorCrescente() {
    Node_Ajc* atual;
    Node_Ajc* prox;
    bool trocado;

    do {
        trocado = false;
        atual = vertices.get_primeiro_elemento();

        while (atual != nullptr && atual->prox != nullptr) {
            prox = atual->prox;

            if (atual->cor > prox->cor) {
                vertices.trocar_nos(atual->chave, prox->chave);
                trocado = true;
            }

            atual = prox;
        }
    } while (trocado);

    vertices.print_chaves();
}

void Grafo::BubbleSort() { 
    bool esta_sorteado;

    int trocas=0, iteracoes=0;

    do {
        esta_sorteado = false;
        Node_Ajc* atual = vertices.get_primeiro_elemento();

        while (atual != nullptr && atual->prox != nullptr) {
            Node_Ajc* prox = atual->prox;

            if (atual->cor > prox->cor) {
                vertices.trocar_nos(atual->chave, prox->chave);
                esta_sorteado = true;
                trocas++;
            }

            atual = prox;
            iteracoes++;
        }
    } while (esta_sorteado);

    vertices.print_chaves();
} 

void Grafo::SelectionSort() {
    int tamanho = vertices.get_size();

    for (int i = 0; i < tamanho - 1; i++) {
        int indiceMenor = i;

        for (int j = i + 1; j < tamanho; j++) {
            // Compare as cores dos vértices para encontrar o menor

            Node_Ajc* temp = vertices.get_elemento_em(j);
            Node_Ajc* menor = vertices.get_elemento_em(indiceMenor);

            if (temp->cor < menor->cor) {
                indiceMenor = j;
            }
            else if ((temp->cor == menor->cor) && (temp->chave < menor->chave)){
                indiceMenor = j;
            }
        }

        // Troque o vértice atual pelo vértice com a menor cor
        if (indiceMenor != i) {
            
            // Trocando o Vértice da posição i, com o vértice da posição indiceMenor
            int chave_i = vertices.get_elemento_em(i)->chave; // Descobrimos o "nome"/chave do Vértice da posição i
            int chave_indiceMenor = vertices.get_elemento_em(indiceMenor)->chave; // Descobrimos o "nome"/chave do Vértice da posição indiceMenor

            // Trocamos os Vértices com base nas chaves
            vertices.trocar_nos(chave_i, chave_indiceMenor);
        }
    }

    vertices.print_chaves();
}

void Grafo::InsertionSort(){
    int i, j;
    Node_Ajc* aux;

    int tamanho_vertices = vertices.get_size();

    for(i = 1; i < tamanho_vertices; i++){
        aux = vertices.get_elemento_em(i);
        j = i - 1;

        while(( j >= 0 ) && (aux->cor < vertices.get_elemento_em(j)->cor)){
            vertices.trocar_nos_das_posicoes(j+1, j);
            j--;
        }
        int temp = vertices.get_elemento_em(j+1)->chave;
        vertices.trocar_nos(temp, aux->chave); 
    }

    vertices.print_chaves();
}


// QuickSort:

void Grafo::Particao(int Esq, int Dir, int *i, int *j) {
    *i = Esq;
    *j = Dir;
    Node_Ajc* x = vertices.get_elemento_em((*i + *j) / 2);
    do {
        while (x->cor > vertices.get_elemento_em(*i)->cor || 
               (x->cor == vertices.get_elemento_em(*i)->cor && x->chave > vertices.get_elemento_em(*i)->chave))
            (*i)++;
        
        while (x->cor < vertices.get_elemento_em(*j)->cor || 
               (x->cor == vertices.get_elemento_em(*j)->cor && x->chave < vertices.get_elemento_em(*j)->chave))
            (*j)--;

        if (*i <= *j) {
            vertices.trocar_nos_das_posicoes(*i, *j);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Grafo::Ordena(int Esq, int Dir){ 
    int i, j;
    Particao(Esq, Dir, &i, &j);
    if (Esq < j) Ordena(Esq, j);
    if (i < Dir) Ordena(i, Dir);
}

void Grafo::Quicksort(){
    int n = vertices.get_size(); 
    Ordena(0, n-1);
    vertices.print_chaves();
}


// Mergesort:

void Grafo::Merge(int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    // Crie vetores temporários
    ListaAdjacencia temp1, temp2;

    // Copie dados para vetores temporários temp1[] e temp2[]
    for (int i = 0; i < n1; i++) {
        temp1.insert();
        temp1.recebe(i, vertices.get_elemento_em(esq + i));
    }
    for (int j = 0; j < n2; j++) {
        temp2.insert();
        temp2.recebe(j, vertices.get_elemento_em(meio + 1 + j));
    }

    // Mesclar os vetores temporários de volta em vetor[esq..dir]
    int i = 0, j = 0, k = esq;

    while (i < n1 && j < n2) {

        int cor1 = temp1.get_elemento_em(i)->cor;
        int cor2 = temp2.get_elemento_em(j)->cor;

        int chave1 = temp1.get_elemento_em(i)->chave;
        int chave2 = temp2.get_elemento_em(j)->chave;

        if (cor1 < cor2 || (cor1 == cor2 && chave1 < chave2)) {
            vertices.trocar_nos(vertices.get_elemento_em(k)->chave, chave1);
            i++;
        } else {
            vertices.trocar_nos(vertices.get_elemento_em(k)->chave, chave2);
            j++;
        }
        k++;
    }

    while (i < n1) {
        vertices.trocar_nos(vertices.get_elemento_em(k)->chave, temp1.get_elemento_em(i)->chave);
        i++;
        k++;
    }

    while (j < n2) {
        vertices.trocar_nos(vertices.get_elemento_em(k)->chave, temp2.get_elemento_em(j)->chave);
        j++;
        k++;
    }
}

void Grafo::Mergesort(int esq, int dir) {
    if (esq < dir) {
        int meio = (esq + dir) / 2;
        // Ordena a primeira metade
        Mergesort(esq, meio);

        // Ordena a segunda metade
        Mergesort(meio+1, dir);

        // Mescla as metades ordenadas
        Merge(esq, meio, dir);
    }
}

void Grafo::Mergesort() {
    int tamanho = vertices.get_size();
    if (tamanho > 0) {
        Mergesort(0, tamanho-1);
    }
    vertices.print_chaves();
}


// Heapsort:

void Grafo::Heapsort() {
    // Tamanho da lista de vértices
    int tamanho = vertices.get_size();

    // Crie uma instância do Heap com o tamanho desejado
    Heap heap(tamanho); 

    // Insira as tuplas no heap

    for(int i=0; i< tamanho; i++){
        Tupla t = {vertices.get_elemento_em(i)->chave, vertices.get_elemento_em(i)->cor};
        heap.Inserir(t);
    }

    // Remova e imprima as tuplas do heap em ordem
    while (!heap.Vazio()) {
        Tupla temp = heap.Remover();
        std::cout << temp.chave << " ";
    }
}



void Grafo::Meu_metodo_de_ordenacao(){
    bool esta_sorteado = false;
    int esq = 0;
    int dir = vertices.get_size() - 1;

    while (!esta_sorteado && esq < dir) {
        esta_sorteado = true;

        // Mova o maior elemento para o final
        for (int i = esq; i < dir; i++) {
            Node_Ajc* atual = vertices.get_elemento_em(i);
            Node_Ajc* prox = vertices.get_elemento_em(i + 1);

            if (atual->cor > prox->cor ||
                (atual->cor == prox->cor && atual->chave > prox->chave)) {
                vertices.trocar_nos(atual->chave, prox->chave);
                esta_sorteado = false;
            }
        }
        dir--;

        // Mova o menor elemento para o início
        for (int i = dir; i > esq; i--) {
            Node_Ajc* atual = vertices.get_elemento_em(i);
            Node_Ajc* anterior = vertices.get_elemento_em(i - 1);

            if (atual->cor < anterior->cor ||
                (atual->cor == anterior->cor && atual->chave < anterior->chave)) {
                vertices.trocar_nos(atual->chave, anterior->chave);
                esta_sorteado = false;
            }
        }
        esq++;
    }

    vertices.print_chaves();
}
