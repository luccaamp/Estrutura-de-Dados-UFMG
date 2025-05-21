#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest.h"

#include "../include/graph.hpp"
#include "../include/lista.hpp"
#include "../include/ListaAdjacencia.hpp"

#include <string>

TEST_CASE("1 - Teste da Classe ListaAdjacencia") {
    SUBCASE("1.1 - Testa da função get_elemento_em") {
        ListaAdjacencia lista;

        // Inserir alguns elementos na lista
        
        lista.insert();
        lista.insert(0, 1);
        lista.insert(0, 4);

        lista.insert();
        lista.insert(1, 0);
        lista.insert(1, 2);

        lista.insert();
        lista.insert(2, 1);
        lista.insert(2, 3);

        lista.insert();
        lista.insert(3, 2);
        lista.insert(3, 4);

        lista.insert();
        lista.insert(4, 3);
        lista.insert(4, 1);

        lista.insert_cor(0, 1);
        lista.insert_cor(1, 2);
        lista.insert_cor(2, 1);
        lista.insert_cor(3, 3);
        lista.insert_cor(4, 2);

        CHECK(lista.get_size() == 5);

        // Agora, vamos verificar se os elementos podem ser recuperados corretamente

        Node_Ajc* elemento_0 = lista.get_elemento_em(0);
        CHECK(elemento_0->chave == 0);
        CHECK(elemento_0->lista.get_item_em(0) == 1);
        CHECK(elemento_0->lista.get_item_em(1) == 4);
        CHECK(elemento_0->cor == 1);

        Node_Ajc* elemento_1 = lista.get_elemento_em(1);
        CHECK(elemento_1->chave == 1);
        CHECK(elemento_1->lista.get_item_em(0) == 0);
        CHECK(elemento_1->lista.get_item_em(1) == 2);
        CHECK(elemento_1->cor == 2);

        lista.print();

        lista.trocar_nos(0, 4);

        std::cout << "---------------------------------------------\nDepois da Troca: " << std::endl;

        lista.print();

        Node_Ajc* node1 = new Node_Ajc{ListaEncadeada(), 70, 25, nullptr};
        
        //lista.inserir_node_em(node1, 3);

        std::cout << "---------------------------------------------\nDepois de inserir_node_em: " << std::endl;

        lista.print();
    }
}//9

TEST_CASE("2 - Teste da Classe ListaEncadeada") {
    SUBCASE("2.1 - Teste da função insere_fim") {
        ListaEncadeada lista;

        // Insere alguns elementos no final da lista
        lista.insere_fim(10);
        lista.insere_fim(20);
        lista.insere_fim(30);

        CHECK(lista.get_tamanho() == 3);
        CHECK(lista.get_item_em(0) == 10);
        CHECK(lista.get_item_em(1) == 20);
        CHECK(lista.get_item_em(2) == 30);
    }

    SUBCASE("2.2 - Teste da função insere_posicao") {
        ListaEncadeada lista;

        // Insere elementos em posições específicas na lista
        lista.insere_posicao(10, 0);
        lista.insere_posicao(20, 1);
        lista.insere_posicao(30, 1);

        CHECK(lista.get_tamanho() == 3);
        CHECK(lista.get_item_em(0) == 10);
        CHECK(lista.get_item_em(1) == 30);
        CHECK(lista.get_item_em(2) == 20);
    }

    SUBCASE("2.3 - Teste da função remove_posicao") {
        ListaEncadeada lista;

        // Insere alguns elementos na lista
        lista.insere_fim(10);
        lista.insere_fim(20);
        lista.insere_fim(30);

        // Remove um elemento da posição 1
        lista.remove_posicao(1);

        CHECK(lista.get_tamanho() == 2);
        CHECK(lista.get_item_em(0) == 10);
        CHECK(lista.get_item_em(1) == 30);
    }

    SUBCASE("2.4 - Teste da função contem") {
        ListaEncadeada lista;

        // Insere alguns elementos na lista
        lista.insere_fim(10);
        lista.insere_fim(20);
        lista.insere_fim(30);

        CHECK(lista.contem(20) == true);
        CHECK(lista.contem(40) == false);
    }
}

TEST_CASE("3 - Teste da Classe ListaAdjacencia") {
    SUBCASE("3.1 - Teste da função insert") {
        ListaAdjacencia lista;

        // Insere alguns elementos na lista
        lista.insert();
        lista.insert(0, 1);
        lista.insert(0, 4);

        CHECK(lista.get_size() == 1);

        Node_Ajc* elemento_0 = lista.get_elemento_em(0);
        CHECK(elemento_0->chave == 0);
        CHECK(elemento_0->lista.get_item_em(0) == 1);
        CHECK(elemento_0->lista.get_item_em(1) == 4);
    }

    SUBCASE("3.2 - Teste da função insert_cor") {
        ListaAdjacencia lista;

        // Insere alguns elementos na lista
        lista.insert();
        lista.insert_cor(0, 1);

        CHECK(lista.get_size() == 1);

        Node_Ajc* elemento_0 = lista.get_elemento_em(0);
        CHECK(elemento_0->chave == 0);
        CHECK(elemento_0->cor == 1);
    }

    SUBCASE("3.3 - Teste da função trocar_nos") {
        ListaAdjacencia lista;

        // Insere alguns elementos na lista
        lista.insert();
        lista.insert(0, 1);

        lista.insert();
        lista.insert(1, 0);

        CHECK(lista.get_size() == 2);

        // Troca os nós com chaves 0 e 1
        lista.trocar_nos(0, 1);

        Node_Ajc* elemento_0 = lista.get_elemento_em(0);
        CHECK(elemento_0->chave == 1);
        CHECK(elemento_0->lista.get_item_em(0) == 0);

        Node_Ajc* elemento_1 = lista.get_elemento_em(1);
        CHECK(elemento_1->chave == 0);
        CHECK(elemento_1->lista.get_item_em(0) == 1);
    }
}
