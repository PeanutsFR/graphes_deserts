
======> ATTENTION : maximum_complet est buggé -> lancer le test avec le graphe tr1 pour s'en apercevoir.



graphes_deserts
===============

AMU - TP Complexite - Graphes Déserts


+--------------------------+
    Travail Réalisé
+--------------------------+

L'intégralité du travail a été réalisé, en utilisant les deux représentations d'un graphe :
  - sous forme de listes d'adjacence
  - sous forme de matrice

/!\ La version matricielle n'est pas stable, des corrections doivent encore être apportées.


+--------------------------+
    Fonctionnement
+--------------------------+

** Les fichiers .c et .h sont dans les dossiers :
    - /src_listes (graphes sous forme de listes)
    - /src_matrices (graphes sous forme de matrices)

** Les fichiers tests sont dans /utils/Benchs

** Pour compiler se placer dans le dossier voulu (verification, maximum etc ), puis exécuter la commande : make

** Les fichiers exécutables sont dans le dossier /bin

** Pour exécuter : ./bin/<nom_du_prog> ./<chemin_vers_fichier_test>/<nom du fichier>

** Les exécutables sont :
    - maximal
    - maximalite
    - maximum_complet
    - maximum_incomplet
    - verification

** Pour verification et maximalite , il faut entrer les sommets un par un au clavier, puis entrer une lettre pour finir la saisie.
Par exemple pour saisir l'ensemble (1,2,3), taper :
  1 (puis Entrer)
	2 (puis Entrer)
	3 (puis Entrer)
	q (puis Entrer)


** Pour nettoyer : make clean


+--------------------------+
    Page du Projet
+--------------------------+

http://www.lsis.org/terriouxc/index.php?page=M1_Consignes
