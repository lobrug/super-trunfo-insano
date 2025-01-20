#include "menu.h"
#include "structEstandes.h"
#include "pesquisaDeCartas.h"
#include "gerenciamentoDeDeck.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

/**
 * @brief Menu para selecionar diferentes opções de pesquisa de cartas no deck.
 * 
 * O menu apresenta ao usuário uma lista de critérios pelos quais ele pode pesquisar
 * as cartas, como nome, poder destrutivo, velocidade, alcance, persistência de poder, 
 * letra e número. Após a seleção, a função correspondente à pesquisa é chamada.
 * 
 * @param deck Array contendo todas as cartas disponíveis.
 */
void menuPesquisa(Estande deck[]) {
    int seleciona_pesquisa = 1; // Armazena a opção selecionada pelo usuário.

    do {
        // Exibe o menu de opções para o usuário.
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

        // Valida a entrada do usuário.
        if (seleciona_pesquisa < 1 || seleciona_pesquisa > 7) {
            printf("Essa opção não existe! Insira novamente.\n");
            printf("\n");
        }
    } while (seleciona_pesquisa < 1 || seleciona_pesquisa > 7); // Repete até que a opção seja válida.

    // Executa a função correspondente à opção escolhida pelo usuário.
    switch (seleciona_pesquisa) {
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
    } // Fim do switch-case.

    return;
} // Fim da função menuPesquisa.

/**
 * @brief Menu para alterar atributos de uma carta específica do deck.
 * 
 * O menu permite ao usuário selecionar uma carta pelo nome e modificar
 * atributos como nome, poder destrutivo, velocidade, alcance e persistência de poder.
 * Após realizar as alterações, o usuário pode finalizar e visualizar as mudanças feitas.
 * 
 * @param deck Array contendo todas as cartas disponíveis.
 */
void menuAlteraCarta(Estande deck[]) {
    int posicao = pesquisarEstandeNomeRetornoPosicao(deck); // Busca a posição da carta pelo nome.

    if (posicao > -1) { // Verifica se a carta foi encontrada.
        while (1) { // Loop para realizar alterações enquanto o usuário desejar.
            int opcao; // Armazena a opção de alteração escolhida pelo usuário.
            printf("            Menu para alterar cartas\n");
            printf("            1 - Alterar Nome.\n");
            printf("            2 - Alterar poder destrutivo.\n");
            printf("            3 - Alterar Velocidade.\n");
            printf("            4 - Alterar Alcance.\n");
            printf("            5 - Alterar persistência de poder.\n");
            printf("            6 - Fechar menu.\n\n");
            
            printf("            Insira a opção desejada: ");
            scanf("%d", &opcao);

            // Se a opção for 6, encerra o menu e exibe a carta alterada.
            if (opcao == 6) {
                printf("            A seguinte carta ficou assim: \n");
                listarCarta(deck[posicao]); // Exibe a carta alterada.
                return;
            } else {
                alterarCarta(&deck[posicao], opcao); // Chama a função para alterar o atributo selecionado.
            }
        }
    }

    return;
} // Fim da função menuAlteraCarta.

/**
 * @brief Menu para inserir uma nova carta no deck, exigindo antes a exclusão de uma carta existente.
 * 
 * Esta função permite ao usuário selecionar uma carta para exclusão e, em seguida, inserir uma nova carta no lugar.
 * A operação exige confirmação antes de excluir a carta selecionada.
 * 
 * @param deck Array de cartas (deck) no qual a nova carta será inserida.
 */
void menuInsereCarta(Estande deck[]) {
    // Exibe uma mensagem informando ao usuário sobre o pré-requisito de exclusão.
    printf("\n            Para inserir uma carta, antes você deverá excluir uma carta do seu deck!\n");

    // Pesquisa a posição da carta que será excluída pelo nome.
    int posicao = pesquisarEstandeNomeRetornoPosicao(deck);
    int seleciona; // Variável para armazenar a escolha do usuário.

    if (posicao == -1) {
        // Se nenhuma carta for encontrada, a função termina.
        return;
    } else {
        // Confirmação da exclusão da carta encontrada.
        printf("                Tem certeza que irá excluir essa carta?\n");
        printf("                1 - SIM\n");
        printf("                2 - NÃO\n");
        printf("                Selecione sua opção: ");
        scanf("%d", &seleciona);

        if (seleciona == 1) {
            // Exclui a carta selecionada e permite a inserção de uma nova carta no mesmo local.
            excluirCarta(&deck, &deck[posicao]); 
            recebeCarta(&deck[posicao]); // Recebe os dados para a nova carta.
        } else {
            // Caso o usuário cancele a operação, a função retorna ao menu anterior.
            return;
        }
    }

    return;
} // Fim da função menuInsereCarta.


/**
 * @brief Menu de gerenciamento de decks que permite ao usuário realizar diversas operações.
 * 
 * Este menu permite:
 * - Selecionar um dos dois decks para gerenciar.
 * - Exportar o conteúdo completo dos decks para um arquivo CSV.
 * - Listar todas as cartas de um deck.
 * - Pesquisar, alterar, inserir ou excluir cartas.
 * 
 * @param deck Primeiro deck de cartas.
 * @param deck2 Segundo deck de cartas.
 */
