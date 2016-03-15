#include <fst/fstlib.h>

using namespace fst;

//pour le moment on ne tient pas compte du poid des arcs
//haut, bas, jeton
int main(int argc, char *argv[]){	

	//affectation des valeurs des variables en fonction des données en paramètre
	string automateN = argv[2];
	string automateN1= argv[1];
	int l=atoi(argv[3]);
	int lprod;

	//Récupération des automates fst à traiter n= niveau le plus bas et n1 = niveau plus haut
	StdVectorFst *n =StdVectorFst::Read(automateN);
	StdVectorFst *n1 =StdVectorFst::Read(automateN1);
	
	StdVectorFst f;

	 //Pour tous les états de niveau n1
    for (StateIterator<StdFst> siter(*n1); !siter.Done(); siter.Next()) {
    	//pour tous les input des transitions qui partent de l'état
		Matcher<StdFst> matcher(*n1, MATCH_INPUT);
		matcher.SetState(siter.Value());
			//si l'input est le numéro du jeton qu'on veut remplacer
			if (matcher.Find(l)) 
  				for (; !matcher.Done(); matcher.Next()){
     				const StdArc &arc = matcher.Value();
     				//L'arc de l'automate consomme l
			    	//on cree une transition en inversant les labels
			    	//(dep, arc(labelin,labelout,poid,fin)
			    	lprod=matcher.Value().olabel;
			   		n1->AddArc(0, StdArc(matcher.Value().olabel, l, 1, 0));
  				}
	}
     

	//Pour tous les états de niveau n
	for (StateIterator<StdFst> siter(*n); !siter.Done(); siter.Next()) { 
		f.AddState();
		
  		StdArc arc;
 		// Iterates over state i's arcs. 
		for (ArcIterator<StdFst> aiter(*n, siter.Value()); !aiter.Done(); aiter.Next()){
  			 arc = aiter.Value();
  			 if(arc.olabel==l){
  			 	//cout << "dans trouve" <<endl;
  			 	arc.olabel = lprod;
  			 	//aiter.SetValue(arc);
  			 }
  			 //arc.olabel = arc.ilabel;
  			 f.AddArc(siter.Value(), arc);
  			 cout << "un nouvel arc avec " << arc.olabel << endl;
		}
	//arbitrairement nous plaçons l'état de départ sur 0 et l'état final à 0 
     	f.SetStart(0);
     	
	}
    f.SetFinal(0, 0);
   
    
     
	//n->Write("ntest.fst");
	n1->Write("n1test.fst");
	f.Write("ntest.fst");
	
	return 0;
}