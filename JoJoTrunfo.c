#include <stdio.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "structEstandes.h"
#include "leituraCsv.h"
#include "manipulacaoCartas.h"
#include "embaralhar.h"
#include "gerenciamentoDeDeck.h"
#include "batalha.h"
#include "botInteligencia.h"
#include <ctype.h>
#include <stdbool.h>
//#include "raygui_icons.h"



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

typedef enum {GAME_MENU, GAME_DECK, GAME_PLAY, DECK_MANAGEMENT} gameScreens;

typedef enum {ESPERANDO_JOGADOR,ESCOLHENDO_ATRIBUTO, MOSTRANDO_CARTA, REVELANDO_CARTAS, FIM_TURNO, ESPERANDO_BOT} estadoJogo;

int main(void){

    bool saida_jogar = false;

    Estande estandes[32];
    Estande deckPlayer[32];
    Estande deckBot[32];
    estadoJogo estadoAtual = ESPERANDO_JOGADOR;

    for (int i = 0; i < 32; i++) {
        estandes[i].nome[0] = '\0';
        deckPlayer[i].nome[0] = '\0';
        deckBot[i].nome[0] = '\0';
    }

    Estande maoJogador;
    Estande maoBot;

    bool cartaRevelada = false;
    bool cartaJogadorExibida = false;
    bool cartaBotExibida = false;
    bool vitoriaPlayer = false;
    bool vitoriaBot = false;
    bool filtroCheck = false;

    bool verificaPesquisa = false;
    bool verificaExportar = false;

    char escolha[20];

    //---- Armazenadores dos valores dos filtros --------------------------------------------------------------------
    //0 - min
    //1 - max

    int filtroPoder[2]; 
    int filtroVelocidade[2];
    int filtroAlcance[2];
    int filtroPersistencia[2];

    //----------------------------------------------------------------------------------------------------------------


    //Pontuacao-----------------------------------------------------------------------------------------------

    int pontuacaoBot = 0;
    int pontuacaoPlayer = 0;

    //---------------------------------------------------------------------------------------------------------



    //---- Verificador de clique em alterar imagem ----------------------------------------------------------------------

    bool click_img = false;
    char endereco[100] = ".\\assets\\mods\\"; //manter o texto pre definido
    
    //-------------------------------------------------------------------------------------------------------------------



    //-- Verificadores de filtro clicado -------------------------------------------------------------------------

    bool checkPoder = false;
    bool checkVelocidade = false;
    bool checkAlcance = false;
    bool checkPersistencia = false;
    bool checkLetra = false;
    bool checkNumero = false;

    //----------------------------------------------------------------------------------------------------------------



    // Letras para filtro de cartas ----------------------------------------------------------------------------------

    char letras[5] = {'A', 'B', 'C', 'D', 'Z'};

    float indiceLetra = 4; // indice inciado como 'Z'
    float filtroNumero = -1; // Número de filtro iniciado como -1

    //----------------------------------------------------------------------------------------------------------------

    int selecionaCarta;

    // Desbloqueio da ediçao de filtros	---------------------

    bool edit[9];

    for (int i = 0; i < 9; i++){
                
        edit[i] = false;
        
    }
    //--------------------------------------------------------


    int turnos = 1;


    // Texturas em game----------------------------------------------------------------------------------------------------

    Texture2D Carta;
    Texture2D Carta2;
    bool blockCarta1 = false;
    bool blockCarta2 = false;
    //---------------------------------------------------------------------------------------------------------------

    // Definir a tela inicial do jogo como o menu --------------------------------------------------------------------
    gameScreens actualScreen = GAME_MENU;
    //----------------------------------------------------------------------------------------------------------------

    
    char pesquisa[100] = ""; // Variavel para armazenar a pesquisa

    int estandeSelecionado = 0;
    bool encontrado = false;

    int passar_pesquisa; //Funcionamento das setas quando algo escrito na pesquisa

    // Tamanho da tela --------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;
    //--------------------------------------------------------------------


    // Verifica se existe um arquivo binário com o estado salvo da última partida.
    FILE *leitorBinario = fopen("deck_ultima_partida.dat", "rb");
    if (leitorBinario == NULL) {
        // Caso o arquivo binário não exista, os dados são lidos do arquivo CSV.
        leituraArquivoCsv(estandes);
        fclose(leitorBinario);
    } else {
        // Caso o arquivo binário exista, os dados são carregados diretamente dele.
        fread(estandes, sizeof(Estande), 32, leitorBinario);
        fclose(leitorBinario);
    }

    // Inicialização da janela e áudio -------------------------------
    InitWindow(screenWidth, screenHeight, "Super-Trunfo Insanamente Bizarro");
    InitAudioDevice();
    //----------------------------------------------------------------


    Image icon = LoadImage(".\\assets\\img\\icon.png"); // Ícone como imagem PNG
    SetWindowIcon(icon);
    
    SetTargetFPS(144);

    // Carregamento de texturas e sons -------------------------------
    Texture2D background = LoadTexture(".\\assets\\img\\background.jpg");
    Texture2D jojoimg = LoadTexture(".\\assets\\img\\jojo.png");
    Texture2D table = LoadTexture(".\\assets\\img\\table.jpg");
    Texture2D backCard = LoadTexture(".\\assets\\img\\backCard.png");
    Texture2D fundoCarta = LoadTexture(".\\assets\\img\\fundoCarta.jpg");
    Sound buttonSound = LoadSound(".\\assets\\sounds\\buttonsound.mp3");
    Sound theme = LoadSound(".\\assets\\sounds\\theme.mp3");
    Font fonteCarta = LoadFont(".\\assets\\font\\OpenSans-Bold.ttf");
    Font fonteJogo = LoadFont(".\\assets\\font\\jjba.ttf");
    Texture2D fundoDeck = LoadTexture(".\\assets\\img\\fundoDeck.png");
    //----------------------------------------------------------------

    // Configuração da fonte da carta -------------------------------
    GenTextureMipmaps(&fonteCarta.texture);
    GenTextureMipmaps(&fonteJogo.texture);
    SetTextureFilter(fonteJogo.texture, TEXTURE_FILTER_BILINEAR);
    GenTextureMipmaps(&fundoDeck);
    SetTextureFilter(fundoDeck, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fonteCarta.texture, TEXTURE_FILTER_BILINEAR);
    
    //----------------------------------------------------------------


    // Carregamento das cartas --------------------------------------------
    {
    loadImageToCard(&estandes[0], ".\\assets\\stands\\starplatinum.png", 202, 251);
    loadImageToCard(&estandes[1], ".\\assets\\stands\\theworld.png", 200, 292);
    loadImageToCard(&estandes[2], ".\\assets\\stands\\purplehaze.png", 202, 303);
    loadImageToCard(&estandes[3], ".\\assets\\stands\\kingcrimson.png", 175, 262);
    loadImageToCard(&estandes[4], ".\\assets\\stands\\madeinheaven.png", 211, 153);
    loadImageToCard(&estandes[5], ".\\assets\\stands\\thehand.png", 200, 238);
    loadImageToCard(&estandes[6], ".\\assets\\stands\\killerqueen.png", 200, 206);
    loadImageToCard(&estandes[7], ".\\assets\\stands\\d4c.png", 218, 145);
    loadImageToCard(&estandes[8], ".\\assets\\stands\\crazydiamond.png", 218, 145);
    loadImageToCard(&estandes[9], ".\\assets\\stands\\goldrequiem.png", 218, 145);
    loadImageToCard(&estandes[10], ".\\assets\\stands\\weatherreport.png", 218, 145);
    loadImageToCard(&estandes[11], ".\\assets\\stands\\magiciansred.png", 218, 145);
    loadImageToCard(&estandes[12], ".\\assets\\stands\\stickyfingers.png", 218, 145);
    loadImageToCard(&estandes[13], ".\\assets\\stands\\echoesact3.png", 218, 145);
    loadImageToCard(&estandes[14], ".\\assets\\stands\\greenday.png", 218, 145);
    loadImageToCard(&estandes[15], ".\\assets\\stands\\stonefree.png", 218, 145);
    loadImageToCard(&estandes[16], ".\\assets\\stands\\silverchariot.png", 218, 145);
    loadImageToCard(&estandes[17], ".\\assets\\stands\\rhcp.png", 218, 145);
    loadImageToCard(&estandes[18], ".\\assets\\stands\\sexpistols.png", 218, 145);
    loadImageToCard(&estandes[19], ".\\assets\\stands\\hierophantgreen.png", 218, 145);
    loadImageToCard(&estandes[20], ".\\assets\\stands\\cmoon.png", 218, 145);
    loadImageToCard(&estandes[21], ".\\assets\\stands\\moodyblues.png", 218, 145);
    loadImageToCard(&estandes[22], ".\\assets\\stands\\goldexperience.png", 218, 145);
    loadImageToCard(&estandes[23], ".\\assets\\stands\\diverdown.png", 218, 145);
    loadImageToCard(&estandes[24], ".\\assets\\stands\\hermitpurple.png", 218, 145);
    loadImageToCard(&estandes[25], ".\\assets\\stands\\heavensdoor.png", 218, 145);
    loadImageToCard(&estandes[26], ".\\assets\\stands\\beachboy.png", 218, 145);
    loadImageToCard(&estandes[27], ".\\assets\\stands\\aerosmith.png", 218, 145);
    loadImageToCard(&estandes[28], ".\\assets\\stands\\tuskact4.png", 218, 145);
    loadImageToCard(&estandes[29], ".\\assets\\stands\\big.png", 218, 145);
    loadImageToCard(&estandes[30], ".\\assets\\stands\\softwet.png", 218, 145);
    loadImageToCard(&estandes[31], ".\\assets\\stands\\justice.png", 218, 145);
    }
    //------------------------------------------------------------------

    // Reprodução do tema do jogo --------------------------------------
    PlaySound(theme);
    //Setar volume do tema---------------------------------------------
    SetSoundVolume(theme, 0.1);


    while(!WindowShouldClose()){
        DrawFPS(720,580);

        // Configuração de estilo dos botões ---------------------------
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(DARKPURPLE));//fundo
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));//texto
        GuiSetFont(fonteJogo);
        //----------------------------------------------------------------

        Vector2 mousePos = GetMousePosition();//Pegar posição do mouse

        if(actualScreen == GAME_MENU){

            BeginDrawing();
            GuiSetStyle(DEFAULT, TEXT_SIZE, 12); 

            ClearBackground(DARKPURPLE);
            DrawTexture(background, 0, 0, WHITE);
            DrawTexture(jojoimg, 230, 100, WHITE);


            if(GuiButton((Rectangle){295,357,211,47}, "Play")){
                PlaySound(buttonSound);
                embaralharDecks(deckPlayer, deckBot, estandes);
                actualScreen = GAME_PLAY;
            }

            if(GuiButton((Rectangle){295,407,211,47}, "Card Management")){
                PlaySound(buttonSound);
                actualScreen = GAME_DECK;
                estandeSelecionado = 0;
                passar_pesquisa= 0;
                
            }
        
            if(GuiButton((Rectangle){295,456,211,47}, "Quit")){
                break;
            }

            EndDrawing();
        }//If - GAME_MENU

        if(actualScreen == GAME_DECK){

            GuiSetStyle(DEFAULT, TEXT_SIZE, 10); 
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(fundoDeck, (Rectangle){0, 0, fundoDeck.width, fundoDeck.height}, (Rectangle){0, 0, 800, 600}, (Vector2){0, 0}, 0.0f, WHITE);

            //filter box rectangle
            DrawRectangle(16, 78, 265, 471, LIGHTGRAY); 

            if(GuiButton((Rectangle){16,16,83,48}, "#121#")){
                actualScreen = GAME_MENU;
                verificaExportar = false;
            }//If - Voltar pro GAME_MENU

            if(filtroCheck){

                DrawRectangle(25,122,249,414, BEIGE);

                GuiCheckBox((Rectangle){42,189,26,26}, "Poder", &checkPoder);
                GuiCheckBox((Rectangle){42,245,26,26}, "Velocidade", &checkVelocidade);
                GuiCheckBox((Rectangle){42,301,26,26}, "Alcance", &checkAlcance);
                GuiCheckBox((Rectangle){42,357,26,26}, "Persistencia", &checkPersistencia);
                GuiCheckBox((Rectangle){42,393,26,26}, "Letra", &checkLetra);
                GuiCheckBox((Rectangle){42,424,26,26}, "Numero", &checkNumero);

                verificaCheckFiltro(&checkPoder, filtroPoder, 166, 177, 203, 80, 24, &edit[0], &edit[1], edit);

                verificaCheckFiltro(&checkVelocidade, filtroVelocidade, 166, 233, 259, 80, 24, &edit[2], &edit[3], edit);

                verificaCheckFiltro(&checkAlcance, filtroAlcance, 166, 289, 315, 80, 24, &edit[4], &edit[5], edit);

                verificaCheckFiltro(&checkPersistencia, filtroPersistencia, 166, 345, 371, 80, 24, &edit[6], &edit[7], edit);

                //Verificar se o check do filtro da letra está ativado
                if (checkLetra) {
                    GuiSlider((Rectangle){78, 456, 143, 26}, "A", "D", &indiceLetra, 0, 3);
                    indiceLetra = (int)(indiceLetra + 0.5); // Arredonda para o inteiro mais próximo
                    char letra = letras[(int)indiceLetra];
                    DrawText(&letra, 144.5, 458, 20, BLACK);
                } else {
                    indiceLetra = 4; // 'Z'
                }//If - checkLetra
                
                //Verificar se o check do filtro do número está ativado
                if (checkNumero) {
                    GuiSlider((Rectangle){46, 496, 207, 26}, "1", "8", &filtroNumero, 1, 8);
                    filtroNumero = (int)(filtroNumero + 0.5); // Arredonda para o inteiro mais próximo
                    DrawText(TextFormat("%d", (int)filtroNumero), 144.5, 500, 20, BLACK);
                } else {
                    filtroNumero = -1;
                }//If - checkNumero

            
            }else{

                memset(filtroPoder, -1, sizeof(filtroPoder));
                memset(filtroVelocidade, -1, sizeof(filtroVelocidade));
                memset(filtroAlcance, -1, sizeof(filtroAlcance));
                memset(filtroPersistencia, -1, sizeof(filtroPersistencia));
                filtroNumero = -1;
                indiceLetra = 4;

            }//if - filtroCheck

            //if pesquisa
            if (strcmp(pesquisa, "") != 0) {
                int salva_pesquisa[32];
                int n = 0;

                // Realizar busca nos estandes
                for (int i = 0; i < 32; i++) {

                    // Verificar se a pesquisa é substring do nome do estande
                    int filtroResult = VerificadorFiltro(letras[(int)indiceLetra],filtroPoder, filtroVelocidade, filtroAlcance, filtroPersistencia, (int)filtroNumero,estandes[i]);
                    if ((strcasestr(estandes[i].nome, pesquisa) != NULL) && (filtroResult == 0)) {
                        salva_pesquisa[n] = i;
                        n++;
                    }
                }

                // Verificar se há resultados encontrados
                if (n == 0) {
                    DrawText("Nenhum resultado encontrado", 300, 300, 20, RED);
                } else {
                    
                    listarCartaNoGerenciamento(estandes[salva_pesquisa[passar_pesquisa]], &Carta, fundoCarta, &blockCarta1, fonteCarta, 426, 113);
                    
                    
                    if ( (GuiButton((Rectangle){463,504,176,46}, "#142# ALTERAR CARTA")))
                    {
                        selecionaCarta = salva_pesquisa[passar_pesquisa];
                        actualScreen = DECK_MANAGEMENT;
                    }

                    // Botão para resultado anterior
                    if (GuiButton((Rectangle){343, 270, 61, 61}, "#114#")) {
                        passar_pesquisa--;
                        if (passar_pesquisa < 0) passar_pesquisa = n - 1; // Ajustar índice para último resultado
                        blockCarta1 = false;
                    }

                    // Botão para próximo resultado
                    if (GuiButton((Rectangle){698, 270, 61, 61}, "#115#")) {
                        passar_pesquisa++;
                        if (passar_pesquisa >= n) passar_pesquisa = 0; // Ajustar índice para primeiro resultado
                        blockCarta1 = false;
                    }
                }

            } else {
                // Mostrar carta normalmente se não houver pesquisa
                encontrado = false;

                int salva_filtro[32];
                int n = 0;

                for (int i = 0; i < 32; i++) {

                    // Verificar se a pesquisa é substring do nome do estande
                    if (VerificadorFiltro(letras[(int)indiceLetra],filtroPoder, filtroVelocidade, filtroAlcance, filtroPersistencia, (int)filtroNumero,estandes[i]) == 0) {
                        salva_filtro[n] = i;
                        n++;
                    }
                }

                if(n == 0){
                    DrawText("Nenhum resultado encontrado", 300, 300, 20, RED);
                }else{

                    listarCartaNoGerenciamento(estandes[salva_filtro[estandeSelecionado]], &Carta, fundoCarta, &blockCarta1, fonteCarta, 426, 113);
                    
                    if ( (GuiButton((Rectangle){463,504,176,46}, "#142# GERENCIAR CARTA")))
                    {
                        selecionaCarta = salva_filtro[estandeSelecionado];
                        actualScreen = DECK_MANAGEMENT;
                    }

                    if (GuiButton((Rectangle){343, 270, 61, 61}, "#114#")) {
                        estandeSelecionado--;
                        if (estandeSelecionado < 0) estandeSelecionado = n - 1;
                        blockCarta1 = false;
                    }

                    if (GuiButton((Rectangle){698, 270, 61, 61}, "#115#")) {
                        estandeSelecionado++;
                        if (estandeSelecionado >= n) estandeSelecionado = 0;
                        blockCarta1 = false;
                    }

                }

            }
    
            //Desenha a caixa de pesquisa
            if(GuiTextBox((Rectangle){24, 86, 249, 31}, pesquisa, 40, edit[8])){

                edit[8] = true;

                for (int i = 0; i < 7; i++)
                {
                    edit[i] = false;
                }
                
            }//if - GuiTextBox - Pesquisa


            //If - Botão de filtro
            if(GuiButton((Rectangle){35,132,40,40}, "#047#")){
                filtroCheck = !filtroCheck;
                verificaExportar = false;

                if (filtroCheck == false)
                {
                    checkPoder = false;
                    checkVelocidade = false;
                    checkAlcance = false;
                    checkPersistencia = false;
                    checkLetra = false;
                    checkNumero = false;
                }    //Se o filtro não estiver clicado, desmarcar todos os checks de filtro
                
            }else if (filtroCheck == false){
             
                if (GuiButton((Rectangle){41,185,215,32}, "EXPORTAR CSV")){
                    verificaExportar = !verificaExportar;
                }
                
                if (verificaExportar == true)
                {
                    static char nome_csv[100];
                    
                    DrawRectangle(41, 231, 180, 31, WHITE);
                    edit[8] = false;
                    GuiTextBox((Rectangle){41, 231, 180, 31}, nome_csv, 100, true);
                    if (GuiButton((Rectangle){232, 236, 21, 21}, "#003#"))
                    {
                        strcat(nome_csv, ".csv");
                        FILE *exportaCSV = fopen(nome_csv, "w");
                        if (exportaCSV == NULL) {
                            // Adicione um log ou mensagem de erro para depuração
                            printf("Erro ao abrir o arquivo %s\n", nome_csv);
                        } else {
                            fprintf(exportaCSV, "Categoria,Número,Nome do Stand,Super,Poder Destrutivo,Velocidade,Alcance,Persistência\n");
                            for (int i = 0, j = 0; i < 32; i++) {
                    
                                fprintf(exportaCSV, "%c,%d,%s,%d,%d,%d,%d,%d\n",
                                        estandes[i].letra,
                                        estandes[i].numero,
                                        estandes[i].nome,
                                        estandes[i].super,
                                        estandes[i].poderDestrutivo,
                                        estandes[i].velocidade,
                                        estandes[i].alcance,
                                        estandes[i].persistenciaDePoder);
                            }
                            fclose(exportaCSV); // Fechar o arquivo após a escrita
                        }
                        verificaExportar = false;
                    }

                }

            }//If - Botão de filtro
                
            EndDrawing();
        }//If - GAME_DECK

        if(actualScreen == GAME_PLAY){

            GuiSetFont(GetFontDefault());
            GuiSetStyle(DEFAULT, TEXT_SIZE, 10);

            BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(table, (Rectangle){0, 0, table.width, table.height}, (Rectangle){0, 0, 800, 600}, (Vector2){0, 0}, 0.0f, WHITE);

            if (GuiButton((Rectangle){16,540,83,48}, "#121#")) {
                saida_jogar = true;
            };

            if(saida_jogar == true){

                ClearBackground(BLACK);
                DrawText("TEM CERTEZA?", 216, 234, 50, RED);
                if ((GuiButton((Rectangle){159, 345, 181, 76}, "SIM")))
                {
                    estadoAtual = ESPERANDO_JOGADOR;
                    pontuacaoBot = 0;
                    pontuacaoPlayer = 0;
                    turnos = 1;
                    actualScreen = GAME_MENU;
                    vitoriaPlayer = false;
                    vitoriaBot = false;
                    cartaJogadorExibida = false;
                    cartaBotExibida = false;  
                    saida_jogar = false;
                }

                if ((GuiButton((Rectangle){459, 345, 181, 76}, "NAO")))
                {
                    saida_jogar = false;
                }
                
            }else{

                DrawRectangle(125, 77, 250, 375, PURPLE);
                DrawText("X",389, 241, 36, BLACK);
                DrawRectangle(425, 77, 250, 375, PURPLE);
                DrawTexturePro(backCard, (Rectangle){0, 0, backCard.width, backCard.height}, (Rectangle){425, 77, 250, 375}, (Vector2){0, 0}, 0.0f, WHITE);
                DrawText("JOGADOR", 187, 11, 26, WHITE);
                DrawText("BOT", 523, 11, 26, WHITE);
                DrawText(TextFormat("%d", pontuacaoPlayer), 241, 43, 26, WHITE);
                DrawText(TextFormat("%d", pontuacaoBot), 541, 43, 26, WHITE);
    
    
                if(GuiButton((Rectangle){0 , 0, 50, 50},"debug button")){
                    printf("%s\n", maoJogador.nome);                   
                    printf("%d\n", maoJogador.poderDestrutivo);
                    printf("%d\n", maoJogador.velocidade);
                    printf("%d\n", maoJogador.alcance);
                    printf("%d\n", maoJogador.persistenciaDePoder);
                    printf("----------------------\n");

                    printf("----------------------\n");
                    printf("%s\n", maoBot.nome);
                    printf("%d\n", maoBot.poderDestrutivo);
                    printf("%d\n", maoBot.velocidade);
                    printf("%d\n", maoBot.alcance);
                    printf("%d\n", maoBot.persistenciaDePoder);
                    printf("----------------------\n");
                    printf("----------------------\n");
                    printf("player: %d\n", pontuacaoPlayer);
                    printf("bot: %d\n", pontuacaoBot);
                    printf("Turnos: %d\n", turnos);
                    printf("%d", estadoAtual);
                }
    
    
                if((turnos % 2) == 1){
                    if(estadoAtual == ESPERANDO_JOGADOR){
                        if(GuiButton((Rectangle){675,473,100,60},"#115#")){
                            PlaySound(buttonSound);
                            maoJogador = recebeCartaParaMao(deckPlayer);
                            maoBot = recebeCartaParaMao(deckBot);
                            estadoAtual = ESCOLHENDO_ATRIBUTO;
                            blockCarta1 = false;
                            blockCarta2 = false;
                        }
                    }
    
                    if(estadoAtual == ESCOLHENDO_ATRIBUTO){
                        DrawRectangle(205 ,523 ,390, 60, PURPLE);
                        listarCartaNoGerenciamento(maoJogador, &Carta, fundoCarta, &blockCarta1, fonteCarta, 125, 77);
    
                        DrawText("ESCOLHA UM ATRIBUTO PARA BATALHAR!", 150, 481, 24, BLACK);
    
                        if(GuiButton((Rectangle){210, 528, 80, 50}, "PODER")){
                            PlaySound(buttonSound);
                            batalha(maoJogador, maoBot, deckPlayer, deckBot, 32, &pontuacaoPlayer, &pontuacaoBot, maoJogador.poderDestrutivo, maoBot.poderDestrutivo);
                            estadoAtual = REVELANDO_CARTAS;
                            strcpy(escolha, "PODER");
                            
                        }
    
                        if(GuiButton((Rectangle){310, 528, 80, 50}, "ALCANCE")){
                            PlaySound(buttonSound);
                            batalha(maoJogador, maoBot, deckPlayer, deckBot, 32, &pontuacaoPlayer, &pontuacaoBot, maoJogador.alcance, maoBot.alcance);;
                            estadoAtual = REVELANDO_CARTAS;
                            strcpy(escolha, "ALCANCE");
                            
                        }

                        if(GuiButton((Rectangle){410, 528, 80, 50}, "VELOCIDADE")){
                            PlaySound(buttonSound);
                            batalha(maoJogador, maoBot, deckPlayer, deckBot, 32, &pontuacaoPlayer, &pontuacaoBot, maoJogador.velocidade, maoBot.velocidade);
                            estadoAtual = REVELANDO_CARTAS;
                            strcpy(escolha, "VELOCIDADE");
                            
                        }
    
    
                        if(GuiButton((Rectangle){510, 528, 80, 50}, "PERSISTENCIA")){
                            PlaySound(buttonSound);
                            batalha(maoJogador, maoBot, deckPlayer, deckBot, 32, &pontuacaoPlayer, &pontuacaoBot, maoJogador.persistenciaDePoder, maoBot.persistenciaDePoder);
                            estadoAtual = REVELANDO_CARTAS;
                            strcpy(escolha, "PERSISTENCIA");
                            
                        }
                    }
    
                    if(estadoAtual == REVELANDO_CARTAS){
    
                        listarCartaNoGerenciamento(maoJogador, &Carta, fundoCarta, &blockCarta1, fonteCarta, 125, 77);
                        listarCartaNoGerenciamento(maoBot, &Carta2, fundoCarta, &blockCarta2, fonteCarta, 425, 77);
                        DrawRectangle(329, 11, 141, 57, PURPLE);
                        DrawCenteredTextEx(fonteJogo, "VOCE ESCOLHEU", (Vector2){400, 27}, 13, 0, BLACK);
                        DrawCenteredTextEx(fonteJogo, TextFormat("%s", escolha), (Vector2){400, 53}, 14, 0, RED);

                        
                        if(GuiButton((Rectangle){310, 483, 180, 40}, "AVANCAR PARA O PROXIMO TURNO")){
                            vitoriaBot = verificaVitoriaBot(deckPlayer);
                            vitoriaPlayer = verificaVitoriaPlayer(deckBot);
                            PlaySound(buttonSound);
                            estadoAtual = ESPERANDO_BOT;
                            turnos++;
                            blockCarta1 = false;
                            blockCarta2 = false;    
                        }
                    }
    
                }else if((turnos % 2) == 0){
    
                    if(estadoAtual == ESPERANDO_BOT){
    
                        if(GuiButton((Rectangle){675,473,100,60},"#115#")){
    
                            PlaySound(buttonSound);
                            maoJogador = recebeCartaParaMao(deckPlayer);
                            maoBot = recebeCartaParaMao(deckBot);
                            botAcao(maoBot, maoJogador, deckBot, deckPlayer, &pontuacaoPlayer, &pontuacaoBot, escolha);
                            estadoAtual = MOSTRANDO_CARTA;
                            blockCarta1 = false;
                            blockCarta2 = false;
                        }
    
                    }
    
                    if(estadoAtual == MOSTRANDO_CARTA){
                        listarCartaNoGerenciamento(maoJogador, &Carta, fundoCarta, &blockCarta1, fonteCarta, 125, 77);
                        listarCartaNoGerenciamento(maoBot, &Carta2, fundoCarta, &blockCarta2, fonteCarta, 425, 77);
                        DrawRectangle(329, 11, 141, 57, PURPLE);
                        DrawCenteredTextEx(fonteJogo, "BOT ESCOLHEU", (Vector2){400, 27}, 13, 0, BLACK);
                        DrawCenteredTextEx(fonteJogo, TextFormat("%s", escolha), (Vector2){400, 53}, 14, 0, RED);
    
                        if(GuiButton((Rectangle){310, 483, 180, 40}, "AVANCAR PARA O PROXIMO TURNO")){
                            PlaySound(buttonSound);
                            estadoAtual = ESPERANDO_JOGADOR;
                            vitoriaBot = verificaVitoriaBot(deckPlayer);
                            vitoriaPlayer = verificaVitoriaPlayer(deckBot);
                            turnos++;
                            blockCarta1 = false;
                            blockCarta2 = false;
                        }
                    }
    
                }
    
                if(vitoriaBot == true && pontuacaoBot > pontuacaoPlayer){
                    DrawRectangle(0,0,800,600,(Color){0,0,0,255});
                    DrawText("VOCÊ PERDEU! TENTE NOVAMENTE", 100, 200, 36, RED);
                    if(GuiButton((Rectangle){295,407,211,47}, "Voltar ao menu")){
                        PlaySound(buttonSound);
                        estadoAtual = ESPERANDO_JOGADOR;
                        pontuacaoBot = 0;
                        pontuacaoPlayer = 0;
                        turnos = 1;
                        actualScreen = GAME_MENU;
                        vitoriaBot = false;
                        cartaJogadorExibida = false;
                        cartaBotExibida = false;
                    }
    
    
                }
    
                if(vitoriaPlayer == true && pontuacaoPlayer > pontuacaoBot){
                    DrawRectangle(0,0,800,600,(Color){0,0,0,255});
                    DrawText("PARABENS! VOCE VENCEU", 200, 200, 36, RED);
                    if(GuiButton((Rectangle){295,407,211,47}, "Voltar ao menu")){
                        PlaySound(buttonSound);
                        estadoAtual = ESPERANDO_JOGADOR;
                        pontuacaoBot = 0;
                        pontuacaoPlayer = 0;
                        turnos = 1;
                        actualScreen = GAME_MENU;
                        vitoriaPlayer = false;
                        cartaJogadorExibida = false;
                        cartaBotExibida = false;
    
                    }
                            
    
                }
    
                if((vitoriaPlayer == true && pontuacaoPlayer == pontuacaoBot) || (vitoriaBot == true && pontuacaoPlayer == pontuacaoBot)){
                    DrawRectangle(0,0,800,600,(Color){0,0,0,255});
                    DrawText("O JOGO TERMINOU EMPATADO", 200, 200, 36, RED);
                    if(GuiButton((Rectangle){295,407,211,47}, "Voltar ao menu")){
                        PlaySound(buttonSound);
                        estadoAtual = ESPERANDO_JOGADOR;
                        pontuacaoBot = 0;
                        pontuacaoPlayer = 0;
                        turnos = 1;
                        actualScreen = GAME_MENU;
                        vitoriaPlayer = false;
                        vitoriaBot = false;
                        cartaJogadorExibida = false;
                        cartaBotExibida = false;
    
                    }
                            
    
                }

            }
                


            EndDrawing();
        }

        if(actualScreen == DECK_MANAGEMENT){

            BeginDrawing();
            ClearBackground(BLACK);

            listarCartaNoGerenciamento(estandes[selecionaCarta], &Carta, fundoCarta, &blockCarta1, fonteCarta, 275, 137);

            if (GuiButton((Rectangle){305, 21, 191, 39}, "#23# Alterar Imagem"))
            {
                click_img = !click_img;
            }

            if (click_img == true)
            {

                for (int i = 0; i < 6; i++)
                {
                    edit[i] = false;
                }
                
                edit[5] = true;

                if (GuiTextBox((Rectangle){255, 77, 291, 39}, endereco, 100, edit[5]) == true && IsKeyPressed(KEY_ENTER)) {
                    loadImageToCard(&estandes[selecionaCarta], endereco, 174, 142);
                    click_img = false;
                    strcpy(endereco, ".\\assets\\mods\\");
                }
            }
            

            if(GuiSpinner((Rectangle){82, 197, 156, 43}, "Poder", &estandes[selecionaCarta].poderDestrutivo, 1, 100, edit[0])){
                for (int i = 0; i < 6; i++)
                {
                    edit[i] = false;
                }
                
                edit[0] = true;
            }

            if(GuiSpinner((Rectangle){82, 268, 156, 43}, "Velocidade", &estandes[selecionaCarta].velocidade, 1, 100, edit[1])){
                for (int i = 0; i < 6; i++)
                {
                    edit[i] = false;
                }
                
                edit[1] = true;
            }

            if(GuiSpinner((Rectangle){82, 339, 156, 43}, "Alcance", &estandes[selecionaCarta].alcance, 1, 100, edit[2])){
                for (int i = 0; i < 6; i++)
                {
                    edit[i] = false;
                }
                
                edit[2] = true;
            }

            if(GuiSpinner((Rectangle){82, 410, 156, 43}, "Persistência", &estandes[selecionaCarta].persistenciaDePoder, 1, 100, edit[3])){
                for (int i = 0; i < 6; i++)
                {
                    edit[i] = false;
                }
                
                edit[3] = true;
            }

            DrawRectangle(255, 533, 291, 39, WHITE);

            if(GuiTextBox((Rectangle){255, 533, 291, 39}, estandes[selecionaCarta].nome, 30, edit[4])){
                for (int i = 0; i < 6; i++)
                {
                    edit[i] = false;
                }
                
                edit[4] = true;
            }

            if(GuiButton((Rectangle){16,16,83,48}, "#121#")){
                actualScreen = GAME_DECK;
            }//If - Voltar pro GAME_DECK


            EndDrawing();
        }
    
    }

    armazenaDeckFinal(estandes);
 
    UnloadTexture(background);
    UnloadTexture(jojoimg); // Unload texture when done
    UnloadTexture(table);
    UnloadTexture(backCard);
    UnloadImage(icon);
    UnloadSound(buttonSound);
    UnloadSound(theme);
    UnloadTexture(fundoDeck);
    UnloadFont(fonteCarta);
    UnloadFont(fonteJogo);
    CloseWindow();

    return 0;
}