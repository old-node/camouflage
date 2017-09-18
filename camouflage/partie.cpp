/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	04 septembre 2017
// Ficher:	partie.cpp
// But:		M�thodes de l'objet partie.
*/

#include "partie.h"
#include <string>
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

					partie::print(cout);
					
					if (pieceCourante == 5)							// 6 pi�ces plac�es, solution trouv�e
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
bool partie::siPieceMatch(const piece& p, int x, int y) {
	//Pour les 4 cases de la pi�ce
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {

			//On v�rifie si la case de la pi�ce est valide
			if (p.getTuile(i, j) != '\0') {

				//Si la case de la pi�ce n'est pas en dehors de la carte
				if ((x + i) < _boardJeu.getSizeCol() && (y + j) < _boardJeu.getSizeLine()) {

					//Si la case corespondante de la solution est vide
					if (_solution[x + i][y + j] == " ") {

						//Si la tuile est un poisson mais que la case sur la carte n'est pas de l'eau on retourne faux
						if (p.getTuile(i, j) == 'P' && _boardJeu.getCase(x + i, y + j) != 'E')
							return false;

						//Si la tuile est un ours mais que la case sur la carte n'est pas une banquise on retourne faux
						if (p.getTuile(i, j) == 'O' && _boardJeu.getCase(x + i, y + j) != 'B')
							return false;
					}
					else
						return false;
				}
				else
					return false;
			}
		}
	}
	return true;
}

//Place la pi�ce dans la solution � x, y
bool partie::placerPiece(const piece & p, int x, int y) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (p.getTuile(j, i) != '\0')
				_solution[x + j][y + i] = p.getTuile(j, i);
}

//retire la pi�ce la solution � x, y
bool partie::retirerPiece(const piece & p, int x, int y) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (p.getTuile(j, i) != '\0')
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
