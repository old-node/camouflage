/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 aoÃ»t 2017
// Ficher:	camouflage.cpp
// But:		Jeu pour le Tp1.
*/

#include <locale>
#include <vector>
#include <algorithm>
#include <iostream>
#include <saisieSecurisee.h>
//#include "partie.h"
#include "map.h"
#include "piece.h"
using namespace std;

/* Prototypes des fonctions */
///======================== */

void tournePieces(vector<piece*> & vec);
void printPiece(vector<piece*> & vec, const int & i);


/* Programme principal */
///=================== */
int main()
{
	setlocale(LC_CTYPE, "fra");

	//// Test Carte

	map carte;

	carte.openFile(cout);
	carte.print(cout);
	cout << endl;
	cout << carte;
	cout << endl;
	char getCase;
	getCase = carte.getCase(0, 0);
	cout << getCase;
	cout << endl;

	pause();


	//// Test Pièces

	vector<piece*> vec;			// Vecteur comprenant toutes les pièces du jeu

	vec.push_back(new piece3cases('U', " PO"));
	vec.push_back(new piece3cases('V', "P O"));
	vec.push_back(new piece3cases('W', " OP"));
	vec.push_back(new piece2cases('X', "PP"));
	vec.push_back(new piece2cases('Y', "PO"));
	vec.push_back(new piece3cases('Z', "O  "));

	// Fait pivoter la pièce Z pour qu'elle débute de la bonne position
	for (int i = 0; i < 3; i++)
		vec.at(5)->tourneDroite();


	cout << "\n\nVoici toutes les formes sous leur angles d'origine.\n";
	for (int i = 0; i < vec.size(); i++)		// Affichage initial
		printPiece(vec, i);

	for (int i = 0; i < 3; i++)					// Pour tout les autres angles
	{
		cout << "\n\nVoici toutes les formes sous leur angle suivant\n";
		tournePieces(vec);						// Pour toutes les pièces
		for (int j = 0; j < vec.size(); j++)
			printPiece(vec, j);
	}

	pause();

	return 1;
}

/* Fonctions */
///========= */

// Fait pivoter les pièces du jeu
void tournePieces(vector<piece*> & vec)
{
	for (int i = 0; i < vec.size(); i++)
		vec.at(i)->tourneDroite();
}
// Affiche les pièces dans la console selon leur type
void printPiece(vector<piece*> & vec, const int & i)
{
	piece2cases *morceau = dynamic_cast<piece2cases*>(vec.at(i));
	if (morceau)
		morceau->print(cout);
	else
	{
		piece3cases *morceau = dynamic_cast<piece3cases*>(vec.at(i));
		morceau->print(cout);
	}
}