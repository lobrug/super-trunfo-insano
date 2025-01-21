#include "raylib.h"
#include "gerenciamentoDeDeck.h"
#include "batalha.h"
#include <stdio.h>

int botEscolha(Estande maoBot){
    int maiorValor = 0; // 0 - poder // 1 - velocidade // 2 - alcance // 3 - persistencia

    if(maoBot.velocidade > maiorValor){
        maiorValor = 1;
    }

    if(maoBot.alcance > maiorValor){
        maiorValor = 2;
    }

    if(maoBot.persistenciaDePoder > maiorValor){
        maiorValor = 3;
    }

    return maiorValor;
}

void botAcao(Estande maoBot, Estande maoPlayer, Estande deckBot[], Estande deckPlayer[]){
    int escolha = botEscolha(maoBot);

    switch (escolha){

    case 0:
        batalhaPoder(maoPlayer, maoBot, deckPlayer, deckBot);
        break;

    case 1:
        batalhaVelocidade(maoPlayer, maoBot, deckPlayer, deckBot);
        break;

    case 2: 
        batalhaAlcance(maoPlayer, maoBot, deckPlayer, deckBot);
        break;
    
    case 3:
        batalhaPersistencia(maoPlayer, maoBot, deckPlayer, deckBot);
        break;
    
    default:
        break;
    }
}