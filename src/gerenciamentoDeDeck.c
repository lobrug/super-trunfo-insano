#include "gerenciamentoDeDeck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "structEstandes.h"
#include "pesquisaDeCartas.h"

/**
 * @file gerenciamentoDeCartas.c
 * @brief Implementa funcionalidades para gerenciar cartas de um deck.
 * 
 * Este arquivo contém as funções necessárias para cadastrar, listar, alterar, excluir e pesquisar cartas 
 * no sistema. O objetivo é permitir a manipulação dinâmica das cartas, garantindo flexibilidade no 
 * gerenciamento dos decks.
 */

/**
 * @brief Armazena o deck final em um arquivo binário.
 * 
 * Esta função escreve o conteúdo do vetor de estandes em um 
 * arquivo binário, que representa o deck utilizado na última 
 * partida. O arquivo é salvo em "bin/deck_ultima_partida.dat".
 * 
 * @param estandes Vetor contendo o deck a ser armazenado.
 * 
 * @note O arquivo é sobrescrito toda vez que esta função é chamada.
 */
void armazenaDeckFinal(Estande estandes[]) {
    // Abre o arquivo para escrita em modo binário
    FILE *arq = fopen("bin/deck_ultima_partida.dat", "wb");

    // Grava os dados do vetor no arquivo
    fwrite(estandes, sizeof(Estande), 32, arq);

    // Fecha o arquivo após a gravação
    fclose(arq);

    return;
} // Fim da função armazenaDeckFinal

Estande recebeCartaParaMao(Estande deck[]) {
    for (int i = 0; i < 32; i++) {
        if (deck[i].nome[0] != '\0') { // Verifica se o slot não está vazio
            Estande carta = deck[i];
            deck[i].nome[0] = '\0'; // Limpa o slot no deck
            return carta;
        }
    }
    printf("Voce nao tem cartas no monte\n");
    return (Estande){{'\0'}}; // Retorna uma carta vazia se não houver cartas no deck
}

void receberCartaAdversario(Estande deck[], Estande mao){
    for(int i = 0; i < 32; i++){
        if(deck[i].nome[0] == '\0'){
            deck[i] = mao;
            memset(&mao, 0, sizeof(Estande));
            return;
        }
    }
    printf("Erro ao receber carta");
}
