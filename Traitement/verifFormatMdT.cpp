#include <fst/fstlib.h>

using namespace fst;

//fichier en entree, fichier en sortie
int main(int argc, char *argv[]){	

	//affectation des valeurs des variables en fonction des données en paramètre
	string output = argv[2];
	string input= argv[1];


	//Récupération des automates fst à traiter n= niveau le plus bas et n1 = niveau plus haut
	StdVectorFst *i =StdVectorFst::Read(input);
	//StdVectorFst *n1 =StdVectorFst::Read(automateN1);
	
	StdVectorFst f;

	//Pour tous les états de niveau n
	for (StateIterator<StdFst> siter(*i); !siter.Done(); siter.Next()) { 
		f.AddState();
		
  		StdArc arc;
 		// Iterates over state i's arcs. 
		for (ArcIterator<StdFst> aiter(*i, siter.Value()); !aiter.Done(); aiter.Next()){
  			 arc = aiter.Value();
  			 arc.olabel = arc.ilabel;
  			 arc.weight=0;
  			 f.AddArc(siter.Value(), arc);
  			 //cout << "un nouvel arc avec " << arc.olabel << endl;
		}
	//arbitrairement nous plaçons l'état de départ sur 0 et l'état final à 0 
		int s=i->Start();
     	f.SetStart(s);
     	
	}
    f.SetFinal(0, 0);
     
	f.Write(output);
	
	return 0;
}