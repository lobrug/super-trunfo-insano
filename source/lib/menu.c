#include "menu.h"
#include "structEstandes.h"
#include "pesquisaDeCartas.h"
#include "gerenciamentoDeDeck.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void menuPesquisa(Estande deck[]){

    int seleciona_pesquisa = 1;

    do  
    {
        printf("\n            De qual maneira você prefere fazer sua pesquisa?\n");
        printf("            1 - NOME DO STAND\n");
        printf("            2 - PODER DESTRUTIVO DO STAND\n");
        printf("            3 - VELOCIDADE DO STAND\n");
        printf("            4 - ALCANDE DO STAND\n");
        printf("            5 - PERSISTÊNCIA DO STAND\n");
        printf("            6 - LETRA DA CARTA\n");
        printf("            7 - NUMERO DA CARTA\n");
        printf("            Selecione sua opção: ");
        scanf("%d", &seleciona_pesquisa);
        printf("\n");

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
            printf("            Menu para alterar cartas\n");
            printf("            1 - ALterar Nome.\n");
            printf("            2 - Alterar poder destrutivo.\n");
            printf("            3 - Alterar Velocidade.\n");
            printf("            4 - Alterar Alcance\n");
            printf("            5 - Alterar persistencia de poder\n");
            printf("            6 - Fechar menu\n\n");
            
            printf("            Insira a opção de desejada: ");
            scanf("%d", &opcao);
            if (opcao == 6)
            {
                printf("            A seguinte carta ficou assim: \n");
                listarCarta(deck[posicao]);
                return;
            }else{
                alterarCarta(&deck[posicao], opcao);
            }
        }    
    }

    return;
}//menuAlteraCarta

void menuInsereCarta(Estande deck[]){

    printf("\n            Para inserir uma carta, antes você deverá excluir uma carta do seu deck!\n");
    int posicao = pesquisarEstandeNomeRetornoPosicao(deck);

    int seleciona;

    if (posicao == -1)
    {
        return;
    }else{

        printf("                Tem certeza que irá excluir essa carta?\n");
        printf("                1 - SIM\n");
        printf("                2 - NÃO\n");
        printf("                Selecione sua opção: ");
        scanf("%d", &seleciona);

        if (seleciona == 1)
        {
            excluirCarta(&deck, &deck[posicao]);

            recebeCarta(&deck[posicao]);

        }else{

            return;
        }

    }
    


    return;
}//menuInsereCarta

void menuGerenciamento(Estande deck[], Estande deck2[]){

    int seleciona_deck;
    int seleciona_funcao;

    do
    {
        printf("\n    1 - DECK 1\n");
        printf("    2 - DECK 2\n");
        printf("    3 - EXPORTAR DECK COMPLETO PARA UM ARQUIVO CSV\n");
        printf("    Selecione o deck à ser gerenciado: ");

        scanf("%d", &seleciona_deck);
        if (seleciona_deck < 1 || seleciona_deck > 3)
        {
            printf("Esse deck não existe, insira novamente!\n");
        }
        
    } while (seleciona_deck < 1 || seleciona_deck > 3);

    printf("\n");
    if (seleciona_deck == 3)
    {
        Estande estandes[32];
        char nome_csv[100];
        printf("Insira o nome do arquivo que será salvo, ou que será criado(.csv ao final): ");
        lerString(nome_csv, 100);

        FILE *exportaCSV = fopen(nome_csv, "w");
        fprintf(exportaCSV, "Categoria,Número,Nome do Stand,Super,Poder Destrutivo,Velocidade,Alcance,Persistência\n");
        for (int i = 0, j = 0; i < 32; i++)
        {
            if (i < 16)
            {
                estandes[i] = deck[i];
            }else{
                estandes[i] = deck2[j];
                j++;
            }
            
            fprintf(exportaCSV, "%c,%d,%s,%d,%d,%d,%d,%d\n",
                    estandes[i].letra, 
                    estandes[i].numero, 
                    estandes[i].nome, 
                    estandes[i].super, 
                    estandes[i].poderDestrutivo, 
                    estandes[i].velocidade, 
                    estandes[i].alcance, 
                    estandes[i].persistenciaDePoder
                    );
        }
        fclose(exportaCSV);
        return;
    }
    
    do
    {
        printf("        1 - LISTAR TODAS AS CARTAS\n");
        printf("        2 - PESQUISAR CARTAS\n");
        printf("        3 - ALTERAR CARTA\n");
        printf("        4 - INSERIR/EXCLUIR CARTAS\n");
        printf("        5 - SAIR PARA O MENU INICIAL\n");
        printf("        Selecione uma opção: ");
        scanf("%d", &seleciona_funcao);

        if (seleciona_funcao < 1 || seleciona_funcao > 5)
        {
            printf("Essa opção não existe, insira novamente!\n");
            printf("\n");
        }
        if (seleciona_funcao == 5)
        {
            return;
        }
        
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

            if (seleciona_deck == 1)
            {
                menuInsereCarta(deck);
            }else{
                menuInsereCarta(deck2);
            }

            break;

        default:
            break;
        }

    } while (seleciona_funcao != 5);

    printf("\n");


    return;
}//menuGerenciamento

void menuInicial(Estande deck[], Estande deck2[]){

    int seleciona_menu;
    do
    {
        printf("\n1 - JOGAR\n");
        printf("2 - GERENCIAMENTO DE DECKS\n");
        printf("3 - FECHAR JOGO\n");
        printf("Selecione uma opção: ");
        scanf("%d", &seleciona_menu);

        switch (seleciona_menu)
        {
        case 1: printf("\nModo ainda não disponível!\n\n");
            break;
        
        case 2: menuGerenciamento(deck, deck2);
            break;
        
        case 3:
            return;
            break;
        
        default: 
            break;
        }

        if (seleciona_menu < 1 || seleciona_menu > 3)
        {
            printf("\nEssa opção não existe, tente novamente!\n");
        }
        

    } while (seleciona_menu != 3);
    
    return;
}//menuInicial

