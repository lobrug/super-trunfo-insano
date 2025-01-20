#include "gerenciamentoDeDeck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "structEstandes.h"
#include "pesquisaDeCartas.h"

/**
 * @file gerenciamentoDeCartas.c
 * @brief Implementa funcionalidades para gerenciar cartas de um deck.
 * 
 * Este arquivo contém as funções necessárias para cadastrar, listar, alterar, excluir e pesquisar cartas 
 * no sistema. O objetivo é permitir a manipulação dinâmica das cartas, garantindo flexibilidade no 
 * gerenciamento dos decks.
 */

/**
 * @brief Recebe os dados de uma nova carta e preenche a estrutura correspondente.
 * 
 * Esta função solicita ao usuário os atributos de um novo Stand (carta). Para cada atributo, 
 * verifica se o valor informado está dentro dos limites aceitáveis (1 a 100), permitindo 
 * apenas entradas válidas. 
 * 
 * @param cartaNova Ponteiro para a estrutura que armazenará os dados da nova carta.
 */
void recebeCarta(Estande *cartaNova) {
    printf("                Insira o nome do seu novo Stand: ");
    lerString(cartaNova->nome, 30); // Lê o nome da carta com limite de 30 caracteres.

    // Recebe e valida o poder destrutivo da carta.
    do {
        printf("                Insira o poder destrutivo do novo Stand: ");
        scanf("%d", &cartaNova->poderDestrutivo);
        if (cartaNova->poderDestrutivo > 100 || cartaNova->poderDestrutivo < 1) {
            printf("                Valor inválido, insira novamente!\n");
        }
    } while (cartaNova->poderDestrutivo > 100 || cartaNova->poderDestrutivo < 1); // Fim do bloco de validação do poder destrutivo.

    // Recebe e valida a velocidade da carta.
    do {
        printf("                Insira a velocidade do novo Stand: ");
        scanf("%d", &cartaNova->velocidade);
        if (cartaNova->velocidade > 100 || cartaNova->velocidade < 1) {
            printf("                Valor inválido, insira novamente!\n");
        }
    } while (cartaNova->velocidade > 100 || cartaNova->velocidade < 1); // Fim do bloco de validação da velocidade.

    // Recebe e valida o alcance da carta.
    do {
        printf("                Insira o alcance do novo Stand: ");
        scanf("%d", &cartaNova->alcance);
        if (cartaNova->alcance > 100 || cartaNova->alcance < 1) {
            printf("                Valor inválido, insira novamente!\n");
        }
    } while (cartaNova->alcance > 100 || cartaNova->alcance < 1); // Fim do bloco de validação do alcance.

    // Recebe e valida a persistência de poder da carta.
    do {
        printf("                Insira a persistencia de poder do novo Stand: ");
        scanf("%d", &cartaNova->persistenciaDePoder);
        if (cartaNova->persistenciaDePoder > 100 || cartaNova->persistenciaDePoder < 1) {
            printf("                Valor inválido, insira novamente!\n");
        }
    } while (cartaNova->persistenciaDePoder > 100 || cartaNova->persistenciaDePoder < 1); // Fim do bloco de validação da persistência de poder.

} // Fim da função recebeCarta.

/**
 * @brief Insere uma nova carta no deck.
 * 
 * Esta função procura a primeira posição vazia no array de ponteiros `deck` e insere uma 
 * nova carta nessa posição. Se não houver memória suficiente, a operação é abortada.
 * 
 * @param deck Array de ponteiros para estruturas de cartas (máximo 16 posições).
 * @param estande Ponteiro para a estrutura da carta que será inserida no deck.
 */
void inserirCarta(Estande* deck[], Estande* estande) {
    // Percorre o deck em busca da primeira posição nula (vazia).
    for (int i = 0; i < 16; i++) {
        if (deck[i] == NULL) { 
            // Aloca memória para a nova carta.
            deck[i] = (Estande*)malloc(sizeof(Estande));
            if (deck[i] == NULL) { // Verifica se a alocação foi bem-sucedida.
                printf("Erro ao alocar memória\n");
                return; // Fim da função em caso de erro de memória.
            }

            *deck[i] = *estande; // Copia os dados da carta para o deck.
            return; // Sai da função após a inserção bem-sucedida.
        }
    }
} // Fim da função inserirCarta.

/**
 * @brief Remove uma carta do deck.
 * 
 * Esta função localiza a carta especificada no deck e remove-a, liberando a posição para 
 * futuras inserções. A estrutura da carta removida é atualizada para valores padrão.
 * 
 * @param deck Array de ponteiros para estruturas de cartas.
 * @param estande Ponteiro para a estrutura da carta que será removida.
 */
void excluirCarta(Estande* deck[], Estande* estande) {
    // Percorre o deck em busca da carta especificada.
    for (int i = 0; i < 16; i++) {
        if (deck[i] == estande) { 
            char temp_letra = estande->letra;         // Armazena temporariamente o identificador da carta.
            int temp_numero = estande->numero;       // Armazena temporariamente o número da carta.
            int temp_trunfo = estande->super;        // Armazena temporariamente a flag de super carta.

            free(deck[i]);                           // Libera a memória alocada para a carta.
            deck[i] = NULL;                          // Marca a posição como disponível.

            estande->letra = temp_letra;             // Mantém os dados temporários para possível reuso.
            estande->numero = temp_numero;
            estande->super = temp_trunfo;

            return; // Encerra a função após a exclusão.
        }
    }
} // Fim da função excluirCarta.

