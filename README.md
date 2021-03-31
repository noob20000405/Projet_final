# Projet : Réorganisation d’un réseau de fibres optiques
## CADRE DU PROJET

Un **réseau** est un ensemble de câbles, chacun contenant un ensemble de fibres optiques et reliant des clients. 

- 1ère partie : reconstituer le plan du réseau de l’agglomération. Chaque opérateur connaît les tronçons de fibres optiques qu’il utilise dans le réseau. Il y a au moins une fibre utilisée par câble. 
- 2ème partie : réorganiser les attributions de fibres de chacun des opérateurs. 

Un **câble** est un fourreau contenant exactement ![image](https://user-images.githubusercontent.com/55035665/113163019-10105480-9240-11eb-8f65-84f9df09a084.png)
 fibres optiques.
 
Les câbles relient deux points du plan : un point peut être **client** ou **concentrateur** (rejoins plusieurs câbles) ou les deux à la fois. 

Les tronçons de fibres optiques ainsi reliés bout à bout forment alors des **chaînes** dans le réseau. 

Une chaîne relie deux pointes du plan : commodité (extrémités de la chaîne). 

Il existe plusieurs opérateurs dans l’agglomération et chaque opérateur possède plusieurs chaînes de fibres optiques. 

![image](https://raw.githubusercontent.com/noob20000405/readme_pic/master/final_projet_l2/reseau.png)

Un réseau composé de 7 points et 4 chaînes.

Chaîne (1,4,6,7) reliant la commodité (1,7)

Chaîne (2,4,6,5) reliant la commodité (2,5)

Chaîne (3,2,4,6,7) reliant la commodité (3,7)

Chaîne (1,5,6) reliant la commodité (1,6)

1,3,7 sont clients (pas intérieur d’une chaîne)

4 est un concentrateur (toujours intérieur)

Les autres sont des clients et des concentrateurs

Il existe seulement 7 **câbles** dans le réseau (arêtes du graphe). Dans le câble (1,4), une seule fibre est utilisée. Dans le câble (4,6), trois fibres sont utilisées. 

Ce dessin ne donne pas l’indication du nombre ![image](https://user-images.githubusercontent.com/55035665/113162971-02f36580-9240-11eb-9676-46eb053867da.png)
 du nombre maximal des fibres utilisables par câble, mais on peut déduire que ![image](https://user-images.githubusercontent.com/55035665/113162731-d2133080-923f-11eb-9269-fb10457e7ea5.png)

## LECTURE, STOCKAGE ET AFFICHAGE DES DONNEES

### EXERCICE 1. Manipulation d’une instance de «Liste de chaînes »

But : construire une bibliothèque de manipulations d’instances

Nous utilisons : 
- Struct cellPoint est un élément de la liste des points et contient les coordonnées d’un point
- Struct cellChaine est un élément de la liste des chaînes et contient un n° de la chaîne et la liste des points
- Struct Chaines est l’ensemble des chaînes contenant le nombre maximal de fibres par câble, le nombre de chaînes et la liste des chaînes.

Fonctions : 
- Lecture et écriture de fichier : lectureChaine et ecrireChaine
- Affichage graphique des réseaux : afficheChaineSVG
- Calcul de la longueur totale des chaînes : longueurChaine
- Calcul du nombre de points : longueurTotale

**RECONSTITUTION DU RESEAU**
Reconstituer efficacement le réseau à partir des chaînes. 
    • Trouver la liste de nœuds du réseau (à une coordonnée un seul nœud) 
    • Identifier tous les câbles qui sont issus d’un nœud. (Conserver la liste des nœuds voisins à un nœud donné)
    • Récupérer et conserver la liste des commodités du réseau

### EXERCICE 2. Première méthode : stockage par liste chaînée

But : Implémenter l’algorithme de reconstitution de réseau en codant l’ensemble des nœuds du réseau par une liste chaînée. 

Nous utilisons : 
    • Reseau : liste chaînée de Noued + liste chaînée de Commodite
    • Nœud : numéro + ses coordonnées + liste chaînée des nœuds voisins (liés par un câble)
    • Commodite : deux nœuds extremités de la châine 
    
Fonctions : 
    • Nœud* rechercheCreeNoeudListe(Reseau *R, double x, double y) ; (si on a (x,y) dans R nous retournons Nœud*, sinon nous créons le nœud avec (x,y) dans R)
    • Reseau* reconstitueReseauListe(Chaines *C) ; qui reconstitue le réseau R à partir de la liste des chaînes C
