#include <fst/fstlib.h>

using namespace fst;

//pour le moment on ne tient pas compte du poid des arcs
//automateModelTaches automateModelTachesSansEpsEps
int main(int argc, char *argv[]){	

	string automateMdT= argv[1];

	//Récupération de l'automate fst à traiter
	StdVectorFst *m =StdVectorFst::Read(automateMdT);
	 //l'automate modifié
	StdVectorFst f;

	//Pour tous les états de l'automate
	for (StateIterator<StdFst> siter(*m); !siter.Done(); siter.Next()) { 
		f.AddState();
		
  		StdArc arc;
 		// Iterates over state i's arcs. 
		for (ArcIterator<StdFst> aiter(*m, siter.Value()); !aiter.Done(); aiter.Next()){
  			 arc = aiter.Value();
  			 if((arc.olabel = arc.ilabel)&&(arc.olabel = "eps")){
  			 	cout << "arc eps/eps " << endl;
  			 	
  			 }
  			 else {
  			 	f.AddArc(siter.Value(), arc);
  			 }
  			 
		}
		//arbitrairement nous plaçons l'état de départ sur 0 et l'état final à 0 également
     	f.SetStart(0);
	}
    f.SetFinal(0, 0);

	f.Write(argv[2]);
	
	return 0;
}