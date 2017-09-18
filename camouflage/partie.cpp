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
	for (int r = 0; r < 4; r++)										// Pour chaque rotation
	{
		for (int x = 0; x < _boardJeu.getSizeCol(); x++)			// Pour 4 position de ligne
		{
			for (int y = 0; y < _boardJeu.getSizeLine(); y++)		// Pour 4 position de colone
			{
				if (siPieceMatch(*_pieces[pieceCourante], x, y))	// 
				{
					placerPiece(*_pieces[pieceCourante], x, y);

					if (pieceCourante == 6)							// 6 pi�ces plac�es, solution trouv�e
						return true;

					if (solutionner(pieceCourante + 1))
						return true;

					retirerPiece(*_pieces[pieceCourante], x, y);
				}
			}
		}
		_pieces[pieceCourante]->tourneDroite();
	}
	return false;
}

//V�rifie si une pi�ce peut �tre � la pos. x,y dans la map et s�il y a d�j� une pi�ce dans la solution � ces m�mes coordonn�es.
bool partie::siPieceMatch(const piece & p, int x, int y) {
	
}

//Place la pi�ce dans la solution � x, y
bool partie::placerPiece(const piece & p, int x, int y) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (p.getTuile(j, i)._code != '\0')
				_solution[x + j][y + i] = p.getTuile(j, i)._code;
}

//retire la pi�ce la solution � x, y
bool partie::retirerPiece(const piece & p, int x, int y) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (p.getTuile(j, i)._code != '\0')
				_solution[x + j][y + i] = " ";
}

//affiche la solution
void partie::print(ostream & sortie)const {
	for (int i = 0; i < _solution.size(); i++) {
		for (int j = 0; j < _solution[0].size(); j++) {
			sortie << _solution[i][j] << " ";
		}
		sortie << endl;
	}
}
