#include "batalha.h"
#include "raylib.h"
#include <stdio.h>
#include "structEstandes.h"
#include "gerenciamentoDeDeck.h"
#include <string.h>

/**
 * @brief Adiciona uma carta ao deck do jogador ou do bot.
 *
 * @param deck Array representando o deck do jogador ou do bot.
 * @param carta Carta a ser adicionada ao deck.
 * @param tamanho Tamanho máximo do deck.
 */
void adicionaCartaAoDeck(Estande deck[], Estande carta, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (deck[i].nome[0] == '\0') { // Encontra um slot vazio no deck
            deck[i] = carta; // Adiciona a carta ao deck
            return;
        }
    }
} // Fim da função adicionaCartaAoDeck

/**
 * @brief Realiza a batalha entre a carta do jogador e a do bot.
 *
 * @param maoJogador Carta escolhida pelo jogador.
 * @param maoBot Carta escolhida pelo bot.
 * @param deckPlayer Deck do jogador.
 * @param deckBot Deck do bot.
 * @param tamanho Tamanho máximo dos decks.
 * @param pontuacaoPlayer Pontuação do jogador.
 * @param pontuacaoBot Pontuação do bot.
 * @param atributoPlayer Atributo escolhido pelo jogador para a batalha.
 * @param atributoBot Atributo da carta do bot para a batalha.
 * @param ganhador Variável para armazenar o vencedor da rodada (1 = jogador, 2 = bot, 3 = empate).
 */
void batalha(Estande maoJogador, Estande maoBot, Estande deckPlayer[], Estande deckBot[], int tamanho, int *pontuacaoPlayer, int *pontuacaoBot, int atributoPlayer, int atributoBot, int *ganhador) {
    printf("Atributo jogador: %d\n", atributoPlayer);
    printf("Atributo bot: %d\n", atributoBot);
    
    if (atributoPlayer > atributoBot) {
        *ganhador = 1;
        printf("Jogador venceu a batalha\n");
        (*pontuacaoPlayer)++;
        for (int i = 0; i < tamanho; i++) {
            if (deckBot[i].nome[0] != '\0' && strcmp(deckBot[i].nome, maoBot.nome) == 0) {
                adicionaCartaAoDeck(deckPlayer, deckBot[i], tamanho);
                memset(&deckBot[i], 0, sizeof(deckBot[i])); 
                break;
            }
        }
    } 
    else if (atributoPlayer < atributoBot) {
        *ganhador = 2;
        printf("Bot venceu a batalha\n");
        (*pontuacaoBot)++;
        for (int i = 0; i < tamanho; i++) {
            if (deckPlayer[i].nome[0] != '\0' && strcmp(deckPlayer[i].nome, maoJogador.nome) == 0) {
                adicionaCartaAoDeck(deckBot, deckPlayer[i], tamanho);
                memset(&deckPlayer[i], 0, sizeof(deckPlayer[i])); 
                break;
            }
        }
    } 
    else {
        *ganhador = 3;
        printf("Empate\n");
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
} // Fim da função batalha

/**
 * @brief Verifica se o bot venceu (se o deck do jogador está vazio).
 *
 * @param deckPlayer Deck do jogador.
 * @return true Se o bot venceu.
 * @return false Se o jogador ainda tem cartas.
 */
bool verificaVitoriaBot(Estande deckPlayer[]) {
    for(int i = 0; i < 32; i++) {
        if(deckPlayer[i].nome[0] != '\0') {
            return false;
        }
    }
    return true;
} // Fim da função verificaVitoriaBot

/**
 * @brief Verifica se o jogador venceu (se o deck do bot está vazio).
 *
 * @param deckBot Deck do bot.
 * @return true Se o jogador venceu.
 * @return false Se o bot ainda tem cartas.
 */
bool verificaVitoriaPlayer(Estande deckBot[]) {
    for(int i = 0; i < 32; i++) {
        if(deckBot[i].nome[0] != '\0') {
            return false;
        }
    }
    return true;
} // Fim da função verificaVitoriaPlayer

/**
 * @brief Exibe a imagem do vencedor da batalha na tela.
 *
 * @param ganhador Identificador do vencedor (1 = jogador, 2 = bot, 3 = empate).
 * @param vitoria Textura exibida em caso de vitória do jogador.
 * @param derrota Textura exibida em caso de derrota do jogador.
 * @param empate Textura exibida em caso de empate.
 */
void exibeGanhador(int ganhador, Texture2D vitoria, Texture2D derrota, Texture2D empate) {
    if (ganhador == 1) {
        DrawTexturePro(vitoria, (Rectangle){0, 0, vitoria.width, vitoria.height}, (Rectangle){250, 115, 300, 300}, (Vector2){0, 0}, 0.0f, WHITE);
    } 
    else if (ganhador == 2) {
        DrawTexturePro(derrota, (Rectangle){0, 0, derrota.width, derrota.height}, (Rectangle){250, 115, 300, 300}, (Vector2){0, 0}, 0.0f, WHITE);
    } 
    else {
        DrawTexturePro(empate, (Rectangle){0, 0, empate.width, empate.height}, (Rectangle){250, 115, 300, 300}, (Vector2){0, 0}, 0.0f, WHITE);
    }
} // Fim da função exibeGanhador