/**
 * @brief Lista todas as cartas contidas nos estandes.
 * 
 * Esta função percorre um vetor de estandes contendo cartas 
 * e exibe cada uma delas através da função listarCarta().
 *
 * @param todosEstandes Vetor contendo todas as cartas nos estandes.
 */
void listarTodasCartas(Estande todosEstandes[]) {
    printf("-----TODAS AS CARTAS-----\n");
    for (int i = 0; i < 32; i++) {
        listarCarta(todosEstandes[i]);
    }
} // Fim da função listarTodasCartas

/**
 * @brief Altera as características de uma carta específica.
 * 
 * Esta função permite alterar atributos individuais de uma carta,
 * como nome, poder destrutivo, velocidade, alcance e persistência 
 * de poder, com base em uma opção fornecida.
 * 
 * @param estandes Ponteiro para a estrutura Estande que representa a carta.
 * @param opcao Inteiro que define qual atributo será alterado.
 * 
 * @note
 * - Opção 1: Nome da carta.
 * - Opção 2: Poder destrutivo (valor entre 1 e 100).
 * - Opção 3: Velocidade (valor entre 1 e 100).
 * - Opção 4: Alcance (valor entre 1 e 100).
 * - Opção 5: Persistência de poder (valor entre 1 e 100).
 */
void alterarCarta(Estande *estandes, int opcao) {
    switch (opcao) {
        case 1:
            printf("            Insira o novo nome da carta: ");
            lerString(estandes->nome, 30);
            break;

        case 2:
            do {
                printf("            Insira o novo poder destrutivo da carta: ");
                scanf("%d", &estandes->poderDestrutivo);
                if (estandes->poderDestrutivo < 1 || estandes->poderDestrutivo > 100) {
                    printf("            Valor inválido, insira novamente!\n");
                }
            } while (estandes->poderDestrutivo < 1 || estandes->poderDestrutivo > 100);
            break; // Fim do case 2

        case 3:
            do {
                printf("            Insira a nova velocidade dessa carta: ");
                scanf("%d", &estandes->velocidade);
                if (estandes->velocidade < 1 || estandes->velocidade > 100) {
                    printf("            Valor inválido, insira novamente!\n");
                }
            } while (estandes->velocidade < 1 || estandes->velocidade > 100);
            break; // Fim do case 3

        case 4:
            do {
                printf("            Insira o novo alcance dessa carta: ");
                scanf("%d", &estandes->alcance);
                if (estandes->alcance < 1 || estandes->alcance > 100) {
                    printf("            Valor inválido, insira novamente!\n");
                }
            } while (estandes->alcance < 1 || estandes->alcance > 100);
            break; // Fim do case 4

        case 5:
            do {
                printf("            Insira a nova persistência de poder dessa carta: ");
                scanf("%d", &estandes->persistenciaDePoder);
                if (estandes->persistenciaDePoder < 1 || estandes->persistenciaDePoder > 100) {
                    printf("            Valor inválido, insira novamente!\n");
                }
            } while (estandes->persistenciaDePoder < 1 || estandes->persistenciaDePoder > 100);
            break; // Fim do case 5

        default:
            break;
    } // Fim do switch
} // Fim da função alterarCarta

/**
 * @brief Armazena o deck final em um arquivo binário.
 * 
 * Esta função escreve o conteúdo do vetor de estandes em um 
 * arquivo binário, que representa o deck utilizado na última 
 * partida. O arquivo é salvo em "bin/deck_ultima_partida.dat".
 * 
 * @param estandes Vetor contendo o deck a ser armazenado.
 * 
 * @note O arquivo é sobrescrito toda vez que esta função é chamada.
 */
void armazenaDeckFinal(Estande estandes[]) {
    // Abre o arquivo para escrita em modo binário
    FILE *arq = fopen("bin/deck_ultima_partida.dat", "wb");

    // Grava os dados do vetor no arquivo
    fwrite(estandes, sizeof(Estande), 32, arq);

    // Fecha o arquivo após a gravação
    fclose(arq);

    return;
} // Fim da função armazenaDeckFinal

Estande recebeCartaParaMao(Estande deck[]) {
    for (int i = 0; i < 32; i++) {
        if (deck[i].nome[0] != '\0') { // Verifica se o slot não está vazio
            Estande carta = deck[i];
            deck[i].nome[0] = '\0'; // Limpa o slot no deck
            return carta;
        }
    }
    printf("Voce nao tem cartas no monte\n");
    return (Estande){{'\0'}}; // Retorna uma carta vazia se não houver cartas no deck
}

void receberCartaAdversario(Estande deck[], Estande mao){
    for(int i = 0; i < 32; i++){
        if(deck[i].nome[0] == '\0'){
            deck[i] = mao;
            memset(&mao, 0, sizeof(Estande));
            return;
        }
    }
    printf("Erro ao receber carta");
}
