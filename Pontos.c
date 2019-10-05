#include <stdio.h>
#include <stdlib.h>
#include "Pontos.h"


typedef struct Dot{
    float x, y;
}

Ponto createPonto(float x, float y){
    Dot *dot = (Dot*) malloc(sizeof(Dot));
    if(dot != NULL){
        dot.x = x;
        dot.y = y;
    }
    else{
        printf("Erro na alocação da memoria.\n");
    }
    return dot;
}

float getPontoX(Ponto ponto){
    Dot *dot = (Dot *)ponto;
    return dot->x;
}

float getPontoY(Ponto ponto){
    Dot *dot = (Dot *)ponto;
    return dot->Y;
}