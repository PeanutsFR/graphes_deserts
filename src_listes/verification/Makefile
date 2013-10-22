#Répertoires et fichiers
OBJ_DIR = ./
SRC_DIR = ./
BIN_DIR = ../../bin/

#liste des sources a compiler
SRC=$(wildcard $(SRC_DIR)*.c) #recherche tout les fichier sources finissant par .c dans le dossier SRC_DIR
OBJ=$(SRC:.c=.o)              #nomme les fichier .o auront le meme nom que .c

PROGS=$(BIN_DIR)verification

#compilateur
CC = gcc

#options compilateur
CFLAGS = -Wall -Wextra -Werror -std=c99 $(OPTFLAGS)
OPTFLAGS = -g3 -O3


#Compilation

all: $(PROGS)

$(PROGS): $(OBJ)
	$(CC) -o $@ $^


%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)


clean:
	rm $(SRC_DIR)*.o

mrproper: clean
	rm $(BIN_DIR)$(EXEC)
