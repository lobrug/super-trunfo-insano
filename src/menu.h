#include "structEstandes.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void menuInicial(){

    printf("1 - JOGAR\n");
    printf("2 - GERENCIAMENTO DE DECKS\n");
    printf("3 - FECHAR JOGO\n");
    printf("Selecione uma opção: \n");

    return;
}//menuInicial

void menuGerenciamento(Estande deck[], Estande deck2[]){

    int seleciona_deck;
    int seleciona_funcao;

    do
    {
        printf("1 - DECK 1\n");
        printf("2 - DECK 2\n");
        printf("Selecione o deck à ser gerenciado: \n");

        scanf("%d", &seleciona_deck);
        if (seleciona_deck < 1 || seleciona_deck > 2)
        {
            printf("Esse deck não existe, insira novamente!\n");
        }
        
    } while (seleciona_deck < 1 || seleciona_deck > 2);

    printf("\n");

    do
    {
        printf("1 - LISTAR TODAS AS CARTAS\n");
        printf("2 - PESQUISAR CARTAS\n");
        printf("3 - INSERIR CARTAS\n");
        printf("Selecione uma opção: ");
        scanf("%d", &seleciona_funcao);

        if (seleciona_funcao < 1 || seleciona_funcao > 3)
        {
            printf("Essa opção não existe, insira novamente!\n");
            printf("\n");
        }
        
    } while (seleciona_funcao < 1 || seleciona_funcao > 3);

    switch (seleciona_funcao)
    {
    case 1:
        
        break;
    
    case 2:

        break;
    
    case 3:

        break;
    
    default:
        break;
    }
        
    
    


}//menuGerenciamento