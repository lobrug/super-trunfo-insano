#ifndef MANIPULACAOCARTAS_H
#define MANIPULACAOCARTAS_H

#include <stdio.h>
#include "raylib.h"
#include "structEstandes.h"

    void loadImageToCard(Estande *estande, const char *fileName){
        Image imageTemp = LoadImage(fileName);
        if(fileName == NULL){
            printf("Erro ao abrir arquivo");
            return;
        }
        ImageResize(&imageTemp, 174, 142);
        Texture2D texture = LoadTextureFromImage(imageTemp);
        estande->foto = texture;
        UnloadImage(imageTemp);
    }

    

#endif