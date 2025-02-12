/**
 * @file botInteligencia.c
 * @brief Implementa a lógica de decisão do bot para a escolha de atributos na batalha.
 */

 #include "botInteligencia.h"
 #include "raylib.h"
 #include "gerenciamentoDeDeck.h"
 #include "batalha.h"
 #include <stdio.h>
 #include <string.h>
 
 /**
  * @brief Determina qual atributo da carta do bot tem o maior valor.
  * 
  * @param maoBot Estrutura representando a carta do bot.
  * @return int Índice do atributo escolhido (0 - poder, 1 - velocidade, 2 - alcance, 3 - persistência).
  */
 int botEscolha(Estande maoBot) {
     int maiorValor = maoBot.poderDestrutivo;
     int escolha = 0; // 0 - poder // 1 - velocidade // 2 - alcance // 3 - persistência
 
     if (maoBot.velocidade > maiorValor) {
         maiorValor = maoBot.velocidade;
         escolha = 1;
     }
 
     if (maoBot.alcance > maiorValor) {
         maiorValor = maoBot.alcance;
         escolha = 2;
     }
 
     if (maoBot.persistenciaDePoder > maiorValor) {
         maiorValor = maoBot.persistenciaDePoder;
         escolha = 3;
     }
 
     return escolha;
 } // Fim da função botEscolha
 
 /**
  * @brief Define a ação do bot na batalha, escolhendo o melhor atributo e chamando a função de batalha.
  * 
  * @param maoBot Carta do bot na batalha.
  * @param maoPlayer Carta do jogador na batalha.
  * @param deckBot Deck do bot.
  * @param deckPlayer Deck do jogador.
  * @param pontuacaoPlayer Ponteiro para a pontuação do jogador.
  * @param pontuacaoBot Ponteiro para a pontuação do bot.
  * @param escolha_string String para armazenar o nome do atributo escolhido.
  * @param ganhador Ponteiro para armazenar o resultado da batalha (1 - jogador, 2 - bot, 3 - empate).
  */
 void botAcao(Estande maoBot, Estande maoPlayer, Estande deckBot[], Estande deckPlayer[], int *pontuacaoPlayer, int *pontuacaoBot, char escolha_string[], int *ganhador) {
     int escolha = botEscolha(maoBot);
 
     if (escolha == 0) {
         printf("Bot escolheu poder\n");
         batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.poderDestrutivo, maoBot.poderDestrutivo, ganhador);
         strcpy(escolha_string, "PODER");
         return;
     }
 
     if (escolha == 1) {
         printf("Bot escolheu velocidade\n");
         batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.velocidade, maoBot.velocidade, ganhador);
         strcpy(escolha_string, "VELOCIDADE");
         return;
     }
 
     if (escolha == 2) {
         printf("Bot escolheu alcance\n");
         batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.alcance, maoBot.alcance, ganhador);
         strcpy(escolha_string, "ALCANCE");
         return;
     }
 
     if (escolha == 3) {
         printf("Bot escolheu persistência\n");
         batalha(maoPlayer, maoBot, deckPlayer, deckBot, 32, pontuacaoPlayer, pontuacaoBot, maoPlayer.persistenciaDePoder, maoBot.persistenciaDePoder, ganhador);
         strcpy(escolha_string, "PERSISTÊNCIA");
         return;
     }
 } // Fim da função botAcao