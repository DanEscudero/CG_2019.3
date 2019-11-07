#include <iostream>
#include<cmath>
#include<array>
#include<cstdio>

#define PI 3.14159265

using namespace std;


class mat33 {
public:
    mat33();  // Construtor
    ~mat33();  // Destrutor

    // Ponteiro publico para os elementos da matrix
    const float *mptr;

    // Principais metodos
    void identity();  // Carrega a matriz identidade
    void rotate(int degrees); // Multiplica a esquerda por uma matriz de rotacao
    void translate(float dx, float dy); // Multiplica a esquerda por uma matriz de translacao
    void scale(float sx, float sy); // Multiplica a esquerda por uma matriz de escala
    void print();  // Imprime no console a matriz atual

private:
    array <float, 9> m;  // Matriz (vetor) principal
    array <float, 9> maux; // Matriz (vetor) auxiliar
};
