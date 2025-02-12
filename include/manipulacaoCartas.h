#ifndef MANIPULACAOCARTAS_H
#define MANIPULACAOCARTAS_H

#include <stdio.h>
#include "raylib.h"
#include "structEstandes.h"

    void loadImageToCard(Estande *estande, const char *fileName, int width, int height);

    Texture2D carregaCarta(char letra);

#endif