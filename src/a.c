#include <stdio.h>
#include <stdlib.h>
#include "structEstandes.h"
#include "leituraCsv.h"


int main(){

Estande estandes[32];

leituraArquivoCsv(estandes);

for(int i = 0; i < 32; i++){
    printf("Nome: %s\n", estandes[i].nome);
    printf("id: %c%d\n", estandes[i].letra, estandes[i].numero);
    if(estandes[i].super == true){
        printf("Esta carta é o super trunfo\n");
    }
    printf("-----ATRIBUTOS-----\n");
    printf("Poder destrutivo: %d\n", estandes[i].poderDestrutivo);
    printf("Velocidade: %d\n", estandes[i].velocidade);
    printf("Alcance: %d\n", estandes[i].alcance);
    printf("Persistencia: %d\n", estandes[i].persistenciaDePoder);
    printf("\n");
}



}