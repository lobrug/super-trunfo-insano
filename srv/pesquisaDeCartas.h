#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "structEstandes.h"

/**
 * @brief Função usada para listar a carta em todas as funções pesquisa
 * 
 * @param estande pesquisado
 */
void listarCarta(Estande* estande){
    printf("Nome: %s\n", estande->nome);
    printf("id: %c%d\n", estande->letra, estande->numero);
    if(estande->super == true){
        printf("Esta carta é o super trunfo\n");
    }
    printf("-----ATRIBUTOS-----\n");
    printf("Poder destrutivo: %d\n", estande->poderDestrutivo);
    printf("Velocidade: %d\n", estande->velocidade);
    printf("Alcance: %d\n", estande->alcance);
    printf("Persistencia: %d\n", estande->persistenciaDePoder);

}

/**
 * @brief Pesquisa o estande pelo nome digitado pelo usuário
 * 
 * @param estandes = deck ou todas as cartas
 * @param nome pesquisado
 */
void pesquisarEstandeNome(Estande estandes[], char* nome){
    for(int i = 0; i < sizeof(estandes); i++){
        if(strcmp(nome, estandes[i].nome)==0){
            listarCarta(&estandes[i]);
            return;
        }
    }
    printf("Estande não encontrado\n");
}

/**
 * @brief filtra as cartas pelo poder destrutivo delas
 * 
 * @param estandes 
 */
void pesquisarEstandePoderDestrutivo(Estande estandes[]){
    int verificacao = 0; //verifica se achou alguma carta dentro do filtro
    int maximo;
    int minimo;
    printf("Qual o poder maximo que você deseja pesquisar?: ");
    scanf("%d", &maximo);
    printf("E o minimo?: ");
    scanf("%d", &minimo);

    for(int i = 0; i < sizeof(estandes); i++){
        if(estandes[i].poderDestrutivo < maximo && estandes[i].poderDestrutivo > minimo){
            listarCarta(&estandes[i]);
            verificacao = 1;
        }
    }

    if(verificacao == 0){
        printf("Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }
}

/**
 * @brief filtra as cartas pela velocidade
 * 
 * @param estandes 
 */
void pesquisarEstandeVelocidade(Estande estandes[]){
    int verificacao = 0; //verifica se achou alguma carta dentro do filtro
    int maximo;
    int minimo;
    printf("Qual a velocidade maxima que você deseja pesquisar?: ");
    scanf("%d", &maximo);
    printf("E a minima?: ");
    scanf("%d", &minimo);

    for(int i = 0; i < sizeof(estandes); i++){
        if(estandes[i].velocidade < maximo && estandes[i].velocidade > minimo){
            listarCarta(&estandes[i]);
            verificacao = 1;
        }
    }

    if(verificacao == 0){
        printf("Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }
}


/**
 * @brief filtra as cartas pelo alcance
 * 
 * @param estandes 
 */
void pesquisarEstandeAlcance(Estande estandes[]){
    int verificacao = 0; //verifica se achou alguma carta dentro do filtro
    int maximo;
    int minimo;
    printf("Qual o alcance maximo que você deseja pesquisar?: ");
    scanf("%d", &maximo);
    printf("E o minimo?: ");
    scanf("%d", &minimo);

    for(int i = 0; i < sizeof(estandes); i++){
        if(estandes[i].alcance < maximo && estandes[i].alcance > minimo){
            listarCarta(&estandes[i]);
            verificacao = 1;
        }
    }

    if(verificacao == 0){
        printf("Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }
}

/**
 * @brief filtra as cartas pela persistencia de poder
 * 
 * @param estandes 
 */
void pesquisarEstandePersistencia(Estande estandes[]){
    int verificacao = 0; //verifica se achou alguma carta dentro do filtro
    int maximo;
    int minimo;
    printf("Qual a persistencia de poder maxima que você deseja pesquisar?: ");
    scanf("%d", &maximo);
    printf("E a minima?: ");
    scanf("%d", &minimo);

    for(int i = 0; i < sizeof(estandes); i++){
        if(estandes[i].persistenciaDePoder < maximo && estandes[i].persistenciaDePoder > minimo){
            listarCarta(&estandes[i]);
            verificacao = 1;
        }
    }

    if(verificacao == 0){
        printf("Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }
}