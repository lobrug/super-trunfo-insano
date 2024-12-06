#include <stdio.h>
#include <stdlib.h>
#include "../structEstandes.h"
#include "../leituraCsv.h"
#include "../pesquisaDeCartas.h"
#include "../gerenciamentoDeDeck.h"

int main(){
    Estande estandes[32];

    
    leituraArquivoCsv(estandes);


    //pesquisarEstandeNome(estandes);
    //pesquisaCartaNumero(estandes);
    //pesquisaCartaLetra(estandes);
    //pesquisarEstandePoderDestrutivo(estandes);
    //pesquisarEstandeVelocidade(estandes);
    //pesquisarEstandeAlcance(estandes);
    //pesquisarEstandePersistencia(estandes);

    return 0;




}