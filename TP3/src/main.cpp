#include <iostream>
#include <chrono>

#include "../include/segTree.hpp"

const bool TIME = false;

int main() {
  // Obtenha o tempo de início
  auto start_time = std::chrono::high_resolution_clock::now();

  // n -> num de instantes de tempo
  // q -> num de operações que serão realizadas
  int n, q;
  std::cin >> n >> q;

  SegTree segTree(n);
  segTree.build(1, 0, n - 1);

  for (int i = 0; i < q; i++) {
    char opcao;
    std::cin >> opcao;

    // Atualização:
    if (opcao == 'u') {
      // Instante de tempo que deve ser alterado:
      int indice;
      std::cin >> indice;

      if (indice < 0) {
        throw std::invalid_argument("Índice inválido. O índice deve ser positivo.");
      }

      if (indice >= n) {
        throw std::invalid_argument("Índice inválido. O índice deve ser menor que o número total de instantes de tempo.");
      }

      // Nova matriz:
      long long a, b, c, d;
      std::cin >> a >> b >> c >> d;

      Matriz matriz(a, b, c, d);

      segTree.update(indice, matriz, 1, 0, n - 1);
    }

    // Consulta:
    else if (opcao == 'q') {

      // t0 -> instante de nascimento do ponto
      // td -> instante de morte do ponto
      // x, y -> coordenadas

      int t0, td, x, y;
      std::cin >> t0 >> td >> x >> y;

      if (t0 < 0 || t0 >= n || td < 0 || td >= n || x < 0 || y < 0) {
        throw std::invalid_argument("Intervalo de instantes de tempo ou coordenadas do ponto inválido.");
      }

      Matriz matriz = segTree.query(1, t0, td, 0, n - 1);

      long long novo_x = (matriz.dado[0][0] * x + matriz.dado[0][1] * y) % (int)(1e8);
      long long novo_y = (matriz.dado[1][0] * x + matriz.dado[1][1] * y) % (int)(1e8);

      std::cout << novo_x << " " << novo_y << std::endl;
    } 
    else {
      throw std::invalid_argument("Operação inválida. Opções: 'u' -> atualização ,  'q' -> consulta");
    }
  }

  if(TIME){
    // Obtenha o tempo de término
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;
    std::cout << n << ", " << q << ", " << elapsed_time.count() << std::endl;
  }
  
  return 0;
}

