#include "gerenciamentoDeDeck.h"
#include "structEstandes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pesquisaDeCartas.h"

/*permitir cadastrar (inserir/listar/pesquisar/alterar/excluir) as cartas disponíveis. Essa
relação deve aumentar e diminuir dinamicamente*/


/**
 * @brief Permite inserir cartas em um deck
 * 
 * @param deck 
 * @param estande 
 */
void inserirCarta(Estande* deck[], Estande* estande){
    //faz a verificação se a carta passado no parametro ja pertence ou não a um deck
    if(estande->verificacao == 1){
        printf("Não foi possivel adicionar esta carta pois ela ja pertence a um deck");
        return;
    }

    //usa um for para verificar a primeira posição nula e atribui a carta passada no parametro
    for (int i = 0; i < 16; i++) {
        if (deck[i] == NULL) {
            deck[i] = (Estande*)malloc(sizeof(Estande));
            if (deck[i] == NULL) {
                printf("Erro ao alocar memória\n");
                return;
            }

            estande->verificacao = 1;
            *deck[i] = *estande;
            
            return;
        }
    }
    printf("Deck cheio. Não foi possível inserir o estande.\n");
}


/**
 * @brief Permite excluir cartas de um deck
 * 
 * @param deck 
 * @param estande 
 */
void excluirCarta(Estande* deck[], Estande* estande){
    //verifica se a carta pertence a um deck
    if(estande->verificacao == 0){
        printf("Esta carta não pertence a nenhum deck\n");
        return;
    }

    for(int i = 0; i < 16; i++){
        if(deck[i] == estande){
            free(deck[i]);
            deck[i] = NULL;
            estande->verificacao = 0;
            return;
        }
    }
    printf("Estande não encontrado\n");
}


/**
 * @brief Lista todas as cartas
 * 
 * @param todosEstandes 
 */
void listarTodasCartas(Estande todosEstandes[]){
    printf("-----TODAS AS CARTAS-----\n");
    for(int i = 0; i < 32; i++){
        listarCarta(todosEstandes[i]);
    }
}


/**
 * @brief Lista as cartas disponiveis para atribuição
 * 
 * @param estandes 
 */
void listarCartasDisponiveis(Estande estandes[]){
    printf("-----CARTAS DISPONIVEIS-----");
    for(int i = 0; i < 32; i++){
        if(estandes[i].verificacao == 0){
            listarCarta(estandes[i]);
        }
    }
}

void alterarCarta(Estande *estandes, int opcao){

    switch (opcao)
    {
    case 1:
        printf("            Insira o novo nome da carta: ");
        lerString(estandes->nome, 30);
        break;
    
    case 2:
        do
        {
            printf("            Insira o novo poder destrutivo da carta: ");
            scanf("%d", &estandes->poderDestrutivo);
            if (estandes->poderDestrutivo < 1 || estandes->poderDestrutivo > 100)
            {
                printf("            Valor inválido, insira novamente!\n");
            }

        } while (estandes->poderDestrutivo < 1 || estandes->poderDestrutivo > 100);
        
        break;
    
    case 3:
        do
        {
            printf("            Insira a nova velocidade dessa carta: ");
            scanf("%d", &estandes->velocidade);
            if (estandes->velocidade < 1 || estandes->velocidade > 100)
            {
                printf("            Valor inválido, insira novamente!\n");
            }
    
        } while (estandes->velocidade < 1 || estandes->velocidade > 100);
        
        break;
    
    case 4:
        do
        {
            printf("            Insira o novo alcance dessa carta: ");
            scanf("%d", & estandes->alcance);
            if (estandes->alcance < 1 || estandes->alcance > 100)
            {
                printf("            Valor inválido, insira novamente!\n");
            }
            
        } while (estandes->alcance < 1 || estandes->alcance > 100);
        
        break;
    
    case 5:
        do
        {
            printf("            Insira a nova persistência de poder dessa carta: ");
            scanf("%d", &estandes->persistenciaDePoder);
            if (estandes->persistenciaDePoder < 1 || estandes->persistenciaDePoder > 100)
            {
                printf("            Valor inválido, insira novamente!\n");
            }
            
        } while (estandes->persistenciaDePoder < 1 || estandes->persistenciaDePoder > 100);
        
        break;
    
    default:
        break;
    }

}

void armazenaDeckFinal(Estande estandes[]){

    FILE *arq = fopen("../bin/deck_ultima_partida.dat", "wb");

    fwrite(estandes, sizeof(Estande), 32, arq);

    fclose(arq);

    return;
}