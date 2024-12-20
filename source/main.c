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

/**
 * @brief Função principal do programa.
 * 
 * Realiza a inicialização dos decks de cartas, lê dados de um arquivo binário (se existente),
 * embaralha os decks, chama o menu principal e armazena o estado final das cartas ao encerrar.
 * 
 * @return int Retorna 0 ao final da execução.
 */
int main() {
    Estande estandes[TAMANHO]; ///< Array contendo todos os estandes.
    Estande* deck;            ///< Ponteiro para o primeiro deck (deck 1).
    Estande* deck2;           ///< Ponteiro para o segundo deck (deck 2).

    // Verifica se existe um arquivo binário com o estado salvo da última partida.
    FILE *leitorBinario = fopen("bin/deck_ultima_partida.dat", "rb");
    if (leitorBinario == NULL) {
        // Caso o arquivo binário não exista, os dados são lidos do arquivo CSV.
        leituraArquivoCsv(estandes);
        fclose(leitorBinario);
    } else {
        // Caso o arquivo binário exista, os dados são carregados diretamente dele.
        fread(estandes, sizeof(Estande), TAMANHO, leitorBinario);
        fclose(leitorBinario);
    }

    // Aloca memória dinâmica para os dois decks de cartas.
    deck = (Estande*) malloc(SIZEDECK * sizeof(Estande));
    deck2 = (Estande*) malloc(SIZEDECK * sizeof(Estande));

    // Embaralha os estandes para preencher os dois decks.
    embaralharDecks(deck, deck2, estandes);

    // Inicia o menu principal do programa.
    menuInicial(deck, deck2);

    // Atualiza o array `estandes` com os estandes dos dois decks após a execução.
    for (int i = 0, j = 0; i < TAMANHO; i++) {
        if (i < SIZEDECK) {
            estandes[i] = deck[i];
        } else {
            estandes[i] = deck2[j];
            j++;
        }
    }

    // Salva o estado final dos estandes em um arquivo binário.
    armazenaDeckFinal(estandes);

    // Libera a memória alocada para os decks.
    free(deck);
    free(deck2);

    /*
    LEMBRAR DE MOVER A MAIN
    PARA
    SOURCES
    */

    return 0;
} // Fim da função main.
