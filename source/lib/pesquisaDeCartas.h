#ifndef pesquisaDeCartas_H
#define pesquisaDeCartas_H

void lerString(char* texto, int tamanho);

void listarCarta(Estande estande);

void pesquisarEstandeNome(Estande estandes[]);

void pesquisarEstandePoderDestrutivo(Estande estandes[]);

void pesquisarEstandeVelocidade(Estande estandes[]);

void pesquisarEstandeAlcance(Estande estandes[]);

void pesquisarEstandePersistencia(Estande estandes[]);

void pesquisaCartaLetra(Estande estandes[]);

void pesquisaCartaNumero(Estande estandes[]);

int pesquisarEstandeNomeRetornoPosicao(Estande estandes[]);

#endif