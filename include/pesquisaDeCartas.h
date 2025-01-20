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

/**
 * @brief Função usada para listar a carta em todas as funções pesquisa
 * 
 * @param estande pesquisado
 */
void listarCarta(Estande estande){
    printf("            -----CARTA-----\n");
    printf("            Nome: %s\n", estande.nome);
    printf("            id: %c%d\n", estande.letra, estande.numero);
    if(estande.super == true){
        printf("            Esta carta é o super trunfo\n");
    }
    printf("            -----ATRIBUTOS-----\n");
    printf("            Poder destrutivo: %d\n", estande.poderDestrutivo);
    printf("            Velocidade: %d\n", estande.velocidade);
    printf("            Alcance: %d\n", estande.alcance);
    printf("            Persistencia: %d\n\n", estande.persistenciaDePoder);
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

/**
 * @brief Pesquisa o estande pelo nome digitado pelo usuário
 * 
 * @param estandes = deck ou todas as cartas
 * @param nome pesquisado
 */
void pesquisarEstandeNome(Estande estandes[]){
    char pesquisa[30];

    printf("            Qual o nome do estande que deseja pesquisar?: ");
    lerString(pesquisa, 30);
    for(int i = 0; i < 32; i++){
//      printf("Comparando com: %s\n", estandes[i].nome); // debug
        if(strcasecmp(pesquisa, estandes[i].nome) == 0){
            listarCarta(estandes[i]);
            printf("\n");
            return;
        }
    }
    printf("            Estande não encontrado\n");
    return;
}

/**
 * @brief filtra as cartas pelo poder destrutivo delas
 * 
 * @param estandes 
 */
void pesquisarEstandePoderDestrutivo(Estande estandes[]){
    int auxiliar = 0; //verifica se achou alguma carta dentro do filtro
    int maximo;
    int minimo;

    do{
        printf("            Qual o poder maximo que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if(maximo < 0 || maximo > 100){
            printf("            Valor invalido\n");
        }
    }while(maximo < 0 || maximo > 100);

    do{
        printf("            E o minimo?: ");
        scanf("%d", &minimo);

        if(minimo < 0 || minimo > maximo){
            printf("            Valor invalido\n");
        }

    }while(minimo < 0 || minimo > maximo);

    for(int i = 0; i < 32; i++){
        if(estandes[i].poderDestrutivo <= maximo && estandes[i].poderDestrutivo >= minimo){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }
    return;
}

/**
 * @brief filtra as cartas pela velocidade
 * 
 * @param estandes 
 */
void pesquisarEstandeVelocidade(Estande estandes[]){
    int auxiliar = 0; //verifica se achou alguma carta dentro do filtro
    int maximo;
    int minimo;

    do{
        printf("            Qual a velocidade maxima que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if(maximo < 0 || maximo > 100){
            printf("            Valor invalido\n");

        }

    }while(maximo < 0 || maximo > 100);

    do{
        printf("            E a minima?: ");
        scanf("%d", &minimo);

        if(minimo < 0 || minimo > maximo){
            printf("            Valor invalido\n");
        }

    }while(minimo < 0 || minimo > maximo);

    for(int i = 0; i < 32; i++){
        if(estandes[i].velocidade <= maximo && estandes[i].velocidade >= minimo){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }
    return;
}


/**
 * @brief filtra as cartas pelo alcance
 * 
 * @param estandes 
 */
void pesquisarEstandeAlcance(Estande estandes[]){
    int auxiliar = 0; //verifica se achou alguma carta dentro do filtro
    int maximo;
    int minimo;

    do{
        printf("            Qual o alcance maximo que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if(maximo < 0 || maximo > 100){
            printf("            Valor invalido\n");
        }
    
    }while(maximo < 0 || maximo > 100);

    do{
        printf("            E o minimo?: ");
        scanf("%d", &minimo);

        if(minimo < 0 || minimo > maximo){
            printf("            Valor invalido\n");
        }
    
    }while(minimo < 0 || minimo > maximo);

    for(int i = 0; i < 32; i++){
        if(estandes[i].alcance <= maximo && estandes[i].alcance >= minimo){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n\n");
    }
    return;
}

/**
 * @brief filtra as cartas pela persistencia de poder
 * 
 * @param estandes 
 */
void pesquisarEstandePersistencia(Estande estandes[]){
    int auxiliar = 0; //verifica se achou alguma carta dentro do filtro
    int maximo;
    int minimo;

    do{
        printf("            Qual a persistencia de poder maxima que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if(maximo < 0 || maximo > 100){
            printf("            Valor invalido\n");
        }
    
    }while(maximo < 0 || maximo > 100);

    do{
        printf("            E a minima?: ");
        scanf("%d", &minimo);

        if(minimo < 0 || minimo > maximo){
            printf("            Valor invalido\n");
        }
    
    }while(minimo < 0 || minimo > maximo);

    for(int i = 0; i < 32; i++){
        if(estandes[i].persistenciaDePoder <= maximo && estandes[i].persistenciaDePoder >= minimo){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n\n");
    }
    return;
}

void pesquisaCartaLetra(Estande estandes[]){
    int auxiliar = 0;
    char pesquisa;

    printf("            Que letra deseja pesquisar?: ");
    setbuf(stdin, NULL);
    scanf("%c", &pesquisa);
    pesquisa = toupper(pesquisa);

    for(int i = 0; i < 32; i++){
        if(estandes[i].letra == pesquisa){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n\n");
    }

    return;
}

void pesquisaCartaNumero(Estande estandes[]){
    int auxiliar = 0;
    int pesquisa;

    printf("            Que numero deseja pesquisar?: ");
    scanf("%d", &pesquisa);

    for(int i = 0; i < 32; i++){
        if(estandes[i].numero == pesquisa){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n\n");
    }

    return;
}

int pesquisarEstandeNomeRetornoPosicao(Estande estandes[]){
    char pesquisa[30];

    printf("\n            Qual o nome do estande que deseja pesquisar?: ");
    lerString(pesquisa, 30);
    for(int i = 0; i < 32; i++){
//      printf("Comparando com: %s\n", estandes[i].nome); // debug
        if(strcasecmp(pesquisa, estandes[i].nome) == 0){
            listarCarta(estandes[i]);
            return i;
        }
    }
    printf("            Estande não encontrado\n\n");
    return -1;
}

#endif