void menuGerenciamento(Estande deck[], Estande deck2[]) {
    int seleciona_deck; // Armazena a escolha do usuário para o deck.
    int seleciona_funcao; // Armazena a escolha do usuário para a operação.

    do {
        // Menu para seleção de deck ou exportação.
        printf("\n    1 - DECK 1\n");
        printf("    2 - DECK 2\n");
        printf("    3 - EXPORTAR DECK COMPLETO PARA UM ARQUIVO CSV\n");
        printf("    Selecione o deck à ser gerenciado: ");

        scanf("%d", &seleciona_deck);
        if (seleciona_deck < 1 || seleciona_deck > 3) {
            printf("Esse deck não existe, insira novamente!\n");
        }
    } while (seleciona_deck < 1 || seleciona_deck > 3); // Fim do do-while para seleção do deck.

    printf("\n");
    if (seleciona_deck == 3) {
        // Exportação dos decks para um arquivo CSV.
        Estande estandes[32];
        char nome_csv[100];
        printf("Insira o nome do arquivo que será salvo, ou que será criado(.csv ao final): ");
        lerString(nome_csv, 100);

        FILE *exportaCSV = fopen(nome_csv, "w");
        fprintf(exportaCSV, "Categoria,Número,Nome do Stand,Super,Poder Destrutivo,Velocidade,Alcance,Persistência\n");
        for (int i = 0, j = 0; i < 32; i++) {
            if (i < 16) {
                estandes[i] = deck[i];
            } else {
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
                    estandes[i].persistenciaDePoder);
        } // Fim do for para exportação.

        fclose(exportaCSV);
        return;
    } // Fim da exportação para CSV.

    do {
        // Menu de operações no deck selecionado.
        printf("        1 - LISTAR TODAS AS CARTAS\n");
        printf("        2 - PESQUISAR CARTAS\n");
        printf("        3 - ALTERAR CARTA\n");
        printf("        4 - INSERIR/EXCLUIR CARTAS\n");
        printf("        5 - SAIR PARA O MENU INICIAL\n");
        printf("        Selecione uma opção: ");
        scanf("%d", &seleciona_funcao);

        if (seleciona_funcao < 1 || seleciona_funcao > 5) {
            printf("Essa opção não existe, insira novamente!\n");
            printf("\n");
        }
        if (seleciona_funcao == 5) {
            return; // Retorna ao menu inicial.
        }

        switch (seleciona_funcao) {
            case 1:
                // Listar todas as cartas do deck selecionado.
                for (int i = 0; i < 16; i++) {
                    if (seleciona_deck == 1) {
                        listarCarta(deck[i]);
                    } else {
                        listarCarta(deck2[i]);
                    }
                } // Fim do for para listar cartas.
                break;

            case 2:
                // Pesquisar cartas no deck selecionado.
                if (seleciona_deck == 1) {
                    menuPesquisa(deck);
                } else {
                    menuPesquisa(deck2);
                }
                break;

            case 3:
                // Alterar cartas no deck selecionado.
                if (seleciona_deck == 1) {
                    menuAlteraCarta(deck);
                } else {
                    menuAlteraCarta(deck2);
                }
                break;

            case 4:
                // Inserir ou excluir cartas no deck selecionado.
                if (seleciona_deck == 1) {
                    menuInsereCarta(deck);
                } else {
                    menuInsereCarta(deck2);
                }
                break;

            default:
                break;
        } // Fim do switch-case para as operações.

    } while (seleciona_funcao != 5); // Fim do do-while para as operações no deck.

    printf("\n");
    return;
} // Fim da função menuGerenciamento.


/**
 * @brief Menu inicial do programa que permite ao usuário acessar diferentes funcionalidades.
 * 
 * O menu inicial apresenta ao usuário três opções:
 * - Jogar (ainda não implementado).
 * - Gerenciamento de decks.
 * - Fechar o jogo.
 * O usuário pode navegar pelas opções até decidir encerrar o programa.
 * 
 * @param deck Primeiro deck de cartas disponível no jogo.
 * @param deck2 Segundo deck de cartas disponível no jogo.
 */
void menuInicial(Estande deck[], Estande deck2[]) {
    int seleciona_menu; // Armazena a opção selecionada pelo usuário no menu.

    do {
        // Exibe as opções do menu inicial.
        printf("\n1 - JOGAR\n");
        printf("2 - GERENCIAMENTO DE DECKS\n");
        printf("3 - FECHAR JOGO\n");
        printf("Selecione uma opção: ");
        scanf("%d", &seleciona_menu);

        // Realiza a ação correspondente à opção escolhida.
        switch (seleciona_menu) {
            case 1: 
                printf("\nModo ainda não disponível!\n\n");
                break;

            case 2: 
                menuGerenciamento(deck, deck2); // Chama o menu de gerenciamento de decks.
                break;

            case 3: 
                return; // Encerra o programa.
                break;

            default: 
                break;
        } // Fim do switch-case.

        // Verifica se a entrada do usuário é inválida.
        if (seleciona_menu < 1 || seleciona_menu > 3) {
            printf("\nEssa opção não existe, tente novamente!\n");
        }
    } while (seleciona_menu != 3); // Repete enquanto o usuário não escolher fechar o jogo.

    return;
} // Fim da função menuInicial.
