#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structEstandes.h"

void leituraArquivoCsv(Estande estandes[]){
    FILE *infocartas = fopen("cartas_stands.csv", "r");

    if(infocartas == NULL){
        printf("Falha ao abrir arquivo\n");
        return;
    }

    char linha[100];
    fgets(linha, sizeof(linha), infocartas);
    int i = 0;

    /*
    A seguinte função esta incompleta, é necessario achar alguma solução
    para criação das habilidades e leitura delas.
    Eu tive uma ideia de um enum de habilidades, e repassar os valores do enum para o
    csv em vez de usar os nomes das habilidades
    */
   fscanf(infocartas, "%*[^\n]\n");
    while (fscanf(infocartas, "%c,%d,%49[^,],%d,%d,%d,%d,%d,%d\n",
                  &estandes[i].letra, 
                  &estandes[i].numero, 
                  estandes[i].nome, 
                  &estandes[i].super, 
                  &estandes[i].poderDestrutivo, 
                  &estandes[i].velocidade, 
                  &estandes[i].alcance, 
                  &estandes[i].persistenciaDePoder,
                  &estandes[i].verificacao
                  )){
        i++;
        if (i >= 32) break;
    }

    fclose(infocartas);
    return;
}