#include "pesquisaDeCartas.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "structEstandes.h"

/**
 * @brief Lê uma string do usuário com tamanho máximo especificado.
 * 
 * Esta função utiliza `fgets` para obter uma string da entrada padrão,
 * substituindo o caractere de nova linha ('\n') por um terminador nulo ('\0').
 * 
 * @param texto Ponteiro para a string onde o texto será armazenado.
 * @param tamanho Tamanho máximo da string, incluindo o terminador nulo.
 */
void lerString(char* texto, int tamanho) {
    setbuf(stdin, NULL); // Limpa o buffer do teclado para evitar entradas indesejadas.
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0'; // Remove o caractere de nova linha.
} // Fim da função lerString

/**
 * @brief Exibe os detalhes de uma carta.
 * 
 * Esta função imprime na tela os atributos de uma carta contida em um estande.
 * É utilizada como suporte para outras funções de pesquisa.
 * 
 * @param estande Estrutura contendo os dados da carta a ser exibida.
 */
void listarCarta(Estande estande) {
    printf("            -----CARTA-----\n");
    printf("            Nome: %s\n", estande.nome);
    printf("            id: %c%d\n", estande.letra, estande.numero);
    if (estande.super == true) {
        printf("            Esta carta é o super trunfo\n");
    }
    printf("            -----ATRIBUTOS-----\n");
    printf("            Poder destrutivo: %d\n", estande.poderDestrutivo);
    printf("            Velocidade: %d\n", estande.velocidade);
    printf("            Alcance: %d\n", estande.alcance);
    printf("            Persistencia: %d\n\n", estande.persistenciaDePoder);
} // Fim da função listarCarta

/**
 * @brief Pesquisa um estande pelo nome.
 * 
 * Esta função solicita ao usuário o nome de um estande e busca no array de estandes.
 * Se encontrado, exibe os detalhes da carta; caso contrário, informa que não foi encontrado.
 * 
 * @param estandes Array contendo todas as cartas disponíveis.
 */
void pesquisarEstandeNome(Estande estandes[]) {
    char pesquisa[30];

    printf("            Qual o nome do estande que deseja pesquisar?: ");
    lerString(pesquisa, 30); // Lê o nome do estande fornecido pelo usuário.

    for (int i = 0; i < 32; i++) {
        // Verifica se o nome fornecido corresponde ao nome de algum estande.
        if (strcasecmp(pesquisa, estandes[i].nome) == 0) {
            listarCarta(estandes[i]); // Exibe os detalhes da carta encontrada.
            printf("\n");
            return;
        }
    }
    printf("            Estande não encontrado\n");
    return;
} // Fim da função pesquisarEstandeNome

/**
 * @brief Filtra os estandes pelo poder destrutivo.
 * 
 * Solicita ao usuário um intervalo de valores mínimo e máximo de poder destrutivo,
 * e lista todas as cartas que atendem ao critério. Caso nenhuma carta seja encontrada,
 * informa que não foram encontrados resultados.
 * 
 * @param estandes Array contendo todas as cartas disponíveis.
 */
void pesquisarEstandePoderDestrutivo(Estande estandes[]) {
    int auxiliar = 0; // Indica se alguma carta foi encontrada no filtro.
    int maximo;
    int minimo;

    // Solicita o valor máximo de poder destrutivo, validando a entrada.
    do {
        printf("            Qual o poder maximo que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if (maximo < 0 || maximo > 100) {
            printf("            Valor invalido\n");
        }
    } while (maximo < 0 || maximo > 100);

    // Solicita o valor mínimo de poder destrutivo, validando a entrada.
    do {
        printf("            E o minimo?: ");
        scanf("%d", &minimo);

        if (minimo < 0 || minimo > maximo) {
            printf("            Valor invalido\n");
        }
    } while (minimo < 0 || minimo > maximo);

    // Itera sobre todas as cartas para verificar se atendem ao critério de filtro.
    for (int i = 0; i < 32; i++) {
        if (estandes[i].poderDestrutivo <= maximo && estandes[i].poderDestrutivo >= minimo) {
            listarCarta(estandes[i]); // Exibe os detalhes da carta encontrada.
            auxiliar = 1; // Indica que pelo menos uma carta foi encontrada.
        }
    }

    // Informa se nenhuma carta foi encontrada dentro do critério especificado.
    if (auxiliar == 0) {
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }
    return;
} // Fim da função pesquisarEstandePoderDestrutivo

