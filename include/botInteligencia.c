#include "botInteligencia.h"
#include "raylib.h"
#include "gerenciamentoDeDeck.h"
#include "batalha.h"
#include <stdio.h>
#include <string.h>

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

void botAcao(Estande maoBot, Estande maoPlayer, Estande deckBot[], Estande deckPlayer[], int *pontuacaoPlayer, int *pontuacaoBot, char escolha_string[], int *ganhador){
    int escolha = botEscolha(maoBot);

    if(escolha == 0){
        printf("Bot escolheu poder\n");
        batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.poderDestrutivo, maoBot.poderDestrutivo, ganhador);
        strcpy(escolha_string, "PODER");
        return;
    }

    if(escolha == 1){
        printf("Bot escolheu velocidade\n");
        batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.velocidade, maoBot.velocidade, ganhador);
        strcpy(escolha_string, "VELOCIDADE");
        return;
    }

    if(escolha == 2){
        printf("Bot escolheu alcance\n");
        batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.alcance, maoBot.alcance, ganhador);
        strcpy(escolha_string, "ALCANCE");
        return;
    }

    if(escolha == 3){
        printf("Bot escolheu persistencia\n");
        batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.persistenciaDePoder, maoBot.persistenciaDePoder, ganhador);
        strcpy(escolha_string, "PERSISTENCIA");
        return;
    }
}