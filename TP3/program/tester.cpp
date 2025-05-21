#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest.h"

#include "../include/segTree.hpp"

#include <string>

TEST_CASE("1 - Teste da Classe SegTree") {
    SUBCASE("1.1 - Teste do Construtor e Destrutor") {
        int n = 5;
        SegTree segTree(n);
        CHECK(segTree.get_size() == n);
    }

    SUBCASE("1.2 - Teste da Função build") {
        int n = 5;
        SegTree segTree(n);
        segTree.build(1, 0, n - 1);

        std::string m1 = segTree.print_node_test(1);
        std::string m2 = segTree.print_node_test(2);
        std::string m3 = segTree.print_node_test(3);
        std::string m4 = segTree.print_node_test(4);
        std::string m5 = segTree.print_node_test(5);

        CHECK(m1 == "1 0 0 1 ");
        CHECK(m2 == "1 0 0 1 ");
        CHECK(m3 == "1 0 0 1 ");
        CHECK(m4 == "1 0 0 1 ");
        CHECK(m5 == "1 0 0 1 ");
    }

    SUBCASE("1.3 - Teste da Função update") {
        int n = 5;
        SegTree segTree(n);
        Matriz novaMatriz(2, 1, 1, 3);
        segTree.update(2, novaMatriz, 1, 0, n - 1);
        
        std::string m = segTree.print_node_test(2);

        CHECK(m == "2 1 1 3 ");
    }

    SUBCASE("1.4 - Teste da Função query matriz identidade") {
        int n = 5;
        SegTree segTree(n);
        segTree.build(1, 0, n - 1);
        Matriz result = segTree.query(1, 2, 4, 0, n - 1);
        
        CHECK(result.print_string() == "1 0 0 1 ");
    }

    SUBCASE("1.5 - Teste da Função query depois de um update") {
        int n = 5;
        SegTree segTree(n);
        segTree.build(1, 0, n - 1);

        Matriz novaMatriz(8, 50, 100, 75);
        segTree.update(3, novaMatriz, 1, 0, n - 1);

        Matriz result = segTree.query(1, 2, 4, 0, n - 1);
        
        CHECK(result.print_string() == "8 50 100 75 ");
    }

    SUBCASE("1.5 - Teste da Função multiplicar") {
        Matriz a(2, 1, 1, 3);
        Matriz b(1, 2, 3, 1);
        SegTree segTree(1);
        Matriz result = segTree.multiplicar(a, b);
        
        CHECK(result.print_string() == "5 5 10 5 ");
    }
}
