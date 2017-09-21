/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
// Ficher:	map.cpp
// But:		Méthodes de l'objet map.
*/

#include "map.h"


//Constructeur par défaut
map::map()
{

}

//Constructeur avec dimensions en paramètre
map::map(int nbLigne, int nbCol)
{
	resize(nbLigne, nbCol);
}

//Destructeur par défaut
map::~map()
{
	_map.clear();
}

//Lit le fichier et initialise la carte avec
void map::init(ifstream& entree) {
	assert(entree.is_open());

	int nbLigne, nbCol;

	//lecture des dimensions de la map
	entree >> nbLigne;						
	entree.ignore();
	entree >> nbCol;
	
	resize(nbLigne, nbCol);

	//initialisation de la map à partir du fichier
	for (int i = 0; i < nbLigne; i++) {		
		for (int j = 0; j < nbCol; j++) {
			entree >> _map[i][j];
		}
	}
}

//resize la matrice selon les dimensions
void map::resize(int nbLigne, int nbCol)
{
	assert(nbLigne >= 0 && nbCol >= 0);

	//Redimmensionne le vecteur extérieur et le vecteur intérieur dans la même ligne
	_map.resize(nbLigne, vector<char>(nbCol));
}

//Affiche le contenu de la carte
void map::print(ostream& sortie)const {

	for (int i = 0; i < _map.size(); i++) {
		for (int j = 0; j < _map[0].size(); j++) {
			sortie << _map[i][j] << " ";
		}
		sortie << endl;
	}
}

ostream& operator<<(ostream& sortie, const map& printMap) {
	printMap.print(sortie);
	return sortie;
}

//Retourne le contenu d'une case de la carte selon sa position X,Y
char map::getCase(int i, int j)const {
	assert(i >= 0 && i < _map.size() && j >= 0 && j < _map[0].size());

	return _map[i][j];
}

//Retourne le nombre de ligne du vecteur (Taille du grand vecteur)
int map::getSizeLine()const {
	return _map.size();
}

//Retourne le nombre de colonnes du vecteur (Taille des petits vecteurs)
int map::getSizeCol()const {
	return _map[0].size();
}

//Modifie le contenu d'une case de la carte selon sa position X,Y
void  map::setCase(char val, int i, int j) {
	assert(i >= 0 && i < _map.size() && j >= 0 && j < _map[0].size());

	_map[i][j] = val;
}