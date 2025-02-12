#include "manipulacaoCartas.h"
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "structEstandes.h"

    void loadImageToCard(Estande *estande, const char *fileName, int width, int height){

        Image imageTemp = LoadImage(fileName);
        
        if(imageTemp.data == NULL){
            printf("Erro ao abrir arquivo");

            imageTemp = LoadImage(".\\assets\\img\\erro.png");
            ImageResize(&imageTemp, 205, 146);
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

    Texture2D carregaCarta(char letra){

        const char *fileName;

        switch (letra)
        {
        case 'a':
        case 'A':
            fileName = ".\\assets\\img\\Roxo.png";
            break;
        
        case 'b':
        case 'B':
            fileName = ".\\assets\\img\\Verde.png";
            break;
        
        case 'c':
        case 'C':
            fileName = ".\\assets\\img\\Amarela.png";
            break;
        
        case 'd':
        case 'D':
            fileName = ".\\assets\\img\\Azul.png";
            break;

        case 'G':
            fileName = ".\\assets\\img\\Supertrunfo.png";
            break;
        
        default:
            break;
        }


        Image imageTemp = LoadImage(fileName);
        ImageResize(&imageTemp, 250, 375);
        Texture2D texture = LoadTextureFromImage(imageTemp);
        UnloadImage(imageTemp);
        return texture;

    }