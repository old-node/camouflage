/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 aout 2017
// Ficher:	camouflage.cpp
// But:		Jeu pour le Tp1.
*/

#include <locale>
#include <vector>
#include <algorithm>
#include <iostream>
#include "partie.h"
#include "map.h"
#include "piece.h"
using namespace std;

/* Prototypes des fonctions */
///======================== */

//Ouvre le fichier selon le nom demander
void openFile(ostream& sortie, ifstream& entree, string& difficulte);	
void printPiece(vector<piece*> & vec, const int & i);

/* Programme principal */
///=================== */
int main()
{
	setlocale(LC_CTYPE, "fra");
	
	//// Solutionner le jeu

	partie jeu;

	jeu.initialiser();
	
	if (jeu.solutionner(0))
		jeu.print(cout);
	else
		cout << "Aucune solution n'est possible avec les pièces aloués." << endl;
	
	system("pause");

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

//Ouvre le fichier selon le nom demander
void openFile(ostream& sortie, ifstream& entree, string& difficulte) {
	string nomFichier;

	do
	{
		entree.clear();
		sortie << endl << "Entrer la carte à solutionner <Ex : Expert27 > : ";
		cin >> difficulte;
		nomFichier = "map" + difficulte + ".txt";
		entree.open(nomFichier.c_str());

		if (!entree.is_open()) // si fichier n’existe pas
			sortie << "Le fichier < " << nomFichier << " > n'existe pas! " << endl;

	} while (!entree.is_open());//tant que le fichier n’a pas été ouvert
}