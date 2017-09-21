/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	04 septembre 2017
// Ficher:	partie.cpp
*/

#include "partie.h"

//initialise le jeu
void partie::initialiser(ofstream& sortie) {
	//On initialise la carte avec le fichier
	ifstream entree;
	openFile(cout, entree);
	_boardJeu.init(entree);

	//On ouvre le fichier de sortie et on inscrit les dimensions de la carte dedans
	sortie.open("solution" + difficulte + ".txt");
	sortie << _boardJeu.getSizeLine() << ", " << _boardJeu.getSizeCol() << endl << endl;

	//On affiche la carte à solutionner
	cout << "Contenu original de la planche du fichier :" << endl;
	cout << _boardJeu;

	//On initialise le tableau de solution
	_solution.resize(_boardJeu.getSizeLine(), vector<string>(_boardJeu.getSizeCol()));
	for (int i = 0; i < _solution.size(); i++) {
		for (int j = 0; j < _solution[0].size(); j++) {
			_solution[i][j] = " ";
		}
	}

	//On initialise les 6 pièces
	_pieces.push_back(new piece3cases('U', " PO"));
	_pieces.push_back(new piece3cases('V', "P O"));
	_pieces.push_back(new piece3cases('W', " OP"));
	_pieces.push_back(new piece2cases('X', "PP"));
	_pieces.push_back(new piece2cases('Y', "PO"));
	_pieces.push_back(new piece3cases('Z', "O  "));
}

//Trouver la position des 6 pièces qui solutionnent le casse-tête selon la map
bool partie::solutionner(int pieceCourante) {
	static int nbItteration = 1;

				// Pour chaque rotation
	for (int r = 0; r < 4; r++)		
	{
		int etendueCol = _boardJeu.getSizeCol();
		int etendueLine = _boardJeu.getSizeLine();
		
				// Vérification pour rendre le brute force plus performant
		if (_pieces[pieceCourante]->getNbTuile() == 2)
			if (dynamic_cast<piece2cases*> (_pieces[pieceCourante])->getAngle())
				etendueLine--;
			else
				etendueCol--;
		
				// Pour 4 position de ligne
		for (int x = 0; x < etendueCol; x++)						
				// Pour 4 position de colone	
			for (int y = 0; y < etendueLine; y++)
				if (siPieceMatch(*_pieces[pieceCourante], x, y))	
				{		
					placerPiece(*_pieces[pieceCourante], x, y);
					
					cout << "Ittération No " << nbItteration++ << endl;
					print(cout);
					cout << endl;

					// 6 pièces placées ou solution trouvée
					if (pieceCourante == 5 || solutionner(pieceCourante + 1))
						return _trouve = true;

					retirerPiece(*_pieces[pieceCourante], x, y);
				}
		_pieces[pieceCourante]->tourne();
	}
	_trouve = false;
	return false;
}


//VÃ©rifie si une pièce peut être à la pos. x,y dans la map et s'il y a dÃ©jà une pièce dans la solution à ces mêmes coordonnÃ©es.
bool partie::siPieceMatch(const piece& p, int x, int y) {
	//Pour les 4 cases de la pièce
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {

			//On vÃ©rifie si la case de la pièce est valide
			if (p.getTuile(i, j) != '\0') {

				//Si la case de la pièce n'est pas en dehors de la carte
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

//Place la pièce dans la solution à x, y
void partie::placerPiece(const piece & p, int x, int y) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (p.getTuile(j, i) != '\0') {
				_solution[x + j][y + i] = p.getNom();
				_solution[x + j][y + i] += p.getTuile(j, i);
			}
}

//retire la pièce la solution à x, y
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
		sortie << endl << "Entrer la carte à solutionner <Ex : Expert27 > : ";
		cin >> difficulte;
		nomFichier = "map" + difficulte + ".txt";
		entree.open(nomFichier.c_str());

		if (!entree.is_open()) // si fichier n'existe pas
			sortie << "Le fichier < " << nomFichier << " > n'existe pas! " << endl;

	} while (!entree.is_open());//tant que le fichier n'a pas Ã©tÃ© ouvert
}

ostream & operator<<(ostream & sortie, const partie & jeu)
{
	// TODO: insert return statement here
	return sortie;
}
