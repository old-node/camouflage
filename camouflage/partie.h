/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 ao�t 2017
// Ficher:	partie.cpp
// But:		Objet qui manipule les diff�rentes versions du jeu.
*/

#pragma once
#include <string>
#include "map.h"
#include "piece.h"
using namespace std;

class partie
{
private:
	vector<piece*> _piece;			// Vecteur comprenant toutes les pi�ces du jeu
	map _boardJeu;		// Map du casse t�te
	vector<vector<string>> _solution; //La solution du casse t�te
	bool _trouve; //Si une solution a �t� trouv�e
public:
	void initialiser(); //initialise le jeu
	//Trouver la position des 6 pi�ces qui solutionnent le casse-t�te selon la map
	bool solutionner(int pieceCourante);
	//V�rifie si une pi�ce peut �tre � la pos. x,y dans la map et s�il y a d�j� une pi�ce dans la solution � ces m�mes coordonn�es.
	bool siPieceMatch(const piece& p, int x, int y);
	bool placerPiece(const piece& p, int x, int y);		//Place la pi�ce dans la solution � x, y
	bool retirerPiece(const piece& p, int x, int y);	//retire la pi�ce la solution � x, y
	void print(ostream& sortie)const;					//affiche la solution
	void openFile(ostream& sortie, ifstream& entree, string& difficulte); //Ouvre le fichier selon le nom demander
};
//affiche la solution
ostream& operator<<(ostream& sortie, const partie& jeu);