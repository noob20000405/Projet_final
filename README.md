# Projet : Réorganisation d’un réseau de fibres optiques
## CADRE DU PROJET
- 1ère partie : reconstituer le plan du réseau de l’agglomération. Chaque opérateur connaît les tronçons de fibres optiques qu’il utilise dans le réseau. Il y a au moins une fibre utilisée par câble. 
- 2ème partie : réorganiser les attributions de fibres de chacun des opérateurs. 
Un câble est un fourreau contenant exactement fibres optiques. 
Les câbles relient deux points du plan : un point peut être client ou concentrateur (rejoins plusieurs câbles) ou les deux à la fois. 
Les tronçons de fibres optiques ainsi reliés bout à bout forment alors des chaînes dans le réseau. 
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
Il existe seulement 7 câbles dans le réseau (arêtes du graphe). Dans le câble (1,4), une seule fibre est utilisée. Dans le câble (4,6), trois fibres sont utilisées. 
Ce dessin ne donne pas l’indication du nombre  du nombre maximal des fibres utilisables par câble, mais on peut déduire que ![image](https://user-images.githubusercontent.com/55035665/113162731-d2133080-923f-11eb-9269-fb10457e7ea5.png)
