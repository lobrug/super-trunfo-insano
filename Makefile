# Verifica o sistema operacional
ifdef OS
	OS := $(strip $(OS))
else
	OS := $(strip $(shell uname))
endif

BINNAME = JoJoTrunfo

ifeq ($(OS),Windows_NT)
		INCLUDE = -I./include/ -L./libwin
		EXTRA_FLAGS = -Wall -Wextra -std=c99 -Wno-missing-braces -lraylib -lm -lopengl32 -lgdi32 -lwinmm
		BIN = .\$(BINNAME).exe
		RM = del /Q /F
else
		INCLUDE = -I./include/ -L./lib
		EXTRA_FLAGS = -Wall -Wextra -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
		BIN = ./$(BINNAME)
		RM = rm -f
endif

SRC = $(wildcard ./*.c) $(wildcard ./include/*.c)

all:
	gcc $(SRC) -g $(INCLUDE) $(EXTRA_FLAGS) -o $(BIN)

run:
	$(BIN)

clean:
	$(RM) $(BIN)

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes $(BIN)
