#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <iomanip>

#include "../include/lista.hpp"
#include "../include/ListaAdjacencia.hpp"
#include "../include/graph.hpp"
#include "../include/Array.hpp"

const bool Verbose = false;
const bool Tempo = false;
const bool TEMPO_ARRAY = false;

void relogio(){
    // Inicialização de variáveis
    char opcao;
    int num_Vertices;

    std::cin >> opcao;
    std::cin >> num_Vertices;

    Array array(num_Vertices);

    // Insere os vértices
    for (int i = 0; i < num_Vertices; i++){
        
        array.insert(i, i);

        int num_Vizinhos;
        std::cin >> num_Vizinhos;

        for (int j = 0; j < num_Vizinhos; j++) {
            int aresta;
            std::cin >> aresta;
        }
    }

    // Pega as cores de cada vértice
    for (int i = 0; i < num_Vertices; i++){
        int cor;
        std::cin >> cor;
        array.insert_cor(i, cor);
    }

    // Obtenha o tempo de início
    auto start_time = std::chrono::high_resolution_clock::now();

    if (opcao == 'b') {
        array.BubbleSort();
    } 
    else if (opcao == 's') {
        array.SelectionSort();
    } 
    else if (opcao == 'i') {
        array.InsertionSort();
    } 
    else if (opcao == 'q') {                 
        array.Quicksort();
    }
    else if (opcao == 'm'){
        array.Mergesort();
    }
    else if (opcao == 'p'){
        array.Heapsort();
    }
    else if (opcao == 'y'){
        array.Meu_metodo_de_ordenacao();
    }

    // Obtenha o tempo de término
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;
    std::cout << num_Vertices << " " << elapsed_time.count() << std::endl;
}

int main(){
    if(TEMPO_ARRAY){
        relogio();
        return 0;
    }

    // Inicialização de variáveis
    char opcao;
    int num_Vertices;
    Grafo g;

    if(Verbose)
        std::cout << "Digite a opção: " <<  std::endl;
    std::cin >> opcao;

    if(Verbose)
        std::cout << "Digite o número de vértices: " <<  std::endl;
    std::cin >> num_Vertices;

    // Insere os vértices
    for (int i = 0; i < num_Vertices; i++){
        
        g.Insere_Vertice();

        int num_Vizinhos;

        if(Verbose)
            std::cout << "Digite a quantidade de vizinhos para o vértice " << i << ": ";
        std::cin >> num_Vizinhos;

        if(Verbose)
            std::cout << "Digite os vizinhos para o vértice " << i << ": ";

        for (int j = 0; j < num_Vizinhos; j++) {
            int aresta;
            std::cin >> aresta;
            g.Insere_Aresta(i, aresta);
        }
    }

    // Pega as cores de cada vértice
    if(Verbose)
        std::cout << "Digite as cores de cada vértice: " <<  std::endl;

    for (int i = 0; i < num_Vertices; i++){
        int cor;
        std::cin >> cor;
        g.Insere_Cor(i, cor); 
    }
    
    if(Verbose){
        // Verifica a quantidade de vértices e arestas
        std::cout << "Quantidade de vértices: ";
        std::cout << g.Quantidade_Vertices() << std::endl;

        std::cout << "Quantidade de arestas: ";
        std::cout << g.Quantidade_Arestas() << std::endl;

        // Verifica o grau mínimo e máximo
        std::cout << "Grau Mínimo: ";
        std::cout << g.Grau_Minimo() << std::endl;

        std::cout << "Grau Máximo: ";
        std::cout << g.Grau_Maximo() << std::endl;

        // Imprime vizinhos
        g.Imprime_Vizinhos();

        std::cout << "É um grafo completo?:  " << (g.EhCompleto() ? "1 - Completo" : "0 - Não é completo") << std::endl;
    }  

    if (g.EhColoracaoGulosa() == true) {
        // Obtenha o tempo de início
        auto start_time = std::chrono::high_resolution_clock::now();

        std::cout << "1 ";
        
        // Método da bolha ou bubble sort.      ESTÁVEL
        if (opcao == 'b') {
            g.BubbleSort();
        } 

        // Método da seleção ou selection sort.   NÃO ESTÁVEL
        else if (opcao == 's') {
            g.SelectionSort();
        } 

        // Método da inserção ou insertion sort.   ESTÁVEL
        else if (opcao == 'i') {
            g.InsertionSort();
        } 

        // Quicksort.                              NÃO ESTÁVEL
        else if (opcao == 'q') {                 
            g.Quicksort();
        }

        // Mergesort.                              ESTÁVEL
        else if (opcao == 'm'){
            g.Mergesort();
        }

        // Heapsort                                NÃO ESTÁVEL
        else if (opcao == 'p'){
            g.Heapsort();
        }

        // Meu método de ordenação                 ESTÁVEL
        else if (opcao == 'y'){
            g.Meu_metodo_de_ordenacao();
        }
        
        if(Tempo){
            // Obtenha o tempo de término
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_time = end_time - start_time;
            std::cout << num_Vertices << " " << elapsed_time.count() << std::endl;
        }
    } 
    else {
        std::cout << "0" << std::endl;
    }
    
    return 0;
}