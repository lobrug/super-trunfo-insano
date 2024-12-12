#include "../structEstandes.h"
#include "../embaralhar.h"
#include "../pesquisaDeCartas.h"
#include "../leituraCsv.h"
#include "../gerenciamentoDeDeck.h"
#include "../menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO 32
#define SIZEDECK 16

/*
void lerString(char* texto, int tamanho){
    setbuf(stdin, NULL);
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}
*/

int main(){
    Estande estandes[32];
    Estande* deck;
    Estande* deck2;

    FILE *verificaBinario = fopen("deck_ultima_partida.dat", "ab");
    if (verificaBinario == NULL)
    {
        leituraArquivoCsv(estandes);
    }else{
        fclose(verificaBinario);
        FILE *leitorBinario = fopen("deck_ultima_partida.dat", "rb");
        fread(estandes, sizeof(Estande), 32, leitorBinario);
        fclose(leitorBinario);
    }

    deck = (Estande*) malloc(SIZEDECK * sizeof(Estande));
    deck2 = (Estande*) malloc(SIZEDECK * sizeof(Estande));

    embaralharDecks(deck, deck2, estandes);

    for (int i = 0; i < 16; i++)
    {
        listarCarta(deck[i]);
    }
    for (int i = 0; i < 16; i++)
    {
        listarCarta(deck2[i]);
    }


    /*
    LEMBRAR DE MOVER A MAIN
    PARA
    SOURCES
    */

   return 0;
}