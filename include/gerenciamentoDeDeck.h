#ifndef gerenciamentoDeDeck_H
#define gerenciamentoDeDeck_H

#include "gerenciamentoDeDeck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "structEstandes.h"
#include "raylib.h"
#include "manipulacaoCartas.h"

void listarCartaNoGerenciamento(Estande estande, Texture2D *Carta, Texture2D fundoCarta, bool *blockCarta, Font fonte, int posX, int posY);

void verificaCheckFiltro(bool* check, int filtro[], int posX, int posY1, int posY2, int largura, int altura, bool* editMin, bool* editMax, bool edit[]);

void armazenaDeckFinal(Estande estandes[]);

Estande recebeCartaParaMao(Estande deck[]);

int VerificadorFiltro(char Letra, int poder[], int velocidade[], int alcance[], int persistencia[], int numero, Estande estandes);

void DrawCenteredTextEx(Font font, const char *text, Vector2 centerPos, float fontSize, float spacing, Color color);

#endif