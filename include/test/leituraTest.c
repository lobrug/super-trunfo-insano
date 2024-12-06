#include <stdio.h>
#include <stdlib.h>
#include "../structEstandes.h"
#include "../leituraCsv.h"
#include "../pesquisaDeCartas.h"
#include "../gerenciamentoDeDeck.h"



int main(){

Estande estandes[32];

leituraArquivoCsv(estandes);

listarTodasCartas(estandes);

return 0;
}
