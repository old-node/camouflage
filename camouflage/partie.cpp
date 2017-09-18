/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	04 septembre 2017
// Ficher:	partie.cpp
// But:		Méthodes de l'objet partie.
*/

#include "partie.h"
using namespace std;

//initialise le jeu
void partie::initialiser() {
	_solution.resize(_boardJeu.getSizeLine(), vector<string>(_boardJeu.getSizeCol()));
}

//Trouver la position des 6 pièces qui solutionnent le casse-tête selon la map
bool partie::solutionner(int pieceCourante) {

}

//Vérifie si une pièce peut être à la pos. x,y dans la map et s’il y a déjà une pièce dans la solution à ces mêmes coordonnées.
bool partie::siPieceMatch(const piece &, int x, int y) {

}

//Place la pièce dans la solution à x, y
bool partie::placerPiece(const piece& p, int x, int y) {

}

//retire la pièce la solution à x, y
bool partie::retirerPiece(const piece& p, int x, int y) {

}

//affiche la solution
void partie::print(ostream& sortie)const {
	for (int i = 0; i < _solution.size(); i++) {
		for (int j = 0; j < _solution[0].size(); j++) {
			sortie << _solution[i][j] << " ";
		}
		sortie << endl;
	}
}
