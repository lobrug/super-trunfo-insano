/**
 * @file manipulacaoCartas.c
 * @brief Implementação das funções para carregar e manipular imagens de cartas.
 */

 #include "manipulacaoCartas.h"
 #include <stdlib.h>
 #include <stdio.h>
 #include "raylib.h"
 #include "structEstandes.h"
 
 /**
  * @brief Carrega uma imagem e a atribui a uma carta.
  *
  * Esta função carrega uma imagem do arquivo especificado, redimensiona e atribui ao estande.
  * Caso a imagem não seja encontrada, carrega uma imagem de erro.
  *
  * @param estande Ponteiro para a estrutura Estande onde a imagem será armazenada.
  * @param fileName Caminho do arquivo de imagem.
  * @param width Largura desejada da imagem.
  * @param height Altura desejada da imagem.
  */
 void loadImageToCard(Estande *estande, const char *fileName, int width, int height) {
     Image imageTemp = LoadImage(fileName);
     
     if (imageTemp.data == NULL) {
         printf("Erro ao abrir arquivo\n");
         
         // Carrega imagem de erro caso o arquivo não seja encontrado
         imageTemp = LoadImage(".\\assets\\img\\erro.png");
         ImageResize(&imageTemp, 205, 146);
         Texture2D texture = LoadTextureFromImage(imageTemp);
         estande->foto = texture;
         UnloadImage(imageTemp);
         return; // Fim da função
     }
     
     // Caso a imagem seja carregada corretamente
     ImageResize(&imageTemp, width, height);
     Texture2D texture = LoadTextureFromImage(imageTemp);
     estande->foto = texture;
     UnloadImage(imageTemp);
     
     return; // Fim da função
 }
 
 /**
  * @brief Carrega uma textura correspondente a uma letra especificada.
  *
  * Esta função associa uma letra a um arquivo de imagem e retorna a textura correspondente.
  *
  * @param letra Letra representando o tipo da carta.
  * @return Texture2D Textura carregada correspondente à letra.
  */
 Texture2D carregaCarta(char letra) {
     const char *fileName;
 
     // Seleciona o arquivo correspondente à letra fornecida
     switch (letra) {
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
             return (Texture2D){0}; // Retorna uma textura vazia caso a letra não seja reconhecida
     }
 
     // Carrega e redimensiona a imagem
     Image imageTemp = LoadImage(fileName);
     ImageResize(&imageTemp, 250, 375);
     Texture2D texture = LoadTextureFromImage(imageTemp);
     UnloadImage(imageTemp);
     
     return texture; // Retorna a textura carregada
 }