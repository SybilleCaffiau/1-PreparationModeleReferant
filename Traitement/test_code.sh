#/usr/bash


echo "Début du processus de transformation"

#demande les informations pour executer le programme de transformation
echo "fichier de symbols prendre pour l'affichage (format .syms) ?"
echo "Attention : votre fichier de symbol doit nécessairement avoir eps 0 en première ligne et R 1 en seconde ligne"
read noml

echo "la première étape est de produire tous les automates à partir des fichiers textes (stop pour arreter) "

g++ -std=c++11 -I ../../../EvaluationMaquetteMdT/VerifMaquettesMdTCogtool/testCpp/openfst-1.5.0/src/include eps_delete.cpp -L ../../../EvaluationMaquetteMdT/VerifMaquettesMdTCogtool/testCpp/openfst-1.5.0/src/lib -lfst -o formate

read -p 'Nom du fichier à convertir (.txt) : ' model
until [ $model == 'stop' ]
do
        read -p 'Nom du fichier automate (.fst) : ' automate
        fstcompile --isymbols=$noml --osymbols=$noml $model | fstarcsort > $automate
        read -p 'Nom du fichier à convertir (.txt) : ' model
done

#compile le programme cpp de transformation : remplacer les chemin pour mettre ceux où se trouve la librairie openFst
g++ -std=c++11 -I ../../../EvaluationMaquetteMdT/VerifMaquettesMdTCogtool/testCpp/openfst-1.5.0/src/include trans.cpp -L ../../../EvaluationMaquetteMdT/VerifMaquettesMdTCogtool/testCpp/openfst-1.5.0/src/lib -lfst -o myapp


echo "la seconde étape est de supprimer un à un chacun des niveaux en commençant par le plus bas et en remontant jusqu à la racine"

read -p 'Quel est l automate de bas niveau (.fst) ? - stop pour arreter ' A1

until [ $A1 == 'stop' ]
do
	
	fstprint --isymbols=$noml --osymbols=$noml $A1

	read -p 'Quel est l automate de haut niveau (.fst) ? ' A0
	fstprint --isymbols=$noml --osymbols=$noml $A0

	read -p 'Quel est le numero du jeton que vous voulez remplacer pour réduire ce niveau ?' l

	#execute le programme de transformation
	echo "la suppression du niveau representé par le jeton n° $l"
	./myapp $A0 $A1 $l
	
	echo "n1test.fst"
	fstprint --isymbols=$noml --osymbols=$noml n1test.fst
	
	echo "ntest.fst"
	fstprint --isymbols=$noml --osymbols=$noml ntest.fst
	
	read -p 'Comment voulez vous nommer le résultat de la transformation (.fst) ?' res
	
	#remplacement 
	#n1test.fst et ntest.fst sont produits par myapp : NE PAS MODIFIER
	
	fstrmepsilon n1test.fst | fstarcsort > n1test_rm.fst
	fstrmepsilon ntest.fst | fstarcsort > ntest_rm.fst
	
	#fstreplace --epsilon_on_replace n1test_rm.fst 1 ntest_rm.fst $l | fstarcsort > MdT1.fst
	fstreplace --epsilon_on_replace n1test_rm.fst 1 ntest_rm.fst $l | fstarcsort > $res

	read -p 'Quel est le nom du fichier pour sauvegarder l automate en text (.txt) ? ' r

	fstprint --isymbols=$noml --osymbols=$noml $res > $r
	read -p 'Quel est le nom du fichier pour l automate sans transitions eps/eps (.txt) ? ' r1

	./formate $r $r1
	
	fstcompile --isymbols=$noml --osymbols=$noml r1 | fstarcsort > $res
	
	
	read -p 'Quel est l automate de bas niveau (.fst) ? - stop pour arreter ' A1
done


echo "Fin du processus de transformation, votre fichier résultat final contenant l'automate plat complet est nommé $r"
