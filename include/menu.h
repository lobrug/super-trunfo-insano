#include "structEstandes.h"
#include "pesquisaDeCartas.h"
#include "gerenciamentoDeDeck.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void menuPesquisa(Estande deck[]){

    int seleciona_pesquisa;

    do
    {
        printf("De qual maneira você prefere fazer sua pesquisa?\n");
        printf("1 - NOME DO STAND\n");
        printf("2 - PODER DESTRUTIVO DO STAND\n");
        printf("3 - VELOCIDADE DO STAND\n");
        printf("4 - ALCANDE DO STAND\n");
        printf("5 - PERSISTÊNCIA DO STAND\n");
        printf("6 - LETRA DA CARTA\n");
        printf("7 - NUMERO DA CARTA\n");

        if (seleciona_pesquisa < 1 || seleciona_pesquisa > 7)
        {
            printf("Essa opção não existe! Insira novamente.\n");
            printf("\n");
        }
        
    } while (seleciona_pesquisa < 1 || seleciona_pesquisa > 7);

    switch (seleciona_pesquisa)
    {
    case 1: pesquisarEstandeNome(deck);
        break;

    case 2: pesquisarEstandePoderDestrutivo(deck);
        break;
    
    case 3: pesquisarEstandeVelocidade(deck);
        break;

    case 4: pesquisarEstandeAlcance(deck);
        break;

    case 5: pesquisarEstandePersistencia(deck);
        break;
    
    case 6: pesquisaCartaLetra(deck);
        break;
    
    case 7: pesquisaCartaNumero(deck);
        break;
    
    default:
        break;
    }//Switch - case
    
    return;
}//menuPesquisa

void menuAlteraCarta(Estande deck[]){
    
    int posicao = pesquisarEstandeNomeRetornoPosicao(deck);
    if (posicao > -1)
    {
        while (1)
        {
            int opcao;
            printf("Menu para alterar cartas\n");
            printf("1 - ALterar Nome.\n");
            printf("2 - Alterar poder destrutivo.\n");
            printf("3 - Alterar Velocidade.\n");
            printf("4 - Alterar Alcance\n");
            printf("5 - Alterar persistencia de poder\n");
            printf("6 - Fechar menu\n\n");
            
            printf("Insira a opção de desejada: ");
            scanf("%d", &opcao);
            if (opcao == 6)
            {
                printf("A seguinte carta ficou assim: \n");
                listarCarta(deck[posicao]);
                return;
            }else{
                alterarCarta(&deck[posicao], opcao);
            }
        }    
    }

    return;
}//menuAlteraCarta

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
        printf("3 - ALTERAR CARTA");
        printf("4 - EXCLUIR CARTA");
        printf("5 - INSERIR CARTAS\n");
        printf("Selecione uma opção: ");
        scanf("%d", &seleciona_funcao);

        if (seleciona_funcao < 1 || seleciona_funcao > 3)
        {
            printf("Essa opção não existe, insira novamente!\n");
            printf("\n");
        }
        
    } while (seleciona_funcao < 1 || seleciona_funcao > 3);

    printf("\n");

    switch (seleciona_funcao)
    {
    case 1:
        
        for (int i = 0; i < 16; i++)
        {
            if (seleciona_deck == 1)
            {
                listarCarta(deck[i]);
            }else
            {
                listarCarta(deck2[i]);
            }
            
        }

        break;
    
    case 2:
        
        if (seleciona_deck == 1)
        {
            menuPesquisa(deck);
        }else{
            menuPesquisa(deck2);
        }

        break;
    
    case 3:

        if (seleciona_deck == 1)
        {
            menuAlteraCarta(deck);
        }else{
            menuAlteraCarta(deck2);
        }
        

        break;
    case 4:
        //mesmo caso aq
        break;

    case 5:
        
        break;
    default:
        break;
    }

    return;
}//menuGerenciamento

void menuInicial(Estande deck[], Estande deck2[]){

    int seleciona_menu;
    do
    {
        printf("1 - JOGAR\n");
        printf("2 - GERENCIAMENTO DE DECKS\n");
        printf("3 - FECHAR JOGO\n");
        printf("Selecione uma opção: \n");
    } while (seleciona_menu < 1 || seleciona_menu > 3);
    

    switch (seleciona_menu)
    {
    case 1: printf("Modo ainda não disponível!\n");
        break;
    
    case 2: menuGerenciamento(deck, deck2);
        break;
    
    case 3: exit(0);
        break;
    
    default: 
        break;
    }

    return;
}//menuInicial
