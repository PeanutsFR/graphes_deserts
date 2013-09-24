#Répertoires et fichiers
OBJ_DIR = .
SRC_DIR = src
INC_DIR = src
BIN_DIR = bin

OBJS = $(OBJ_DIR)/ast.o $(OBJ_DIR)/patchwork.o

PROGS = test_affiches_specifiques test_evaluer testparse

#Flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 $(OPTFLAGS)
OPTFLAGS = -g

#Première règle
.PHONY: all
all: $(PROGS)
	

#Génération des programmes
%: $(SRC_DIR)/%.c $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) libparser.a -o $(BIN_DIR)/$@ -lm
testparse: $(SRC_DIR)/testparse.c $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) libparser.a -o $(BIN_DIR)/$@ -lm

#Génération des modules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

#Règles PHONY diverses
.PHONY: clean
clean:
	rm -rf $(OBJS) *~ $(OBJ_DIR)/*~ $(SRC_DIR)/*~ $(INC_DIR)/*~
