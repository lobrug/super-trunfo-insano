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

void batalhaPoder(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho) {
    if (maoJogador.poderDestrutivo > maoBot.poderDestrutivo) {
        // Jogador vence a batalha, a carta do bot é transferida para o deck do jogador
        for (int i = 0; i < tamanho; i++) {
            if (deckBot[i].nome[0] != '\0' && strcmp(deckBot[i].nome, maoBot.nome) == 0) {
                // Adiciona a carta ao deck do jogador
                adicionaCartaAoDeck(deckPlayer, deckBot[i], tamanho);
                // Remove a carta do deck do bot
                memset(&deckBot[i], 0, sizeof(deckBot[i])); 
                break;
            }
        }
    } else {
        // Bot vence a batalha, a carta do jogador é transferida para o deck do bot
        for (int i = 0; i < tamanho; i++) {
            if (deckPlayer[i].nome[0] != '\0' && strcmp(deckPlayer[i].nome, maoJogador.nome) == 0) {
                // Adiciona a carta ao deck do bot
                adicionaCartaAoDeck(deckBot, deckPlayer[i], tamanho);
                // Remove a carta do deck do jogador
                memset(&deckPlayer[i], 0, sizeof(deckPlayer[i])); 
                break;
            }
        }
    }
}


void batalhaVelocidade(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho) {
    if (maoJogador.velocidade > maoBot.velocidade) {
        // Jogador vence a batalha, a carta do bot é transferida para o deck do jogador
        for (int i = 0; i < tamanho; i++) {
            if (deckBot[i].nome[0] != '\0' && strcmp(deckBot[i].nome, maoBot.nome) == 0) {
                // Adiciona a carta ao deck do jogador
                adicionaCartaAoDeck(deckPlayer, deckBot[i], tamanho);
                // Remove a carta do deck do bot
                memset(&deckBot[i], 0, sizeof(deckBot[i])); 
                break;
            }
        }
    } else {
        // Bot vence a batalha, a carta do jogador é transferida para o deck do bot
        for (int i = 0; i < tamanho; i++) {
            if (deckPlayer[i].nome[0] != '\0' && strcmp(deckPlayer[i].nome, maoJogador.nome) == 0) {
                // Adiciona a carta ao deck do bot
                adicionaCartaAoDeck(deckBot, deckPlayer[i], tamanho);
                // Remove a carta do deck do jogador
                memset(&deckPlayer[i], 0, sizeof(deckPlayer[i])); 
                break;
            }
        }
    }
}


void batalhaAlcance(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho) {
    if (maoJogador.alcance > maoBot.alcance) {
        // Jogador vence a batalha, a carta do bot é transferida para o deck do jogador
        for (int i = 0; i < tamanho; i++) {
            if (deckBot[i].nome[0] != '\0' && strcmp(deckBot[i].nome, maoBot.nome) == 0) {
                // Adiciona a carta ao deck do jogador
                adicionaCartaAoDeck(deckPlayer, deckBot[i], tamanho);
                // Remove a carta do deck do bot
                memset(&deckBot[i], 0, sizeof(deckBot[i])); 
                break;
            }
        }
    } else {
        // Bot vence a batalha, a carta do jogador é transferida para o deck do bot
        for (int i = 0; i < tamanho; i++) {
            if (deckPlayer[i].nome[0] != '\0' && strcmp(deckPlayer[i].nome, maoJogador.nome) == 0) {
                // Adiciona a carta ao deck do bot
                adicionaCartaAoDeck(deckBot, deckPlayer[i], tamanho);
                // Remove a carta do deck do jogador
                memset(&deckPlayer[i], 0, sizeof(deckPlayer[i])); 
                break;
            }
        }
    }
}


void batalhaPersistencia(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho) {
    if (maoJogador.persistenciaDePoder > maoBot.persistenciaDePoder) {
        // Jogador vence a batalha, a carta do bot é transferida para o deck do jogador
        for (int i = 0; i < tamanho; i++) {
            if (deckBot[i].nome[0] != '\0' && strcmp(deckBot[i].nome, maoBot.nome) == 0) {
                // Adiciona a carta ao deck do jogador
                adicionaCartaAoDeck(deckPlayer, deckBot[i], tamanho);
                // Remove a carta do deck do bot
                memset(&deckBot[i], 0, sizeof(deckBot[i])); 
                break;
            }
        }
    } else {
        // Bot vence a batalha, a carta do jogador é transferida para o deck do bot
        for (int i = 0; i < tamanho; i++) {
            if (deckPlayer[i].nome[0] != '\0' && strcmp(deckPlayer[i].nome, maoJogador.nome) == 0) {
                // Adiciona a carta ao deck do bot
                adicionaCartaAoDeck(deckBot, deckPlayer[i], tamanho);
                // Remove a carta do deck do jogador
                memset(&deckPlayer[i], 0, sizeof(deckPlayer[i])); 
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