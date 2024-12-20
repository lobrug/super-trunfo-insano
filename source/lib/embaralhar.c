/**
 * @file embaralhar.c
 * @brief Implementação da função para embaralhar dois decks a partir de um conjunto de estandes.
 *
 * Esta função divide um array de estandes em dois decks, embaralha os elementos usando
 * o algoritmo de Fisher-Yates, e redistribui os elementos no array original.
 */

#include "embaralhar.h"
#include "structEstandes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pesquisaDeCartas.h"

/**
 * @brief Embaralha dois decks a partir de um array de estandes.
 *
 * A função utiliza o algoritmo de Fisher-Yates para gerar uma permutação aleatória
 * dos estandes e os distribui entre dois decks, mantendo uma referência organizada no
 * array original.
 *
 * @param deck Array que receberá os primeiros 16 estandes embaralhados.
 * @param deck2 Array que receberá os próximos 16 estandes embaralhados.
 * @param estandes Array contendo todos os 32 estandes a serem embaralhados.
 */
void embaralharDecks(Estande deck[], Estande deck2[], Estande* estandes) {

    int n = 32; // Quantidade total de estandes
    int indices[n]; // Array de índices para embaralhar

    /**
     * @brief Inicializa o array de índices sequencialmente.
     */
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    } // Fim do loop for (inicializa indices)

    srand(time(NULL)); // Semente para geração de números aleatórios

    /**
     * @brief Embaralha os índices usando o algoritmo de Fisher-Yates.
     */
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Gera índice aleatório entre 0 e i
        // Troca os elementos nos índices i e j
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    } // Fim do loop for (Fisher-Yates)

    /**
     * @brief Preenche o primeiro deck com os 16 primeiros estandes embaralhados.
     */
    for (int i = 0; i < 16; i++) {
        deck[i] = estandes[indices[i]];
    } // Fim do loop for (preenche deck)

    /**
     * @brief Preenche o segundo deck com os 16 últimos estandes embaralhados.
     */
    for (int i = 16; i < 32; i++) {
        deck2[i - 16] = estandes[indices[i]];
    } // Fim do loop for (preenche deck2)

    /**
     * @brief Reorganiza os estandes originais a partir dos decks.
     */
    for (int i = 0, j = 0; i < 32; i++) {
        if (i < 16) {
            estandes[i] = deck[i];
        } else {
            estandes[i] = deck2[j];
            j++;
        } // Fim do bloco if-else
    } // Fim do loop for (reorganiza estandes)

    return; // Fim da função
} // Fim da função embaralharDecks
