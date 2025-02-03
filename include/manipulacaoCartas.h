#ifndef MANIPULACAOCARTAS_H
#define MANIPULACAOCARTAS_H

#include <stdio.h>
#include "raylib.h"
#include "structEstandes.h"

    void loadImageToCard(Estande *estande, const char *fileName, int width, int height){

        Image imageTemp = LoadImage(fileName);
        
        if(imageTemp.data == NULL){
            printf("Erro ao abrir arquivo");

            imageTemp = LoadImage(".\\assets\\img\\erro.png");
            ImageResize(&imageTemp, 174, 142);
            Texture2D texture = LoadTextureFromImage(imageTemp);
            estande->foto = texture;
            UnloadImage(imageTemp);
            return;

        }else{

            ImageResize(&imageTemp, width, height);
            Texture2D texture = LoadTextureFromImage(imageTemp);
            estande->foto = texture;
            UnloadImage(imageTemp);

        }

        return;
        
    }


#endif