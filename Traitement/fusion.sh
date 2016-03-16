#/usr/bash


echo "Début du processus de fusion"

#demande les informations pour executer le programme de transformation
echo "fichier de symbols prendre pour l'affichage (format .syms) ?"
echo "Attention : votre fichier de symbol doit nécessairement avoir eps 0 en première ligne et R 1 en seconde ligne"
read noml

g++ -std=c++11 -I ../../../EvaluationMaquetteMdT/VerifMaquettesMdTCogtool/testCpp/openfst-1.5.0/src/include eps_delete.cpp -L ../../../EvaluationMaquetteMdT/VerifMaquettesMdTCogtool/testCpp/openfst-1.5.0/src/lib -lfst -o formate

read -p 'Quel est l automate de bas niveau (.txt) ? ' A1
read -p 'Nom du fichier automate (.fst) : ' automate1
fstcompile --isymbols=$noml --osymbols=$noml $A1 | fstarcsort > $automate1
fstprint --isymbols=$noml --osymbols=$noml $automate1

read -p 'Quel est l automate de haut niveau (.txt) ? ' A2
read -p 'Nom du fichier automate (.fst) : ' automate2
fstcompile --isymbols=$noml --osymbols=$noml $A2 | fstarcsort > $automate2
fstprint --isymbols=$noml --osymbols=$noml $automate2


#compile le programme cpp de transformation : remplacer les chemin pour mettre ceux où se trouve la librairie openFst
g++ -std=c++11 -I ../../../EvaluationMaquetteMdT/VerifMaquettesMdTCogtool/testCpp/openfst-1.5.0/src/include trans.cpp -L ../../../EvaluationMaquetteMdT/VerifMaquettesMdTCogtool/testCpp/openfst-1.5.0/src/lib -lfst -o myapp


read -p 'Quel est le numero du jeton que vous voulez remplacer pour réduire ce niveau ?' l

#execute le programme de transformation
echo "la suppression du niveau representé par le jeton n° $l"
./myapp $automate2 $automate1 $l
	
echo "n1test.fst"
fstprint --isymbols=$noml --osymbols=$noml n1test.fst
	
echo "ntest.fst"
fstprint --isymbols=$noml --osymbols=$noml ntest.fst
	
read -p 'Comment voulez vous nommer le résultat de la transformation (.txt) ?' res

#remplacement 
#n1test.fst et ntest.fst sont produits par myapp : NE PAS MODIFIER
	
fstrmepsilon n1test.fst | fstarcsort > n1test_rm.fst
fstrmepsilon ntest.fst | fstarcsort > ntest_rm.fst
	
fstreplace --epsilon_on_replace n1test_rm.fst 1 ntest_rm.fst $l | fstarcsort > MdT1.fst
fstprint --isymbols=$noml --osymbols=$noml MdT1.fst > MdT1.txt

./formate MdT1.txt $res


echo "Fin du processus de transformation, votre fichier résultat final contenant l'automate plat complet est nommé $res"
