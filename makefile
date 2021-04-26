CC = gcc

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -lm -g

SRC1 = Chaine.c Reseau.c ArbreQuat.c Hachage.c SVGwriter.c
SRC2 = Graphe.c Struct_File.c Struct_Liste.c Chaine.c Reseau.c SVGwriter.c

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

all : graphique main ReconstitueReseau ReorganiseReseau

graphique : graphique.c $(SRC1)
	$(CC) $(CFLAGS) -o graphique graphique.c $(SRC1)

main :  main.c $(SRC1)
	$(CC) $(CFLAGS) -o main main.c $(SRC1)

ReconstitueReseau : ReconstitueReseau.c $(SRC1)
	$(CC) $(CFLAGS) -o ReconstitueReseau ReconstitueReseau.c $(SRC1)

ReorganiseReseau : ReorganiseReseau.c 
	$(CC) $(CFLAGS) -o ReorganiseReseau ReorganiseReseau.c $(SRC2)

clean : 
	rm -f graphique main ReconstitueReseau ReorganiseReseau

