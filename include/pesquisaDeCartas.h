#ifndef pesquisaDeCartas_H
#define pesquisaDeCartas_H

#include "pesquisaDeCartas.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "structEstandes.h"
#include "raylib.h"
#include "manipulacaoCartas.h"

void lerString(char* texto, int tamanho){
    setbuf(stdin, NULL);
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}

void listarCartaNoGerenciamento(Estande estande, Texture2D *Carta, Texture2D fundoCarta, bool *blockCarta, Font fonte, int posX, int posY){

    if (*blockCarta == false)
    {
        if(estande.super ==1){

            *Carta = carregaCarta('G');
        }else{
            *Carta = carregaCarta(estande.letra);
        }

        *blockCarta = true;
    }
    DrawTexturePro(fundoCarta, (Rectangle){0, 0, fundoCarta.width, fundoCarta.height}, (Rectangle){posX, posY + 57, 250, 166}, (Vector2){0, 0}, 0, WHITE);
    DrawTexture(estande.foto, posX+25, posY+64, WHITE);
    DrawTexture(*Carta, posX, posY, WHITE);

    Color cor;

    if (estande.super == 1)
    {
        cor = GOLD;
        DrawTextEx(fonte, estande.nome, (Vector2){posX + 52, posY + 5}, 17, 0, WHITE);
    }else{
        cor = WHITE;
        DrawTextEx(fonte, estande.nome, (Vector2){posX + 52, posY + 3}, 23, 0, WHITE);
    }

    DrawTextEx(fonte, TextFormat("%d", estande.poderDestrutivo), (Vector2){posX + 123, posY + 274}, 20, 0, cor);
    DrawTextEx(fonte, TextFormat("%d", estande.velocidade), (Vector2){posX + 123, posY + 292}, 20, 0, cor);
    DrawTextEx(fonte, TextFormat("%d", estande.alcance), (Vector2){posX + 123, posY + 309}, 20, 0, cor);
    DrawTextEx(fonte, TextFormat("%d", estande.persistenciaDePoder), (Vector2){posX + 123, posY + 327}, 20, 0, cor);
    DrawTextEx(fonte, TextFormat("%c%d", estande.letra, estande.numero), (Vector2){posX +5, posY - 2}, 33, 0, cor);
    
}

void verificaCheckFiltro(bool* check, int filtro[], int posX, int posY1, int posY2, int largura, int altura, bool* editMin, bool* editMax, bool edit[]){

    if (*check == true){


        if(GuiSpinner((Rectangle){posX,posY1,largura,altura}, "MIN", &filtro[0], 0, 100, *editMin)){
            
            for (int i = 0; i < 9; i++)
            {
                edit[i] = false;
            }
            
            *editMin = true;
        }

        if(GuiSpinner((Rectangle){posX,posY2,largura,altura}, "MAX", &filtro[1], 0, 100, *editMax)){

            for (int i = 0; i < 9; i++)
            {
                edit[i] = false;
            }

            *editMax = true;
        }
                
        if(filtro[0] > filtro[1]){
            filtro[0] = filtro[1];
        }
                    
    }else{
        memset(filtro, -1, sizeof(filtro));
    }
    return;
}

#endif