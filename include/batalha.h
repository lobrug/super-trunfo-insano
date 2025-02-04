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

void batalhaPoder(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho, int *pontuacaoPlayer, int *pontuacaoBot) {
    if (maoJogador.poderDestrutivo > maoBot.poderDestrutivo) {
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
    } else if(maoJogador.poderDestrutivo < maoBot.poderDestrutivo){
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
    } else {
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


void batalhaVelocidade(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho, int *pontuacaoPlayer, int *pontuacaoBot) {
    if (maoJogador.velocidade > maoBot.velocidade) {
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
    } else if(maoJogador.velocidade < maoBot.velocidade){
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
    } else {
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


void batalhaAlcance(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho, int *pontuacaoPlayer, int *pontuacaoBot) {
    if (maoJogador.alcance > maoBot.alcance) {
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
    } else if (maoJogador.alcance < maoBot.alcance) {
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
    } else {
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


void batalhaPersistencia(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho, int *pontuacaoPlayer, int *pontuacaoBot) {
    if (maoJogador.persistenciaDePoder > maoBot.persistenciaDePoder) {
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
    } else if (maoJogador.persistenciaDePoder < maoBot.persistenciaDePoder) {
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
    } else {
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

void listarCartaJogadorBotVerso(Estande player){
    if (player.super == 0) DrawRectangle(150, 150, 200, 300, LIGHTGRAY); // Card rectangle
    if (player.super == 1) DrawRectangle(150, 150, 200, 300, GOLD);

    DrawRectangle(163, 158, 174, 142, BLACK);
    DrawTexture(player.foto, 163, 158, WHITE);

    
}

void revelarCarta(Estande bot){
    if (bot.super == 0) DrawRectangle(450, 150, 200, 300, LIGHTGRAY); // Card rectangle
    if (bot.super == 1) DrawRectangle(450, 150, 200, 300, GOLD);

    DrawRectangle(463, 158, 174, 142, BLACK);
    DrawTexture(bot.foto, 463, 158, WHITE);
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