all : graphique main ReconstitueReseau

graphique : graphique.c Chaine.c Reseau.c ArbreQuat.c Hachage.c SVGwriter.c
	gcc -o graphique graphique.c Chaine.c Reseau.c ArbreQuat.c Hachage.c SVGwriter.c -lm

main : main.c Chaine.c Reseau.c ArbreQuat.c Hachage.c SVGwriter.c
	gcc -o main main.c Chaine.c Reseau.c ArbreQuat.c Hachage.c SVGwriter.c -lm

ReconstitueReseau : ReconstitueReseau.c Chaine.c Reseau.c ArbreQuat.c Hachage.c SVGwriter.c
	gcc -o ReconstitueReseau ReconstitueReseau.c Chaine.c Reseau.c ArbreQuat.c Hachage.c SVGwriter.c -lm

clean : 
	rm -f graphique main ReconstitueReseau

