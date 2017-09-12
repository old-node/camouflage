/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
// Ficher:	map.cpp
// But:		Méthodes de l'objet map.
*/

#include "map.h"
using namespace std;

map::map()
{

}

map::~map()
{

}

//Ouvre le fichier et apelle la fonction de lecture de fichier
string map::openFile(ostream& sortie){
	string	difficulte, nomFichier;

	do
	{
		_entree.clear();
		sortie << endl << "Entrer la carte à solutionner <Ex : Expert27 > : ";
		cin >> difficulte;
		nomFichier = "map" + difficulte + ".txt";
		_entree.open(nomFichier.c_str());

		if (!_entree.is_open()) // si fichier n’existe pas
			sortie << "Le fichier < " << nomFichier << " > n'existe pas! " << endl;

	} while (!_entree.is_open());//tant que le fichier n’a pas été ouvert
	initMap();
	return difficulte;
}

//Lit le fichier et initialise la carte avec
void map::initMap() {
	int tailleVX, tailleVY;
	_entree >> tailleVX;
	_entree.ignore();
	_entree >> tailleVY;
	_map.resize(tailleVX, vector<char>(tailleVY));
	for (int i = 0; i < tailleVX; i++) {
		for (int j = 0; j < tailleVY; j++) {
			_entree >> _map[i][j];
		}
	}
	_entree.close();
}

//Affiche le contenu de la carte
void map::print(ostream& sortie)const {
	sortie << "Contenu original de la planche du fichier :" << endl;
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
char map::getCase(int x, int y)const {
	return _map[x][y];
}