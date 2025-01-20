#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "leituraCsv.h"
#include "structEstandes.h"

/**
 * @brief Lê os dados de cartas de um arquivo CSV e armazena no vetor de estandes.
 * 
 * Esta função lê as informações das cartas contidas em um arquivo CSV,
 * realiza o parsing (extração dos dados) e preenche o vetor de estandes 
 * com os valores lidos.
 * 
 * @param estandes Vetor do tipo Estande onde os dados lidos serão armazenados.
 * 
 * @note
 * - O arquivo de entrada deve estar localizado em "lib/cartas_stands.csv".
 * - O arquivo deve seguir o formato: letra,numero,nome,super,poderDestrutivo,velocidade,alcance,persistenciaDePoder
 * - A leitura considera até 32 cartas, limite máximo do vetor.
 */
void leituraArquivoCsv(Estande estandes[]) {
    // Abre o arquivo CSV para leitura
    FILE *infocartas = fopen("lib/cartas_stands.csv", "r");

    // Verifica se o arquivo foi aberto corretamente
    if (infocartas == NULL) {
        printf("Falha ao abrir arquivo\n");
        return;
    }

    char linha[100]; /**< Buffer para leitura de linhas do cabeçalho. */
    fgets(linha, sizeof(linha), infocartas); // Lê e descarta o cabeçalho do arquivo

    int i = 0; /**< Índice para armazenar os dados no vetor de estandes. */

    // Loop para ler os dados do arquivo até o final ou atingir o limite de 32 entradas
    while (fscanf(infocartas, 
            "%c,%d,%49[^,],%d,%d,%d,%d,%d\n",
            &estandes[i].letra, 
            &estandes[i].numero, 
            estandes[i].nome, 
            &estandes[i].super, 
            &estandes[i].poderDestrutivo, 
            &estandes[i].velocidade, 
            &estandes[i].alcance, 
            &estandes[i].persistenciaDePoder) == 8) { // Garante que todos os campos foram lidos corretamente
        
        i++; // Avança para o próximo índice do vetor

        // Verifica se o limite de 32 cartas foi atingido
        if (i >= 32) break;
    } // Fim do while

    // Fecha o arquivo após a leitura
    fclose(infocartas);

    return;
} // Fim da função leituraArquivoCsv
