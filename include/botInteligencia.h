#ifndef BOTINTELIGENCIA_H
#define BOTINTELIGENCIA_H

#include "raylib.h"
#include "gerenciamentoDeDeck.h"
#include "batalha.h"
#include <stdio.h>

int botEscolha(Estande maoBot){
    int maiorValor = maoBot.poderDestrutivo;
    int escolha = 0; // 0 - poder // 1 - velocidade // 2 - alcance // 3 - persistencia

    if(maoBot.velocidade > maiorValor){
        maiorValor = maoBot.velocidade;
        escolha = 1;
    }

    if(maoBot.alcance > maiorValor){
        maiorValor = maoBot.alcance;
        escolha = 2;
    }

    if(maoBot.persistenciaDePoder > maiorValor){
        maiorValor = maoBot.persistenciaDePoder;
        escolha = 3;
    }

    return escolha;
}

void botAcao(Estande maoBot, Estande maoPlayer, Estande deckBot[], Estande deckPlayer[], int *pontuacaoPlayer, int *pontuacaoBot){
    int escolha = botEscolha(maoBot);

    if(escolha == 0){
        batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.poderDestrutivo, maoBot.poderDestrutivo);
        return;
    }

    if(escolha == 1){
        batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.velocidade, maoBot.velocidade);
        return;
    }

    if(escolha == 2){
        batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.alcance, maoBot.alcance);
        return;
    }

    if(escolha == 3){
        batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.persistenciaDePoder, maoBot.persistenciaDePoder);
        return;
    }
}

#endif BOTINTELIGENCIA_H