#ifndef BOTINTELIGENCIA_H
#define BOTINTELIGENCIA_H

#include "raylib.h"
#include "gerenciamentoDeDeck.h"
#include "batalha.h"
#include <stdio.h>
#include <string.h>

int botEscolha(Estande maoBot);

void botAcao(Estande maoBot, Estande maoPlayer, Estande deckBot[], Estande deckPlayer[], int *pontuacaoPlayer, int *pontuacaoBot, char escolha_string[], int *ganhador);

#endif 