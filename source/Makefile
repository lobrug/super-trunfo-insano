#Esse make funciona só no windows

# Variáveis
CC = gcc
CFLAGS = -Wall -Ilib
SRC = main.c lib/embaralhar.c lib/gerenciamentoDeDeck.c lib/leituraCsv.c lib/menu.c lib/pesquisaDeCartas.c
OBJ = $(SRC:%.c=build/%.o)
BIN = bin/projeto.exe

# Regra padrão
all: setup $(BIN)

# Regra para criar o executável
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)
	@echo "Executável criado em $(BIN)"

# Regra para compilar arquivos .c em .o
build/%.o: %.c
	@mkdir build 2>nul || (exit 0)
	@mkdir build\lib 2>nul || (exit 0)
	$(CC) $(CFLAGS) -c $< -o $@

# Preparação de diretórios
setup:
	@mkdir build 2>nul || (exit 0)
	@mkdir build\lib 2>nul || (exit 0)
	@mkdir bin 2>nul || (exit 0)

# Limpeza dos arquivos objeto e do executável
clean:
	@rmdir /S /Q build 2>nul || (exit 0)
	@rmdir /S /Q bin 2>nul || (exit 0)
	@echo "Limpeza concluída!"

# Regra para rodar o programa
run: $(BIN)
	@echo "Executando o programa:"
	$(BIN)

.PHONY: all clean run setup
