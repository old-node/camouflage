/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	04 septembre 2017
// Ficher:	partie.cpp
// But:		M�thodes de l'objet partie.
*/

#include "partie.h"
using namespace std;

//initialise le jeu
void partie::initialiser() {
	_solution.resize(_boardJeu.getSizeLine(), vector<string>(_boardJeu.getSizeCol()));
}

//Trouver la position des 6 pi�ces qui solutionnent le casse-t�te selon la map
bool partie::solutionner(int pieceCourante) {

}

//V�rifie si une pi�ce peut �tre � la pos. x,y dans la map et s�il y a d�j� une pi�ce dans la solution � ces m�mes coordonn�es.
bool partie::siPieceMatch(const piece &, int x, int y) {

}

//Place la pi�ce dans la solution � x, y
bool partie::placerPiece(const piece& p, int x, int y) {

}

//retire la pi�ce la solution � x, y
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
