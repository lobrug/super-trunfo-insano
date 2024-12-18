#ifndef gerenciamentoDeDeck_H
#define gerenciamentoDeDeck_H
#include "structEstandes.h"

void recebeCarta(Estande *cartaNova);

void inserirCarta(Estande* deck[], Estande* estande);

void excluirCarta(Estande* deck[], Estande* estande);

void listarTodasCartas(Estande todosEstandes[]);

void listarCartasDisponiveis(Estande estandes[]);

void alterarCarta(Estande *estandes, int opcao);

void armazenaDeckFinal(Estande estandes[]);

#endif