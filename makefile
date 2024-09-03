PATH_PRJ = c:/source/hash
PATH_SHARE = $(PATH_PRJ)/share
PATH_SRC = $(PATH_PRJ)/src
PATH_BIN = $(PATH_PRJ)/bin

run:
	$(PATH_BIN)/main.exe

build: $(PATH_SHARE)/hash.h $(PATH_SRC)/main.c
	gcc -o $(PATH_BIN)/main.exe -I $(PATH_SHARE) $(PATH_SRC)/main.c