/**
 * @brief Filtra os estandes pela velocidade.
 * 
 * Solicita ao usuário um intervalo de valores mínimo e máximo de velocidade
 * e lista todas as cartas que atendem ao critério. Caso nenhuma carta seja
 * encontrada, informa que não foram encontrados resultados.
 * 
 * @param estandes Array contendo todas as cartas disponíveis.
 */
void pesquisarEstandeVelocidade(Estande estandes[]) {
    int auxiliar = 0; // Indica se alguma carta foi encontrada no filtro.
    int maximo;
    int minimo;

    // Solicita o valor máximo de velocidade, validando a entrada.
    do {
        printf("            Qual a velocidade maxima que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if (maximo < 0 || maximo > 100) {
            printf("            Valor invalido\n");
        }
    } while (maximo < 0 || maximo > 100);

    // Solicita o valor mínimo de velocidade, validando a entrada.
    do {
        printf("            E a minima?: ");
        scanf("%d", &minimo);

        if (minimo < 0 || minimo > maximo) {
            printf("            Valor invalido\n");
        }
    } while (minimo < 0 || minimo > maximo);

    // Itera sobre as cartas verificando se atendem ao critério de filtro.
    for (int i = 0; i < 32; i++) {
        if (estandes[i].velocidade <= maximo && estandes[i].velocidade >= minimo) {
            listarCarta(estandes[i]); // Exibe os detalhes da carta encontrada.
            auxiliar = 1; // Indica que pelo menos uma carta foi encontrada.
        }
    }

    // Informa se nenhuma carta foi encontrada.
    if (auxiliar == 0) {
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n");
    }
    return;
} // Fim da função pesquisarEstandeVelocidade

/**
 * @brief Filtra os estandes pelo alcance.
 * 
 * Solicita ao usuário um intervalo de valores mínimo e máximo de alcance
 * e lista todas as cartas que atendem ao critério. Caso nenhuma carta seja
 * encontrada, informa que não foram encontrados resultados.
 * 
 * @param estandes Array contendo todas as cartas disponíveis.
 */
void pesquisarEstandeAlcance(Estande estandes[]) {
    int auxiliar = 0; // Indica se alguma carta foi encontrada no filtro.
    int maximo;
    int minimo;

    // Solicita o valor máximo de alcance, validando a entrada.
    do {
        printf("            Qual o alcance maximo que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if (maximo < 0 || maximo > 100) {
            printf("            Valor invalido\n");
        }
    } while (maximo < 0 || maximo > 100);

    // Solicita o valor mínimo de alcance, validando a entrada.
    do {
        printf("            E o minimo?: ");
        scanf("%d", &minimo);

        if (minimo < 0 || minimo > maximo) {
            printf("            Valor invalido\n");
        }
    } while (minimo < 0 || minimo > maximo);

    // Itera sobre as cartas verificando se atendem ao critério de filtro.
    for (int i = 0; i < 32; i++) {
        if (estandes[i].alcance <= maximo && estandes[i].alcance >= minimo) {
            listarCarta(estandes[i]); // Exibe os detalhes da carta encontrada.
            auxiliar = 1; // Indica que pelo menos uma carta foi encontrada.
        }
    }

    // Informa se nenhuma carta foi encontrada.
    if (auxiliar == 0) {
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n\n");
    }
    return;
} // Fim da função pesquisarEstandeAlcance

/**
 * @brief Filtra os estandes pela persistência de poder.
 * 
 * Solicita ao usuário um intervalo de valores mínimo e máximo de persistência
 * de poder e lista todas as cartas que atendem ao critério. Caso nenhuma carta
 * seja encontrada, informa que não foram encontrados resultados.
 * 
 * @param estandes Array contendo todas as cartas disponíveis.
 */
void pesquisarEstandePersistencia(Estande estandes[]) {
    int auxiliar = 0; // Indica se alguma carta foi encontrada no filtro.
    int maximo;
    int minimo;

    // Solicita o valor máximo de persistência de poder, validando a entrada.
    do {
        printf("            Qual a persistencia de poder maxima que você deseja pesquisar?: ");
        scanf("%d", &maximo);

        if (maximo < 0 || maximo > 100) {
            printf("            Valor invalido\n");
        }
    } while (maximo < 0 || maximo > 100);

    // Solicita o valor mínimo de persistência de poder, validando a entrada.
    do {
        printf("            E a minima?: ");
        scanf("%d", &minimo);

        if (minimo < 0 || minimo > maximo) {
            printf("            Valor invalido\n");
        }
    } while (minimo < 0 || minimo > maximo);

    // Itera sobre as cartas verificando se atendem ao critério de filtro.
    for (int i = 0; i < 32; i++) {
        if (estandes[i].persistenciaDePoder <= maximo && estandes[i].persistenciaDePoder >= minimo) {
            listarCarta(estandes[i]); // Exibe os detalhes da carta encontrada.
            auxiliar = 1; // Indica que pelo menos uma carta foi encontrada.
        }
    }

    // Informa se nenhuma carta foi encontrada.
    if (auxiliar == 0) {
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n\n");
    }
    return;
} // Fim da função pesquisarEstandePersistencia

