#ifndef pesquisaDeCartas_H
#define pesquisaDeCartas_H

#include "pesquisaDeCartas.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "structEstandes.h"
#include "raylib.h"

void lerString(char* texto, int tamanho){
    setbuf(stdin, NULL);
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}

void listarCartaNaAlteracao(Estande estande){
    if(estande.super == 0) DrawRectangle(300, 150, 200, 300, LIGHTGRAY); //card rectangle
    if(estande.super == 1) DrawRectangle(300, 150, 200, 300, GOLD);
    DrawRectangle(313, 158, 174, 142, BLACK); //foto
    DrawRectangle(313, 336, 172, 52, WHITE); //stats box
    DrawText("Strenght: ", 318, 345, 12, BLACK);
    DrawText("    Speed: ", 318, 363, 12, BLACK);
    DrawText("Range: ", 406, 346, 12, BLACK);
    DrawText("Prstc: ", 406, 362, 12, BLACK);
    DrawTexture(estande.foto, 313, 158, WHITE);
    if(estande.super ==1){
        char goldenAux[40] = "Golden Experience\nRequiem - SUPER";
        DrawText(goldenAux, 313, 300, 18, BLACK);
    }else{
        DrawText(estande.nome, 313, 300, 18, BLACK);
    }
    int valores[4] = {estande.poderDestrutivo, estande.velocidade, estande.alcance, estande.persistenciaDePoder};
    char buffer[32];
    
    for(int i = 0; i < 4; i++){
        snprintf(buffer, sizeof(buffer), "%d", valores[i]);
        if(i == 0){
            DrawText(buffer, 378, 346, 14, BLACK);
        }

        if(i == 1){
            DrawText(buffer, 378, 362, 14, BLACK);
        }

        if(i == 2){
            DrawText(buffer, 447, 346, 14, BLACK);
        }

        if(i == 3){
            DrawText(buffer, 447, 362, 14, BLACK);
        }
    }
    
}

void listarCartaNoGerenciamento(Estande estande){
    if(estande.super == 0) DrawRectangle(451, 151, 200, 300, LIGHTGRAY); //card rectangle
    if(estande.super == 1) DrawRectangle(451, 151, 200, 300, GOLD);
    DrawRectangle(464, 159, 174, 142, BLACK); //foto
    DrawRectangle(464, 337, 172, 52, WHITE); //stats box
    DrawText("Strenght: ", 469, 346, 12, BLACK);
    DrawText("    Speed: ", 469, 364, 12, BLACK);
    DrawText("Range: ", 557, 347, 12, BLACK);
    DrawText("Prstc: ", 557, 363, 12, BLACK);
    DrawTexture(estande.foto, 464, 159, WHITE);
    if(estande.super ==1){
        char goldenAux[40] = "Golden Experience\nRequiem - SUPER";
        DrawText(goldenAux, 464, 301, 18, BLACK);
    }else{
        DrawText(estande.nome, 464, 301, 18, BLACK);
    }
    int valores[4] = {estande.poderDestrutivo, estande.velocidade, estande.alcance, estande.persistenciaDePoder};
    char buffer[32];
    
    for(int i = 0; i < 4; i++){
        snprintf(buffer, sizeof(buffer), "%d", valores[i]);
        if(i == 0){
            DrawText(buffer, 529, 347, 14, BLACK);
        }

        if(i == 1){
            DrawText(buffer, 529, 363, 14, BLACK);
        }

        if(i == 2){
            DrawText(buffer, 598, 347, 14, BLACK);
        }

        if(i == 3){
            DrawText(buffer, 598, 363, 14, BLACK);
        }
    }
    
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