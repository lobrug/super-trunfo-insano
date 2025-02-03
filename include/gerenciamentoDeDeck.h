#ifndef gerenciamentoDeDeck_H
#define gerenciamentoDeDeck_H

#include "gerenciamentoDeDeck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "structEstandes.h"
#include "pesquisaDeCartas.h"

/*permitir cadastrar (inserir/listar/pesquisar/alterar/excluir) as cartas disponíveis. Essa
relação deve aumentar e diminuir dinamicamente*/

void armazenaDeckFinal(Estande estandes[]){

    FILE *arq = fopen("deck_ultima_partida.dat", "wb");

    fwrite(estandes, sizeof(Estande), 32, arq);

    fclose(arq);

    return;
}

Estande recebeCartaParaMao(Estande deck[]) {
    for (int i = 0; i < 32; i++) {
        if (deck[i].nome[0] != '\0') { // Verifica se o slot não está vazio
            Estande carta = deck[i]; // Atribui a carta do deck para a mão
            deck[i].nome[0] = '\0';
            return carta;
        }
    }
    printf("Voce nao tem cartas no monte\n");
}


int VerificadorFiltro(char Letra, int poder[], int velocidade[], int alcance[], int persistencia[], int numero, Estande estandes){

    if ((Letra != 'Z') && (Letra != estandes.letra))
    {
        return -1;
    }

    if ((poder[0] != -1) && ((estandes.poderDestrutivo < poder[0]) || (estandes.poderDestrutivo > poder[1])))
    {
        return -1;
    }

    if ((velocidade[0] != -1) && ((estandes.velocidade < velocidade[0]) || (estandes.velocidade > velocidade[1])))
    {
        return -1;
    }
    
    if ((alcance[0] != -1) && ((estandes.alcance < alcance[0]) || (estandes.alcance > alcance[1])))
    {
        return -1;
    }

    if ((persistencia[0] != -1) && ((estandes.persistenciaDePoder < persistencia[0]) || (estandes.persistenciaDePoder > persistencia[1])))
    {
        return -1;
    }
    
    if ((numero != -1) && (numero != estandes.numero))
    {
        return -1;
    }
    
    return 0;
    
}

#endif