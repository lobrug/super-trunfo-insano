# Comentário do makefile de exemplo

# Regra para compilar o programa principal
main: main.o embaralhar.o gerenciamentoDeDeck.o leituraCsv.o menu.o pesquisaDeCartas.o
 	gcc main.o -o main

# Regra para compilar os arquivos objeto
main.o: main.c
	gcc -c main.c

embaralhar.o: embaralhar.c
	gcc -c ./lib/embaralhar.c

gerenciamentoDeDeck.o: gerenciamentoDeDeck.c
	gcc -c ./lib/gerenciamentoDeDeck.c

leituraCsv.o: leituraCsv.c
	gcc -c ./lib/leituraCsv.c

menu.o: menu.c
	gcc -c ./lib/menu.c

pesquisaDeCartas.o: pesquisaDeCartas.c
	gcc -c ./lib/pesquisaDeCartas.c

# Limpeza dos arquivos objeto e binário gerados
clean:
	rm -f main.o main

# Regra para rodar o programa
run:
	./main
