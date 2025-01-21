#ifndef BATALHA_H
#define BATALHA_H

#include "raylib.h"
#include <stdio.h>
#include "structEstandes.h"
#include "gerenciamentoDeDeck.h"

void batalhaPoder(Estande player, Estande bot, Estande deckJogador[], Estande deckBot[]){
    if(player.poderDestrutivo > bot.poderDestrutivo){
        receberCartaAdversario(deckJogador, bot);
        return;
    }

    if(player.poderDestrutivo < bot.poderDestrutivo){
        receberCartaAdversario(deckBot, player);
        return;
    }

    if(player.poderDestrutivo == bot.poderDestrutivo){
        return;
    }
}

void batalhaVelocidade(Estande player, Estande bot, Estande deckJogador[], Estande deckBot[]){
    if(player.velocidade > bot.velocidade){
        receberCartaAdversario(deckJogador, bot);
        return;
    }

    if(player.velocidade < bot.velocidade){
        receberCartaAdversario(deckBot, player);
        return;
    }

    if(player.velocidade == bot.velocidade){
        return;
    }
}

void batalhaAlcance(Estande player, Estande bot, Estande deckJogador[], Estande deckBot[]){
    if(player.alcance > bot.alcance){
        receberCartaAdversario(deckJogador, bot);
        return;
    }

    if(player.alcance < bot.alcance){
        receberCartaAdversario(deckBot, player);
        return;
    }

    if(player.alcance == bot.alcance){
        return;
    }
}

void batalhaPersistencia(Estande player, Estande bot, Estande deckJogador[], Estande deckBot[]){
    if(player.persistenciaDePoder > bot.persistenciaDePoder){
        receberCartaAdversario(deckJogador, bot);
        return;
    }

    if(player.persistenciaDePoder < bot.persistenciaDePoder){
        receberCartaAdversario(deckBot, player);
        return;
    }

    if(player.persistenciaDePoder == bot.persistenciaDePoder){
        return;
    }
}

bool verificaVitoriaBot(Estande deckPlayer[]){
    bool verifica = false;
    for(int i = 0; i < 32; i++){
        if(deckPlayer[i].nome != '\0'){
            return false;
        }
    }
    return true;
}

bool verificaVitoriaPlayer(Estande deckBot[]){
    bool verifica = false;
    for(int i = 0; i < 32; i++){
        if(deckBot[i].nome != '\0'){
            return false;
        }
    }
    return true;
}

#endif BATALHA_H