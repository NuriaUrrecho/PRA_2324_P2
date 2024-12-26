#include <iostream>
#include <vector>
#include <algorithm>



// Hace que la funcion mochila te devuelva un par de datos (i, j[]), donde i es el beneficio y j un vector binarioque te dice si el objeto ha sido incluido o no

std::pair<int, std::vector<int>> mochila(int N, const std::vector<int>& p, const std::vector<int>& b, int M) {
    // Creación de la tabla 
    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(M + 1, 0));

    // Rellenar la tabla
    for (int i = 1; i <= N; i++) {
        for (int C = 0; C <= M; C++) {
            if (p[i - 1] > C) {
                dp[i][C] = dp[i - 1][C]; // No incluir el objeto
            } else {
                dp[i][C] = std::max(dp[i - 1][C], b[i - 1] + dp[i - 1][C - p[i - 1]]);
            }
        }
    }

    // Vamos a l¡calcular el vector solucion
    std::vector<int> x(N, 0); // Inicializar el vector
    int C = M, i = N;
    while (i > 0 && C > 0) {
        if (dp[i][C] != dp[i - 1][C]) {
            x[i - 1] = 1; // Incluir el objeto
            C -= p[i - 1]; // Reducir la capacidad
        }
        i--;
    }

    // Retornar el máximo beneficio y el vector solución
    return {dp[N][M], x};
}

int main() {
    int N = 4; // Número de objetos
    std::vector<int> p = {1,3,2,4 }; // Pesos
    std::vector<int> b = {10,20,15,20}; // Beneficios
    int M = 5; // Capacidad máxima

    auto [maxBeneficio, solucion] = mochila(N, p, b, M);

    std::cout << "Máximo beneficio: " << maxBeneficio << "\n";
    std::cout << "Vector solución: ";
    for (int xi : solucion) {
        std::cout << xi << " ";
    }
    std::cout << "\n";

    return 0;
}