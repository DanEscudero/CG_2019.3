#ifndef MAT33_H
#define MAT33_H

#include<cmath>
#include<array>
#include<cstdio>
#include "mat33.hpp"


#define PI 3.14159265

using namespace std;

void mat33::identity() {
    m = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    mptr = m.data();
}

void mat33::rotate(int degrees) {
    float rads = degrees*PI/180;
    float c = cos(rads);
    float s = sin(rads);
    maux = { c * m[0] - s * m[3],  c * m[1] - s * m[4], c * m[2] - s * m[5],
             s * m[0] + c * m[3],  s * m[1] + c * m[4], s * m[2] + c * m[5],
             m[6],                 m[7],                m[8]
        };
    m=maux;
}

void mat33::translate(float dx, float dy) { // Multiplica a esquerda por uma matriz de translacao
    maux = {
        m[0] + dx * m[6], m[1] + dx * m[7], m[2] + dx * m[8]
        m[3] + dy * m[6], m[4] + dy * m[7], m[5] + dy * m[8]
        m[6],             m[7],             m[8]
    };
    m = maux
}

void mat33::scale(float sx, float sy) { // Multiplica a esquerda por uma matriz de escala
    maux = { m[0] * sx, m[1],      m[2],
             m[3],      m[4] * sy, m[5]
             m[6],      m[7],      m[8]
    };
    m = maux
}



void mat33::print() {
    printf("%4.1f %4.1f %4.1f\n", m[0], m[1], m[2]);
    printf("%4.1f %4.1f %4.1f\n", m[3], m[4], m[5]);
    printf("%4.1f %4.1f %4.1f\n", m[6], m[7], m[8]);
}


mat33::mat33() {  // construtor
    identity();
}

mat33::~mat33() {
    //destrutor
}


#endif // MAT33_H
