#ifndef BATALHA_H
#define BATALHA_H

#include "raylib.h"
#include <stdio.h>
#include "structEstandes.h"
#include "gerenciamentoDeDeck.h"

void adicionaCartaAoDeck(Estande deck[], Estande carta, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (deck[i].nome[0] == '\0') { // Encontra um slot vazio no deck
            deck[i] = carta; // Adiciona a carta ao deck
            return;
        }
    }
}

void batalha(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho, int *pontuacaoPlayer, int *pontuacaoBot, int atributoPlayer, int atributoBot) {
    printf("Atributo jogador: %d\n", atributoPlayer);
    printf("Atributo bot: %d\n", atributoBot);
    if (atributoPlayer > atributoBot) {
        printf("Jogador venceu a batalha\n");
        // Jogador vence a batalha, a carta do bot é transferida para o deck do jogador
        (*pontuacaoPlayer)++;
        for (int i = 0; i < tamanho; i++) {
            if (deckBot[i].nome[0] != '\0' && strcmp(deckBot[i].nome, maoBot.nome) == 0) {
                // Adiciona a carta ao deck do jogador
                adicionaCartaAoDeck(deckPlayer, deckBot[i], tamanho);
                // Remove a carta do deck do bot
                memset(&deckBot[i], 0, sizeof(deckBot[i])); 
                break;
            }
        }
    } if(atributoPlayer < atributoBot){
        printf("Bot venceu a batalha\n");
        // Bot vence a batalha, a carta do jogador é transferida para o deck do bot
        (*pontuacaoBot)++;
        for (int i = 0; i < tamanho; i++) {
            if (deckPlayer[i].nome[0] != '\0' && strcmp(deckPlayer[i].nome, maoJogador.nome) == 0) {
                // Adiciona a carta ao deck do bot
                adicionaCartaAoDeck(deckBot, deckPlayer[i], tamanho);
                // Remove a carta do deck do jogador
                memset(&deckPlayer[i], 0, sizeof(deckPlayer[i])); 
                break;
            }
        }
    } if(atributoPlayer == atributoBot){
        printf("Empate\n");
        for (int i = 0; i < tamanho; i++) {
            if (deckPlayer[i].nome[0] != '\0' && strcmp(deckPlayer[i].nome, maoJogador.nome) == 0) {
                memset(&deckPlayer[i], 0, sizeof(deckPlayer[i]));
                break;
            }
        }
        for (int i = 0; i < tamanho; i++) {
            if (deckBot[i].nome[0] != '\0' && strcmp(deckBot[i].nome, maoBot.nome) == 0) {
                memset(&deckBot[i], 0, sizeof(deckBot[i]));
                break;
            }
        }
    }
}


bool verificaVitoriaBot(Estande deckPlayer[]){
    for(int i = 0; i < 32; i++){
        if(deckPlayer[i].nome[0] != '\0'){
            return false;
        }
    }
    return true;
}

bool verificaVitoriaPlayer(Estande deckBot[]){
    for(int i = 0; i < 32; i++){
        if(deckBot[i].nome[0] != '\0'){
            return false;
        }
    }
    return true;
}


#endif BATALHA_H