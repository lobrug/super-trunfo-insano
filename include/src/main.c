#include "structEstandes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO 32
#define SIZEDECK 16

void lerString(char* texto, int tamanho){
    setbuf(stdin, NULL);
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}

int main(){
    Estande estandes[32];
    Estande* deck;
    Estande* deck2;

    leituraArquivoCsv(estandes);

    deck = (Estande*) malloc(SIZEDECK * sizeof(Estande));
    deck2 = (Estande*) malloc(SIZEDECK * sizeof(Estande));


    /*
    LEMBRAR DE MOVER A MAIN
    PARA
    SOURCES
    */

   return 0;
}