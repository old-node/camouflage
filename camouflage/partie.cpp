/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	04 septembre 2017
// Ficher:	partie.cpp
// But:		M�thodes de l'objet partie.
*/

#include "partie.h"
#include <string>
using namespace std;

//initialise le jeu
void partie::initialiser(ofstream& sortie) {
	//On initialise la carte avec le fichier
	ifstream entree;
	openFile(cout, entree);
	_boardJeu.init(entree);

	//On ouvre le fichier de sortie et on inscrit les dimensions de la carte dedans
	sortie.open("solution" + difficulte + ".txt");
	sortie << _boardJeu.getSizeLine() << ", " << _boardJeu.getSizeCol() << endl << endl;

	//On affiche la carte � solutionner
	cout << "Contenu original de la planche du fichier :" << endl;
	cout << _boardJeu;

	//On initialise le tableau de solution
	_solution.resize(_boardJeu.getSizeLine(), vector<string>(_boardJeu.getSizeCol()));
	for (int i = 0; i < _solution.size(); i++) {
		for (int j = 0; j < _solution[0].size(); j++) {
			_solution[i][j] = " ";
		}
	}

	//On initialise les 6 pi�ces
	_pieces.push_back(new piece3cases('U', " PO"));
	_pieces.push_back(new piece3cases('V', "P O"));
	_pieces.push_back(new piece3cases('W', " OP"));
	_pieces.push_back(new piece2cases('X', "PP"));
	_pieces.push_back(new piece2cases('Y', "PO"));
	_pieces.push_back(new piece3cases('Z', "O  "));
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

					print(cout);
					cout << endl;

					if (pieceCourante == 5)							// 6 pi�ces plac�es, solution trouv�e
					{
						_trouve = true;
						return true;
					}

					if (solutionner(pieceCourante + 1))
					{
						_trouve = true;
						return true;
					}

					retirerPiece(*_pieces[pieceCourante], x, y);
				}
			}
		}
		_pieces[pieceCourante]->tourneDroite();
	}
	_trouve = false;
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
void partie::placerPiece(const piece & p, int x, int y) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (p.getTuile(j, i) != '\0') {
				_solution[x + j][y + i] = p.getNom();
				_solution[x + j][y + i] += p.getTuile(j, i);
			}
}

//retire la pi�ce la solution � x, y
void partie::retirerPiece(const piece & p, int x, int y) {
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

//Ouvre le fichier selon le nom demander
void partie::openFile(ostream& sortie, ifstream& entree) {
	string nomFichier;

	do
	{
		entree.clear();
		sortie << endl << "Entrer la carte � solutionner <Ex : Expert27 > : ";
		cin >> difficulte;
		nomFichier = "map" + difficulte + ".txt";
		entree.open(nomFichier.c_str());

		if (!entree.is_open()) // si fichier n�existe pas
			sortie << "Le fichier < " << nomFichier << " > n'existe pas! " << endl;

	} while (!entree.is_open());//tant que le fichier n�a pas �t� ouvert
}

ostream & operator<<(ostream & sortie, const partie & jeu)
{
	// TODO: insert return statement here
	return sortie;
}
