#ifndef gerenciamentoDeDeck_H
#define gerenciamentoDeDeck_H

#include "gerenciamentoDeDeck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "structEstandes.h"
#include "pesquisaDeCartas.h"

/*permitir cadastrar (inserir/listar/pesquisar/alterar/excluir) as cartas disponíveis. Essa
relação deve aumentar e diminuir dinamicamente*/

void recebeCarta(Estande *cartaNova){

    printf("                Insira o nome do seu novo Stand: ");
    lerString(cartaNova->nome, 30);

    do{
        printf("                Insira o poder destrutivo do novo Stand: ");
        scanf("%d", &cartaNova->poderDestrutivo);
        if (cartaNova->poderDestrutivo > 100 || cartaNova->poderDestrutivo < 1)
        {
            printf("                Valor inválido, insira novamente!\n");
        }
        
    }while(cartaNova->poderDestrutivo > 100 || cartaNova->poderDestrutivo < 1);
    
    do{
        printf("                Insira a velocidade do novo Stand: ");
        scanf("%d", &cartaNova->velocidade);
        if (cartaNova->velocidade > 100 || cartaNova->velocidade < 1)
        {
            printf("                Valor inválido, insira novamente!\n");
        }
        
    }while(cartaNova->velocidade > 100 || cartaNova->velocidade < 1);

    do{
        printf("                Insira o alcance do novo Stand: ");
        scanf("%d", &cartaNova->alcance);
        if (cartaNova->alcance > 100 || cartaNova->alcance < 1)
        {
            printf("                Valor inválido, insira novamente!\n");
        }
        
    }while(cartaNova->alcance > 100 || cartaNova->alcance < 1);

    do{
        printf("                Insira a persistencia de poder do novo Stand: ");
        scanf("%d", &cartaNova->persistenciaDePoder);
        if (cartaNova->persistenciaDePoder > 100 || cartaNova->persistenciaDePoder < 1)
        {
            printf("                Valor inválido, insira novamente!\n");
        }
        
    }while(cartaNova->persistenciaDePoder > 100 || cartaNova->persistenciaDePoder < 1);
}


/**
 * @brief Permite inserir cartas em um deck
 * 
 * @param deck 
 * @param estande 
 */
void inserirCarta(Estande* deck[], Estande* estande){

    //usa um for para verificar a primeira posição nula e atribui a carta passada no parametro
    for (int i = 0; i < 16; i++) {
        if (deck[i] == NULL) {
            deck[i] = (Estande*)malloc(sizeof(Estande));
            if (deck[i] == NULL) {
                printf("Erro ao alocar memória\n");
                return;
            }

            *deck[i] = *estande;
            
            return;
        }
    }
}


/**
 * @brief Permite excluir cartas de um deck
 * 
 * @param deck 
 * @param estande 
 */
void excluirCarta(Estande* deck[], Estande* estande){

    for(int i = 0; i < 16; i++){
        if(deck[i] == estande){
            char temp_letra = estande->letra;
            int temp_numero = estande->numero;
            int temp_trunfo = estande->super;
            deck[i] = NULL;
            deck[i]->letra = temp_letra;
            deck[i]->numero = temp_numero;
            deck[i]->super = temp_trunfo;
            return;
        }
    }

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

    FILE *arq = fopen("deck_ultima_partida.dat", "wb");

    fwrite(estandes, sizeof(Estande), 32, arq);

    fclose(arq);

    return;
}

Estande recebeCartaParaMao(Estande deck[]) {
    for (int i = 0; i < 32; i++) {
        if (deck[i].nome[0] != '\0') { // Verifica se o slot não está vazio
            Estande carta = deck[i];
            deck[i].nome[0] = '\0'; // Limpa o slot no deck
            return carta;
        }
    }
    printf("Voce nao tem cartas no monte\n");
}

void receberCartaAdversario(Estande deck[], Estande mao){
    for(int i = 0; i < 32; i++){
        if(deck[i].nome[0] == '\0'){
            deck[i] = mao;
            mao = (Estande){{'\0'}};
            return;
        }
    }
    printf("Erro ao receber carta");
}

int VerificadorFiltro(char Letra, int poder[], int velocidade[], int alcance[], int percistencia[], int numero, Estande estandes){

    if ((Letra != NULL) && Letra != estandes.letra)
    {
        return -1;
    }

    if ((poder != NULL) && ((poder[0] < estandes.poderDestrutivo) || (poder[1] > estandes.poderDestrutivo)))
    {
        return -1;
    }

    if ((velocidade != NULL) && ((velocidade[0] < estandes.velocidade) || (velocidade[1] > estandes.velocidade)))
    {
        return -1;
    }
    
    if ((alcance != NULL) && ((alcance[0] < estandes.alcance) || (alcance[1] > estandes.alcance)))
    {
        return -1;
    }

    if ((percistencia != NULL) && ((percistencia[0] < estandes.persistenciaDePoder) || (percistencia[1] > estandes.persistenciaDePoder)))
    {
        return -1;
    }
    
    if ((numero != NULL) && (numero != estandes.numero))
    {
        return -1;
    }
    
    return 0;
    
}

#endif