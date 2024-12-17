#include "lib/structEstandes.h"
#include "lib/embaralhar.h"
#include "lib/pesquisaDeCartas.h"
#include "lib/leituraCsv.h"
#include "lib/gerenciamentoDeDeck.h"
#include "lib/menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO 32
#define SIZEDECK 16


int main(){
    Estande estandes[32];
    Estande* deck;
    Estande* deck2;

    FILE *leitorBinario = fopen("../bin/deck_ultima_partida.dat", "rb");
    if (leitorBinario == NULL)
    {
        leituraArquivoCsv(estandes);
        fclose(leitorBinario);
    }else{
        fread(estandes, sizeof(Estande), 32, leitorBinario);
        fclose(leitorBinario);
    }//Verificação da existencia de um arquivo binário com os dados da ultima partida salvos

    deck = (Estande*) malloc(SIZEDECK * sizeof(Estande));
    deck2 = (Estande*) malloc(SIZEDECK * sizeof(Estande));

    embaralharDecks(deck, deck2, estandes);

    menuInicial(deck, deck2);

    for (int i = 0, j = 0; i < 32; i++)
    {
        if (i < 16)
        {
            estandes[i] = deck[i];
        }else
        {
            estandes[i] = deck2[j];
            j++;
        }
        
    }//Armazena em estandes o deck completo e

    armazenaDeckFinal(estandes);
    free(deck);
    free(deck2);

    /*
    LEMBRAR DE MOVER A MAIN
    PARA
    SOURCES
    */

   return 0;
}