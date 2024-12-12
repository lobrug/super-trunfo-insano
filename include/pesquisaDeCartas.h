#ifndef pesquisaDeCartas_H
#define pesquisaDeCartas_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "structEstandes.h"

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
    printf("-----CARTA-----\n");
    printf("Nome: %s\n", estande.nome);
    printf("id: %c%d\n", estande.letra, estande.numero);
    if(estande.super == true){
        printf("Esta carta é o super trunfo\n");
    }
    printf("-----ATRIBUTOS-----\n");
    printf("Poder destrutivo: %d\n", estande.poderDestrutivo);
    printf("Velocidade: %d\n", estande.velocidade);
    printf("Alcance: %d\n", estande.alcance);
    printf("Persistencia: %d\n", estande.persistenciaDePoder);
}

/**
 * @brief Pesquisa o estande pelo nome digitado pelo usuário
 * 
 * @param estandes = deck ou todas as cartas
 * @param nome pesquisado
 */
void pesquisarEstandeNome(Estande estandes[]){
    char pesquisa[30];

    printf("Qual o nome do estande que deseja pesquisar?: ");
    lerString(pesquisa, 30);
    for(int i = 0; i < 32; i++){
//      printf("Comparando com: %s\n", estandes[i].nome); // debug
        if(strcasecmp(pesquisa, estandes[i].nome) == 0){
            listarCarta(estandes[i]);
            return;
        }
    }
    printf("Estande não encontrado\n");
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
        printf("Qual o poder maximo que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if(maximo < 0 || maximo > 100){
            printf("Valor invalido\n");
        }
    }while(maximo < 0 || maximo > 100);

    do{
        printf("E o minimo?: ");
        scanf("%d", &minimo);

        if(minimo < 0 || minimo > maximo){
            printf("Valor invalido\n");
        }

    }while(minimo < 0 || minimo > maximo);

    for(int i = 0; i < 32; i++){
        if(estandes[i].poderDestrutivo <= maximo && estandes[i].poderDestrutivo >= minimo){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("Não foi encontrado nenhuma carta com o filtro expecificado\n");
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
        printf("Qual a velocidade maxima que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if(maximo < 0 || maximo > 100){
            printf("Valor invalido\n");

        }

    }while(maximo < 0 || maximo > 100);

    do{
        printf("E a minima?: ");
        scanf("%d", &minimo);

        if(minimo < 0 || minimo > maximo){
            printf("Valor invalido\n");
        }

    }while(minimo < 0 || minimo > maximo);

    for(int i = 0; i < 32; i++){
        if(estandes[i].velocidade <= maximo && estandes[i].velocidade >= minimo){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("Não foi encontrado nenhuma carta com o filtro expecificado\n");
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
        printf("Qual o alcance maximo que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if(maximo < 0 || maximo > 100){
            printf("Valor invalido\n");
        }
    
    }while(maximo < 0 || maximo > 100);

    do{
        printf("E o minimo?: ");
        scanf("%d", &minimo);

        if(minimo < 0 || minimo > maximo){
            printf("Valor invalido\n");
        }
    
    }while(minimo < 0 || minimo > maximo);

    for(int i = 0; i < 32; i++){
        if(estandes[i].alcance <= maximo && estandes[i].alcance >= minimo){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("Não foi encontrado nenhuma carta com o filtro expecificado\n");
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
        printf("Qual a persistencia de poder maxima que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if(maximo < 0 || maximo > 100){
            printf("Valor invalido\n");
        }
    
    }while(maximo < 0 || maximo > 100);

    do{
        printf("E a minima?: ");
        scanf("%d", &minimo);

        if(minimo < 0 || minimo > maximo){
            printf("Valor invalido\n");
        }
    
    }while(minimo < 0 || minimo > maximo);

    for(int i = 0; i < 32; i++){
        if(estandes[i].persistenciaDePoder <= maximo && estandes[i].persistenciaDePoder >= minimo){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }
    return;
}

void pesquisaCartaLetra(Estande estandes[]){
    int auxiliar = 0;
    char pesquisa;

    printf("Que letra deseja pesquisar?: ");
    scanf(" %c", &pesquisa);

    for(int i = 0; i < 32; i++){
        if(estandes[i].letra == pesquisa){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }

    return;
}

void pesquisaCartaNumero(Estande estandes[]){
    int auxiliar = 0;
    int pesquisa;

    printf("Que numero deseja pesquisar?: ");
    scanf("%d", &pesquisa);

    for(int i = 0; i < 32; i++){
        if(estandes[i].numero == pesquisa){
            listarCarta(estandes[i]);
            auxiliar = 1;
        }
    }

    if(auxiliar == 0){
        printf("Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }

    return;
}

int pesquisarEstandeNomeRetornoPosicao(Estande estandes[]){
    char pesquisa[30];

    printf("Qual o nome do estande que deseja pesquisar?: ");
    lerString(pesquisa, 30);
    for(int i = 0; i < 32; i++){
//      printf("Comparando com: %s\n", estandes[i].nome); // debug
        if(strcasecmp(pesquisa, estandes[i].nome) == 0){
            listarCarta(estandes[i]);
            return i;
        }
    }
    printf("Estande não encontrado\n");
    return -1;
}

#endif