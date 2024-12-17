#include "embaralhar.h"
#include "structEstandes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pesquisaDeCartas.h"

void embaralharDecks(Estande deck[], Estande deck2[], Estande* estandes) {

    int n = 32;
    int indices[n];

    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }

    srand(time(NULL));

    // Embaralha os índices usando o algoritmo de Fisher-Yates
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Índice aleatório entre 0 e i
        // Troca os índices
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Preenche o deck com os estandes embaralhados
    for (int i = 0; i < 16; i++) {
        deck[i] = estandes[indices[i]];
    }
    for (int i = 16; i < 32; i++)
    {
        deck2[i - 16] = estandes[indices[i]];
    }

    for (int i = 0, j = 0; i < 32; i++)
    {
        if (i < 16)
        {
            estandes[i] = deck[i];
        }else
        {
            estandes[i] = deck2[j];
            j++;
        }
        
    }

    return;
}