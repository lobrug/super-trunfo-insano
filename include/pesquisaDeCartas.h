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

void listarCartaNoGerenciamento(Estande estande, Texture2D *Carta, bool *blockCarta, Font fonte, int posX, int posY){
    if (*blockCarta == false)
    {
        if(estande.super ==1){

            *Carta = carregaCarta('G');
        }else{
            *Carta = carregaCarta(estande.letra);
        }

        *blockCarta = true;
    }
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

void listarCartaNoJogoGrande(Estande estande) {
    
    if (estande.super == 0) DrawRectangle(150, 150, 200, 300, LIGHTGRAY); // Card rectangle
    if (estande.super == 1) DrawRectangle(150, 150, 200, 300, GOLD);

    DrawRectangle(285, 59, 224, 170, BLACK); // Foto
    DrawRectangle(285, 285, 222, 62, WHITE); // Stats box

    DrawText("Strenght: ", 302, 297, 14, BLACK);
    DrawText("    Speed: ", 302, 312, 14, BLACK);
    DrawText("Range: ", 405, 297, 14, BLACK);
    DrawText("Prstc: ", 405, 312, 14, BLACK);

    DrawTexture(estande.foto, 309, 87, WHITE);

    if (estande.super == 1) {
        char goldenAux[40] = "Golden Experience\nRequiem - SUPER";
        DrawText(goldenAux, 283, 233, 24, BLACK);
    } else {
        DrawText(estande.nome, 283, 233, 24, BLACK);
    }

    int valores[4] = {estande.poderDestrutivo, estande.velocidade, estande.alcance, estande.persistenciaDePoder};
    char buffer[32];

    snprintf(buffer, sizeof(buffer), "%d", valores[0]);
    DrawText(buffer, 369, 297, 14, BLACK);

    snprintf(buffer, sizeof(buffer), "%d", valores[1]);
    DrawText(buffer, 369, 314, 14, BLACK);

    snprintf(buffer, sizeof(buffer), "%d", valores[2]);
    DrawText(buffer, 450, 297, 14, BLACK);

    snprintf(buffer, sizeof(buffer), "%d", valores[3]);
    DrawText(buffer, 450, 314, 14, BLACK);
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