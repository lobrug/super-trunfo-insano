#ifndef structEstandes_H
#define structEstandes_H

#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    char nome[30];
    char letra;
    int numero;
    int super;

    //atributos a seguir sao medidos de 0 a 100
    int poderDestrutivo;
    int velocidade;
    int alcance;
    int persistenciaDePoder;
    
}Estande;

#endif