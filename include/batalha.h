#ifndef BATALHA_H
#define BATALHA_H

#include "raylib.h"
#include <stdio.h>
#include "structEstandes.h"
#include "gerenciamentoDeDeck.h"
#include <string.h>

void adicionaCartaAoDeck(Estande deck[], Estande carta, int tamanho);

void batalha(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho, int *pontuacaoPlayer, int *pontuacaoBot, int atributoPlayer, int atributoBot, int *ganhador);

bool verificaVitoriaBot(Estande deckPlayer[]);

bool verificaVitoriaPlayer(Estande deckBot[]);

void exibeGanhador(int ganhador, Texture2D vitoria, Texture2D derrota, Texture2D empate);


#endif 