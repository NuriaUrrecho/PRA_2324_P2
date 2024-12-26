#include <iostream>
#include <limits>
#include <algorithm>


int* cambio(const int* monedas, int N, int M, int& totalMonedas){
	//Creación de la matriz
	int** dp= new int*[N];
	for(int i = 0; i <N; i++){
		dp[i] = new int[M+1];
	}
	
	//Rellenar la tabla en su primera columna con 0, primera fila y resto con numeros enormes
	for(int i = 0; i <N; i++){
                for(int j = 0; j<= M; j++){
			if(j == 0){
				dp[i][j]= 0; //Si el cambio es 0, hacen falta 0 monedas
			}else if(i == 0){ //Rellenamos la primera fila con el valor de la primera moneda, si es divisible y si no con un valor muy alto
				dp[i][j] =(j % monedas[0]==0) ? j/ monedas[0]: std::numeric_limits<int>::max();
        
			}else{ //El resto de posiciones numeros enormes
				dp[i][j] = std::numeric_limits<int>::max();
			}

		}
	}


	// Rellenar la tabla con las combinaciones de las monedas
	for(int i = 1; i <N; i++){
                for(int j = 0; j<= M; j++){
			dp[i][j] = dp[i-1][j]; // Siempre hereda la combinación de arriba
			if(j>= monedas[i] && dp[i][j - monedas[i]] != std::numeric_limits<int>::max()){
				dp[i][j]= std::min(dp[i][j], 1+ dp[i][j-monedas[i]]); // Calcula el minimo entre lo que tiene
										      // (combi de fila de arriba) o usando 
										      // la moneda nueva y se queda con la me
										      // jor combinación. (siempre que los va
										      // lores anteriores sean validoa).
			}
		}
	}


	// Si el ultimo valor sigue siendo enorme, el problema no tiene solución, pone el numero a -1 y elimina la tabla para prevenir memory leaks
	if(dp[N-1][M] == std::numeric_limits<int>::max()){
		totalMonedas = -1;
		for (int i = 0; i < N; i++) delete[] dp[i];
		delete[] dp;

	}

	//Calcular el vector solución
	
	int* solucion = new int[N]();
	totalMonedas = dp[N-1][M];
	int i = N-1;
	int j = M;
	while (j > 0 && i >= 0) {
        	if (i == 0 || dp[i][j] != dp[i - 1][j]) {
            		solucion[i]++;
            		j -= monedas[i];
        	} else {
            		i--;
        	}
    	}


	// Liberar memoria
	for (int i = 0; i < N; i++) delete[] dp[i];
	delete[] dp;

	// Devolver el puntero que apunta al vector solución
    	return solucion;
}


	


int main() {
    int monedas[] = {1, 4, 6};
    int N = 3; // Número de tipos de monedas
    int M = 8; // Cantidad a devolver
    int totalMonedas = 0;

    int* solucion = cambio(monedas, N, M, totalMonedas);

    if (solucion) {
        std::cout << "Número total de monedas necesarias: " << totalMonedas << "\n";
        std::cout << "Vector solución:\n";
        for (int i = 0; i < N; i++) {
            std::cout << "Monedas de " << monedas[i] << ": " << solucion[i] << "\n";
        }
        delete[] solucion; // Liberar memoria dinámica
    } else {
        std::cout << "No es posible devolver el cambio con las monedas dadas.\n";
    }

    return 0;
}