/**
 * @brief Pesquisa cartas com base na letra fornecida pelo usuário.
 * 
 * O usuário fornece uma letra, e todas as cartas cujo atributo `letra`
 * corresponde ao valor fornecido são listadas. Caso nenhuma carta seja
 * encontrada, informa que não foram encontrados resultados.
 * 
 * @param estandes Array contendo todas as cartas disponíveis.
 */
void pesquisaCartaLetra(Estande estandes[]) {
    int auxiliar = 0; // Indica se alguma carta foi encontrada no filtro.
    char pesquisa;

    // Solicita ao usuário a letra para pesquisa.
    printf("            Que letra deseja pesquisar?: ");
    setbuf(stdin, NULL); // Limpa o buffer de entrada para evitar erros no scanf.
    scanf("%c", &pesquisa);
    pesquisa = toupper(pesquisa); // Converte a letra para maiúscula para comparação.

    // Itera sobre as cartas verificando se atendem ao critério de filtro.
    for (int i = 0; i < 32; i++) {
        if (estandes[i].letra == pesquisa) {
            listarCarta(estandes[i]); // Exibe os detalhes da carta encontrada.
            auxiliar = 1; // Indica que pelo menos uma carta foi encontrada.
        }
    }

    // Informa se nenhuma carta foi encontrada.
    if (auxiliar == 0) {
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n\n");
    }

    return;
} // Fim da função pesquisaCartaLetra

/**
 * @brief Pesquisa cartas com base no número fornecido pelo usuário.
 * 
 * O usuário fornece um número, e todas as cartas cujo atributo `numero`
 * corresponde ao valor fornecido são listadas. Caso nenhuma carta seja
 * encontrada, informa que não foram encontrados resultados.
 * 
 * @param estandes Array contendo todas as cartas disponíveis.
 */
void pesquisaCartaNumero(Estande estandes[]) {
    int auxiliar = 0; // Indica se alguma carta foi encontrada no filtro.
    int pesquisa;

    // Solicita ao usuário o número para pesquisa.
    printf("            Que numero deseja pesquisar?: ");
    scanf("%d", &pesquisa);

    // Itera sobre as cartas verificando se atendem ao critério de filtro.
    for (int i = 0; i < 32; i++) {
        if (estandes[i].numero == pesquisa) {
            listarCarta(estandes[i]); // Exibe os detalhes da carta encontrada.
            auxiliar = 1; // Indica que pelo menos uma carta foi encontrada.
        }
    }

    // Informa se nenhuma carta foi encontrada.
    if (auxiliar == 0) {
        printf("            Não foi encontrado nenhuma carta com o filtro expecificado\n\n");
    }

    return;
} // Fim da função pesquisaCartaNumero

/**
 * @brief Pesquisa um estande pelo nome fornecido e retorna sua posição no array.
 * 
 * O usuário fornece o nome de um estande, e a função busca por esse nome no array.
 * Caso encontrado, exibe os detalhes do estande e retorna sua posição no array.
 * Caso contrário, informa que o estande não foi encontrado e retorna -1.
 * 
 * @param estandes Array contendo todas as cartas disponíveis.
 * @return int Posição do estande no array, ou -1 se não encontrado.
 */
int pesquisarEstandeNomeRetornoPosicao(Estande estandes[]) {
    char pesquisa[30];

    // Solicita ao usuário o nome do estande para pesquisa.
    printf("\n            Qual o nome do estande que deseja pesquisar?: ");
    lerString(pesquisa, 30);

    // Itera sobre o array procurando pelo nome fornecido.
    for (int i = 0; i < 32; i++) {
        // Compara o nome digitado com o nome do estande ignorando diferenças de maiúsculas/minúsculas.
        if (strcasecmp(pesquisa, estandes[i].nome) == 0) {
            listarCarta(estandes[i]); // Exibe os detalhes do estande encontrado.
            return i; // Retorna a posição do estande no array.
        }
    }

    // Informa se o estande não foi encontrado.
    printf("            Estande não encontrado\n\n");
    return -1;
} // Fim da função pesquisarEstandeNomeRetornoPosicao
