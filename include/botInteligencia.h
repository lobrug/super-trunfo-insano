#ifndef BOTINTELIGENCIA_H
#define BOTINTELIGENCIA_H

#include "raylib.h"
#include "gerenciamentoDeDeck.h"
#include "batalha.h"
#include <stdio.h>

int botEscolha(Estande maoBot){
    int maiorValor = maoBot.poderDestrutivo; // 0 - poder // 1 - velocidade // 2 - alcance // 3 - persistencia

    if(maoBot.velocidade > maiorValor){
        maiorValor = maoBot.velocidade;
    }

    if(maoBot.alcance > maiorValor){
        maiorValor = maoBot.alcance;
    }

    if(maoBot.persistenciaDePoder > maiorValor){
        maiorValor = maoBot.persistenciaDePoder;
    }

    return maiorValor;
}

void botAcao(Estande maoBot, Estande maoPlayer, Estande deckBot[], Estande deckPlayer[]){
    int escolha = botEscolha(maoBot);

    if(escolha == maoBot.poderDestrutivo){
        batalhaPoder(maoPlayer, maoBot, deckPlayer, deckBot);
    }

    if(escolha == maoBot.velocidade){
        batalhaVelocidade(maoPlayer, maoBot, deckPlayer, deckBot);
    }

    if(escolha == maoBot.alcance){
        batalhaAlcance(maoPlayer, maoBot, deckPlayer, deckBot);
    }

    if(escolha == maoBot.persistenciaDePoder){
        batalhaPersistencia(maoPlayer, maoBot, deckPlayer, deckBot);
    }
}

#endif BOTINTELIGENCIA_H