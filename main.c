#include <stdio.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "structEstandes.h"
#include "leituraCsv.h"
#include "menu.h"
#include "pesquisaDeCartas.h"
#include "manipulacaoCartas.h"

typedef enum {GAME_MENU, GAME_DECK, GAME_PLAY} gameScreens;

int main(void){
    Estande estandes[32];
    gameScreens actualScreen = GAME_MENU;
    char pesquisa[100] = "";
    

    const int screenWidth = 800;
    const int screenHeight = 600;

    leituraArquivoCsv(estandes);

    InitWindow(screenWidth, screenHeight, "Meu pau");
    
    SetTargetFPS(144);

    // Adicione uma mensagem de depuração para verificar o caminho do arquivo
//    printf("Tentando carregar a textura de: content\\jojo.png\n");
    Texture2D background = LoadTexture(".\\assets\\img\\background.jpg");
    Texture2D jojoimg = LoadTexture(".\\assets\\img\\jojo.png");

    {
    loadImageToCard(&estandes[0], ".\\assets\\stands\\starplatinum.png");
    loadImageToCard(&estandes[1], ".\\assets\\stands\\theworld.png");
    loadImageToCard(&estandes[2], ".\\assets\\stands\\goldexperience.png");
    loadImageToCard(&estandes[3], ".\\assets\\stands\\kingcrimson.png");
    loadImageToCard(&estandes[4], ".\\assets\\stands\\madeinheaven.png");
    loadImageToCard(&estandes[5], ".\\assets\\stands\\tuskact4.png");
    loadImageToCard(&estandes[6], ".\\assets\\stands\\killerqueen.png");
    loadImageToCard(&estandes[7], ".\\assets\\stands\\d4c.png");
    loadImageToCard(&estandes[8], ".\\assets\\stands\\crazydiamond.png");
    loadImageToCard(&estandes[9], ".\\assets\\stands\\goldrequiem.png");
    loadImageToCard(&estandes[10], ".\\assets\\stands\\weatherreport.png");
    loadImageToCard(&estandes[11], ".\\assets\\stands\\magiciansred.png");
    loadImageToCard(&estandes[12], ".\\assets\\stands\\stickyfingers.png");
    loadImageToCard(&estandes[13], ".\\assets\\stands\\echoesact3.png");
    loadImageToCard(&estandes[14], ".\\assets\\stands\\greenday.png");
    loadImageToCard(&estandes[15], ".\\assets\\stands\\stonefree.png");
    loadImageToCard(&estandes[16], ".\\assets\\stands\\silverchariot.png");
    loadImageToCard(&estandes[17], ".\\assets\\stands\\rhcp.png");
    loadImageToCard(&estandes[18], ".\\assets\\stands\\sexpistols.png");
    loadImageToCard(&estandes[19], ".\\assets\\stands\\hierophantgreen.png");
    loadImageToCard(&estandes[20], ".\\assets\\stands\\cmoon.png");
    loadImageToCard(&estandes[21], ".\\assets\\stands\\moodyblues.png");
    loadImageToCard(&estandes[22], ".\\assets\\stands\\purplehaze.png");
    loadImageToCard(&estandes[23], ".\\assets\\stands\\diverdown.png");
    loadImageToCard(&estandes[24], ".\\assets\\stands\\hermitpurple.png");
    loadImageToCard(&estandes[25], ".\\assets\\stands\\heavensdoor.png");
    loadImageToCard(&estandes[26], ".\\assets\\stands\\beachboy.png");
    loadImageToCard(&estandes[27], ".\\assets\\stands\\aerosmith.png");
    loadImageToCard(&estandes[28], ".\\assets\\stands\\thehand.png");
    loadImageToCard(&estandes[29], ".\\assets\\stands\\big.png");
    loadImageToCard(&estandes[30], ".\\assets\\stands\\softwet.png");
    loadImageToCard(&estandes[31], ".\\assets\\stands\\justice.png");
    }
    // Verifique se a textura foi carregada corretamente
    if (jojoimg.id == 0) {
        printf("Failed to load texture\n");
        return -1;
    }

    while(!WindowShouldClose()){
        DrawFPS(720,580);
        int estandeSelecionado;
        if(actualScreen == GAME_MENU){
        BeginDrawing();
        ClearBackground(DARKPURPLE);
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(jojoimg, 230, 100, WHITE);
        GuiButton((Rectangle){295,357,211,47}, "Play");

        if(GuiButton((Rectangle){295,407,211,47}, "Card Management")){
            actualScreen = GAME_DECK;
            estandeSelecionado = 0;
        }
        
        if(GuiButton((Rectangle){295,456,211,47}, "Quit")){
            break;
        }
        EndDrawing();
        }

        if(actualScreen == GAME_DECK){
            BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangle(16, 78, 265, 471, WHITE); //filter box rectangle

            GuiTextBox((Rectangle){24, 86, 249, 31}, pesquisa, 40, true);

            //card design
            
            listarCartaNoGerenciamento(estandes[estandeSelecionado]);

            
            
            if(GuiButton((Rectangle){16,16,83,48}, "MENU")){
                actualScreen = GAME_MENU;
            }

            
            if(GuiButton((Rectangle){343, 270, 61, 61}, "BACK")){
                estandeSelecionado--;
                if(estandeSelecionado == -1) estandeSelecionado = 31;
            }

            if(GuiButton((Rectangle){698, 270, 61, 61}, "NEXT")){
                estandeSelecionado++;
                if(estandeSelecionado == 32) estandeSelecionado = 0;
            }


            EndDrawing();
        }

    }

    UnloadTexture(background);
    UnloadTexture(jojoimg); // Unload texture when done
    CloseWindow();

    return 0;
}