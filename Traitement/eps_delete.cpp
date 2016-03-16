#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;


//fonction qui fusionne les états identiques 
void fusionner(string fichierAutomate, string fichierAutomateSortie, int num_state1, int num_state2){
	//cout<< "dans fusionner pour les états : "<<num_state1 <<" et "<<num_state2<< endl;
	
	//valeur numerique des états tel que smin<smax
	int smin;
	int smax;
	
	int ns1;
	int ns2;
	//valeur des jetons
	string li;
	string lo;
	
	//variables pour la lecture et l'ecriture dans le fichier
	stringstream buffer;
	string ligne;

	ifstream a(fichierAutomate);
	ofstream a2(fichierAutomateSortie);
	
	if(num_state1<num_state2){
		smin=num_state1;
		smax=num_state2;
	}
	else{
		smin=num_state2;
		smax=num_state1;
	}
	
	
	if(a) {
		if(a2){
			getline(a, ligne);
			while(!a.eof()){
				ligne=ligne+" 1";
				buffer.str("");
				buffer.str(ligne);		
				//cout << "taille du buffer : "<<buffer.str().size() << endl; 
				
				if(buffer.str().size()>4){
					buffer>>ns1;
					//cout << "ns1 : " <<ns1<< endl;
					buffer>>ns2;
					//cout << "ns2 : " <<ns2<< endl;						
					buffer>>li;
					//cout << "li : " <<li<< endl;
					buffer>>lo;
					//cout << "lo : " <<lo<< endl;
					if((li=="eps")&&(lo=="eps")){
					}
					else{
						if(ns1==smax){a2<<smin;a2<<" ";}
						else{
							if(ns1>smax){a2<<ns1-1;a2<<" ";}
							else{a2<<ns1;a2<<" ";}
						}
	
						if(ns2==smax){a2<<smin;a2<<" ";}
						else{
							if(ns2>smax){a2<<ns2-1;a2<<" ";}
							else{a2<<ns2;a2<<" ";}
						}
						a2<<li;
						a2<<" ";
						a2<<lo;
						a2<<" ";
						a2<<endl;	
					}
				}

				if(buffer.str().size()<4){
					//cout << "contenu du nouveau buffer : " <<buffer.str()<<endl;
					buffer>>ns1;
					//cout << "ns1 : " <<ns1<< endl;
						
					if(ns1==smax){a2<<smin;a2<<" ";}
					else{
						if(ns1>smax){a2<<ns1-1;a2<<" ";}
						else{a2<<ns1;a2<<" ";}
					}
					a2<<endl;
				}
				getline(a, ligne);				
			}
			a2.close();
		}
		else{cout << "Impossible d'ouvrir l'un des fichiers!"<<endl;}
		a.close();
	}
	else{cout << "Impossible d'ouvrir l'un des fichiers!"<<endl;}
}


//fichier en txt de l'automate en entree
int main(int argc, char *argv[]){	

	//affectation des valeurs des variables en fonction des données en paramètre
	//on récupére le nom du fichier .txt qui décrit l'automate qu'on va traiter
	string automate= argv[1];
	string automateSortie=argv[2];
	
	int s1;
	int s2;

	int ns1;
	int ns2;
	string li;
	string lo;
	
	bool trans_eps_eps=false;
	
	stringstream buffer;
	string ligne;

	ifstream a(automate);
	
	
	if(a)
	{
		
		getline(a, ligne);
		
		while(!a.eof()){
			//cout << endl;
			//cout << "changement de ligne " << endl;
			//cout << "taille dde la ligne : "<<ligne.size() << endl; 
			ligne=ligne+" 1";
			buffer.str("");
			buffer.str(ligne);
			
			
			//cout << "taille du buffer : "<<buffer.str().size() << endl; 
			if(buffer.str().size()>4){
				//cout << "contenu du nouveau buffer : " <<buffer.str()<<endl;
			
				buffer>>ns1;
				//cout << "ns1 : " <<ns1<< endl;
			
				buffer>>ns2;
				//cout << "ns2 : " <<ns2<< endl;
		
				buffer>>li;
				//cout << "li : " <<li<< endl;
	
				buffer>>lo;
				//cout << "lo : " <<lo<< endl;
				
				if((li=="eps") &&(lo=="eps")){
					//cout << "ns1 : " << s1 << endl;
					//cout << "ns2 : " << s2 << endl;
					if(trans_eps_eps){
					//on a déjà trouvé une transition eps eps
						if((s1==ns2) && (s2==ns1)){							
						//c'est bien l'inverse de la transition eps eps déjà trouvé
							a.close();
							fusionner(automate, automateSortie,ns1, ns2);
							trans_eps_eps=false;
						}
					}
					else{
						//c'est la premiere trnasition eps eps
						trans_eps_eps=true;
						s1=ns1;
						s2=ns2;
					}
				}
			}
			getline(a, ligne);
		}
		a.close();
	}
	else
		cout << "Impossible d'ouvrir le fichier!"<<endl;
	
	return 0;
}