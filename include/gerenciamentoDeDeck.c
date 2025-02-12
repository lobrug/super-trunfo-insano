#include "gerenciamentoDeDeck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "raylib.h"
#include "raygui.h" // Adicione esta linha
#include "structEstandes.h"


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
    DrawTextEx(fonte, TextFormat("%d", estande.velocidade), (Vector2){posX + 123, posY + 309}, 20, 0, cor);
    DrawTextEx(fonte, TextFormat("%d", estande.alcance), (Vector2){posX + 123, posY + 292}, 20, 0, cor);
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

void armazenaDeckFinal(Estande estandes[]){

    FILE *arq = fopen("deck_ultima_partida.dat", "wb");

    fwrite(estandes, sizeof(Estande), 32, arq);

    fclose(arq);

    return;
}

Estande recebeCartaParaMao(Estande deck[]) {
    for (int i = 0; i < 32; i++) {
        if (deck[i].nome[0] != '\0') { // Verifica se o slot não está vazio
            Estande carta = deck[i]; // Atribui a carta do deck para a mão
            deck[i].nome[0] = '\0';
            return carta;
        }
    }
    printf("Voce nao tem cartas no monte\n");
}


int VerificadorFiltro(char Letra, int poder[], int velocidade[], int alcance[], int persistencia[], int numero, Estande estandes){

    if ((Letra != 'Z') && (Letra != estandes.letra))
    {
        return -1;
    }

    if ((poder[0] != -1) && ((estandes.poderDestrutivo < poder[0]) || (estandes.poderDestrutivo > poder[1])))
    {
        return -1;
    }

    if ((velocidade[0] != -1) && ((estandes.velocidade < velocidade[0]) || (estandes.velocidade > velocidade[1])))
    {
        return -1;
    }
    
    if ((alcance[0] != -1) && ((estandes.alcance < alcance[0]) || (estandes.alcance > alcance[1])))
    {
        return -1;
    }

    if ((persistencia[0] != -1) && ((estandes.persistenciaDePoder < persistencia[0]) || (estandes.persistenciaDePoder > persistencia[1])))
    {
        return -1;
    }
    
    if ((numero != -1) && (numero != estandes.numero))
    {
        return -1;
    }
    
    return 0;
    
}

void DrawCenteredTextEx(Font font, const char *text, Vector2 centerPos, float fontSize, float spacing, Color color) {
    Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing); // Mede o tamanho do texto
    Vector2 position = { centerPos.x - textSize.x / 2, centerPos.y - textSize.y / 2 }; // Ajusta posição
    DrawTextEx(font, text, position, fontSize, spacing, color); // Desenha o texto
}
