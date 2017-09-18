/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
// Ficher:	partie.cpp
// But:		Objet qui manipule les différentes versions du jeu.
*/

#pragma once
#include "map.h"
#include "piece.h"
using namespace std;

class partie
{
private:
	piece *_pieces[6]; //les 6 pièces du casse tête
	map _boardJeu; //map du casse tête
	vector<vector<string>> _solution; //La solution du casse tête
	bool _trouve; //Si une solution a été trouvée
public:
	void initialiser(); //initialise le jeu
	//Trouver la position des 6 pièces qui solutionnent le casse-tête selon la map
	bool solutionner(int pieceCourante);
	//Vérifie si une pièce peut être à la pos. x,y dans la map et s’il y a déjà une pièce dans la solution à ces mêmes coordonnées.
	bool siPieceMatch(const piece &, int x, int y);
	bool placerPiece(const piece& p, int x, int y);		//Place la pièce dans la solution à x, y
	bool retirerPiece(const piece& p, int x, int y);	//retire la pièce la solution à x, y
	void print(ostream& sortie)const;					//affiche la solution
};
//affiche la solution
ostream& operator<<(ostream& sortie, const partie& jeu);