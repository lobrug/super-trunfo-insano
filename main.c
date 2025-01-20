#include <stdio.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "structEstandes.h"
#include "leituraCsv.h"
#include "pesquisaDeCartas.h"
#include "manipulacaoCartas.h"
#include "embaralhar.h"
#include "gerenciamentoDeDeck.h"
#include "batalha.h"
#include <ctype.h>

char *strcasestr(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;  // Retorna o haystack se needle for vazio.

    size_t needle_len = strlen(needle);

    for (; *haystack; haystack++) {
        if (strncasecmp(haystack, needle, needle_len) == 0) {
            return (char *)haystack;  // Retorna o ponteiro para a primeira ocorrência.
        }
    }

    return NULL;  // Retorna NULL se não encontrar.
}

typedef enum {GAME_MENU, GAME_DECK, GAME_PLAY} gameScreens;

int main(void){
    Estande estandes[32];
    Estande deckPlayer[32];
    Estande deckBot[32];

    Estande maoJogador;
    Estande maoBot;

    bool cartaJogadorExibida = false;

    int turnos = 0;

    gameScreens actualScreen = GAME_MENU;

    char pesquisa[100] = "";

    Estande estandesPesquisa;
    Estande filtracaoEstandes;
    int estandeSelecionado = 0;
    bool encontrado = false;
    int verificaVoltarMenu = 0;

    int j;
    

    const int screenWidth = 800;
    const int screenHeight = 600;

    leituraArquivoCsv(estandes);

    InitWindow(screenWidth, screenHeight, "Super-Trunfo Insanamente Bizarro");
    
    SetTargetFPS(144);

    // Adicione uma mensagem de depuração para verificar o caminho do arquivo
//    printf("Tentando carregar a textura de: content\\jojo.png\n");
    Texture2D background = LoadTexture(".\\assets\\img\\background.jpg");
    Texture2D jojoimg = LoadTexture(".\\assets\\img\\jojo.png");
    Texture2D table = LoadTexture(".\\assets\\img\\table.jpg");
    Texture2D backCard = LoadTexture(".\\assets\\img\\backCard.png");
    
    

    {
    loadImageToCard(&estandes[0], ".\\assets\\stands\\starplatinum.png", 174, 142);
    loadImageToCard(&estandes[1], ".\\assets\\stands\\theworld.png", 174, 142);
    loadImageToCard(&estandes[2], ".\\assets\\stands\\goldexperience.png", 174, 142);
    loadImageToCard(&estandes[3], ".\\assets\\stands\\kingcrimson.png", 174, 142);
    loadImageToCard(&estandes[4], ".\\assets\\stands\\madeinheaven.png", 174, 142);
    loadImageToCard(&estandes[5], ".\\assets\\stands\\tuskact4.png", 174, 142);
    loadImageToCard(&estandes[6], ".\\assets\\stands\\killerqueen.png", 174, 142);
    loadImageToCard(&estandes[7], ".\\assets\\stands\\d4c.png", 174, 142);
    loadImageToCard(&estandes[8], ".\\assets\\stands\\crazydiamond.png", 174, 142);
    loadImageToCard(&estandes[9], ".\\assets\\stands\\goldrequiem.png", 174, 142);
    loadImageToCard(&estandes[10], ".\\assets\\stands\\weatherreport.png", 174, 142);
    loadImageToCard(&estandes[11], ".\\assets\\stands\\magiciansred.png", 174, 142);
    loadImageToCard(&estandes[12], ".\\assets\\stands\\stickyfingers.png", 174, 142);
    loadImageToCard(&estandes[13], ".\\assets\\stands\\echoesact3.png", 174, 142);
    loadImageToCard(&estandes[14], ".\\assets\\stands\\greenday.png", 174, 142);
    loadImageToCard(&estandes[15], ".\\assets\\stands\\stonefree.png", 174, 142);
    loadImageToCard(&estandes[16], ".\\assets\\stands\\silverchariot.png", 174, 142);
    loadImageToCard(&estandes[17], ".\\assets\\stands\\rhcp.png", 174, 142);
    loadImageToCard(&estandes[18], ".\\assets\\stands\\sexpistols.png", 174, 142);
    loadImageToCard(&estandes[19], ".\\assets\\stands\\hierophantgreen.png", 174, 142);
    loadImageToCard(&estandes[20], ".\\assets\\stands\\cmoon.png", 174, 142);
    loadImageToCard(&estandes[21], ".\\assets\\stands\\moodyblues.png", 174, 142);
    loadImageToCard(&estandes[22], ".\\assets\\stands\\purplehaze.png", 174, 142);
    loadImageToCard(&estandes[23], ".\\assets\\stands\\diverdown.png", 174, 142);
    loadImageToCard(&estandes[24], ".\\assets\\stands\\hermitpurple.png", 174, 142);
    loadImageToCard(&estandes[25], ".\\assets\\stands\\heavensdoor.png", 174, 142);
    loadImageToCard(&estandes[26], ".\\assets\\stands\\beachboy.png", 174, 142);
    loadImageToCard(&estandes[27], ".\\assets\\stands\\aerosmith.png", 174, 142);
    loadImageToCard(&estandes[28], ".\\assets\\stands\\thehand.png", 174, 142);
    loadImageToCard(&estandes[29], ".\\assets\\stands\\big.png", 174, 142);
    loadImageToCard(&estandes[30], ".\\assets\\stands\\softwet.png", 174, 142);
    loadImageToCard(&estandes[31], ".\\assets\\stands\\justice.png", 174, 142);
    }

    while(!WindowShouldClose()){
        DrawFPS(720,580);
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(DARKPURPLE));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
        Vector2 mousePos = GetMousePosition();

        if(actualScreen == GAME_MENU){

            BeginDrawing();

            ClearBackground(DARKPURPLE);
            DrawTexture(background, 0, 0, WHITE);
            DrawTexture(jojoimg, 230, 100, WHITE);


            if(GuiButton((Rectangle){295,357,211,47}, "Play")){
                embaralharDecks(deckPlayer, deckBot, estandes);
                actualScreen = GAME_PLAY;
            }

            if(GuiButton((Rectangle){295,407,211,47}, "Card Management")){
                actualScreen = GAME_DECK;
                estandeSelecionado = 0;
                j= 0;
                
            }
        
            if(GuiButton((Rectangle){295,456,211,47}, "Quit")){
                break;
            }

            EndDrawing();
        }//If - GAME_MENU

        if(actualScreen == GAME_DECK){

            BeginDrawing();
            ClearBackground(BLACK);

            //filter box rectangle
            DrawRectangle(16, 78, 265, 471, LIGHTGRAY); 

            if(GuiButton((Rectangle){16,16,83,48}, "#121#")){
                actualScreen = GAME_MENU;
            }//If - Voltar pro GAME_MENU

            if (strcmp(pesquisa, "") != 0) {
                int salva_pesquisa[32];
                int n = 0;

                // Realizar busca nos estandes
                for (int i = 0; i < 32; i++) {

                    // Verificar se a pesquisa é substring do nome do estande
                    if (strcasestr(estandes[i].nome, pesquisa) != NULL) {
                        salva_pesquisa[n] = i;
                        n++;
                    }
                }

                // Verificar se há resultados encontrados
                if (n == 0) {
                    DrawText("Nenhum resultado encontrado", 300, 300, 20, RED);
                } else {
                    listarCartaNoGerenciamento(estandes[salva_pesquisa[j]]);

                    // Botão para resultado anterior
                    if (GuiButton((Rectangle){343, 270, 61, 61}, "#114#")) {
                        j--;
                        if (j < 0) j = n - 1; // Ajustar índice para último resultado
                    }

                    // Botão para próximo resultado
                    if (GuiButton((Rectangle){698, 270, 61, 61}, "#115#")) {
                        j++;
                        if (j >= n) j = 0; // Ajustar índice para primeiro resultado
                    }
                }

            } else {
                // Mostrar carta normalmente se não houver pesquisa
                encontrado = false;
                listarCartaNoGerenciamento(estandes[estandeSelecionado]);

                if (GuiButton((Rectangle){343, 270, 61, 61}, "#114#")) {
                    estandeSelecionado--;
                    if (estandeSelecionado < 0) estandeSelecionado = 31;
                }

                if (GuiButton((Rectangle){698, 270, 61, 61}, "#115#")) {
                    estandeSelecionado++;
                    if (estandeSelecionado > 31) estandeSelecionado = 0;
                }
            }
    
            (GuiTextBox((Rectangle){24, 86, 249, 31}, pesquisa, 40, true));
                
            EndDrawing();
        }

        if(actualScreen == GAME_PLAY){

            BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(table, (Rectangle){0, 0, table.width, table.height}, (Rectangle){0, 0, 800, 600}, (Vector2){0, 0}, 0.0f, WHITE);


            if(GuiButton((Rectangle){16,540,83,48}, "#121#")){         
                        actualScreen = GAME_MENU;  
            }


            DrawRectangle(240, 206, 126, 189, PURPLE);
            DrawText("X",392, 279, 36, BLACK);
            DrawRectangle(435, 206, 126, 189, PURPLE);

            bool isHoverPlayerDeck = CheckCollisionPointRec(mousePos, (Rectangle){656, 395, 126, 189});
            bool isClickedPlayerDeck = isHoverPlayerDeck && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            Color tint = isHoverPlayerDeck ? GRAY : WHITE;
            DrawTexturePro(backCard, (Rectangle){0, 0, backCard.width, backCard.height}, (Rectangle){656, 395, 126, 189}, (Vector2){0, 0}, 0.0f, WHITE);
            DrawTexturePro(backCard, (Rectangle){0, 0, backCard.width, backCard.height}, (Rectangle){18, 16, 126, 189}, (Vector2){0, 0}, 0.0f, WHITE);

            if ((turnos % 2) == 1) { // Vez do player jogar
                if (isClickedPlayerDeck && !cartaJogadorExibida) { // Só executa ao clicar no botão
                    printf("Teste click\n");
                    maoJogador = recebeCartaParaMao(deckPlayer);
                    maoBot = recebeCartaParaMao(deckBot);
                    cartaJogadorExibida = true; // Marca que a carta foi exibida
                    turnos++; // Avança o turno
                }

                // Sempre desenha a carta do jogador se ela foi sacada
                if (cartaJogadorExibida) {
                    DrawRectangle(0,0,800,600,(Color){0,0,0,180});

                    DrawRectangle(126, 470, 548, 111, DARKPURPLE);
                    listarCartaNoJogoGrande(maoJogador);
                    DrawText("SELECIONE UM ATRIBUTO PARA BATALHA!", 145, 430, 24, PURPLE);

                    if(GuiButton((Rectangle){147, 485, 100, 80}, "STRENGHT")){
                        batalhaPoder(maoJogador, maoBot, deckPlayer, deckBot);
                        cartaJogadorExibida = false;
                    }

                    if(GuiButton((Rectangle){281, 485, 100, 80}, "SPEED")){
                        batalhaVelocidade(maoJogador, maoBot, deckPlayer, deckBot);
                        cartaJogadorExibida = false;
                    }

                    if(GuiButton((Rectangle){413, 485, 100, 80}, "RANGE")){
                        batalhaAlcance(maoJogador, maoBot, deckPlayer, deckBot);
                        cartaJogadorExibida = false;
                    }

                    if(GuiButton((Rectangle){549, 485, 100, 80}, "PRSTC")){
                        batalhaPersistencia(maoJogador, maoBot, deckPlayer, deckBot);
                        cartaJogadorExibida = false;
                    }

                }

            }else{ //vez do bot jogar
                maoJogador = recebeCartaParaMao(deckPlayer);
                maoBot = recebeCartaParaMao(deckBot);

                

                turnos++;
            }

            
            

            EndDrawing();
        }

    }

    UnloadTexture(background);
    UnloadTexture(jojoimg); // Unload texture when done
    CloseWindow();

    return 0;
}