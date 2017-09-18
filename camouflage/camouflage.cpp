/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
// Ficher:	camouflage.cpp
// But:		Jeu pour le Tp1.
*/

#include <locale>
#include <vector>
#include <algorithm>
#include <iostream>
//#include <saisieSecurisee.h>
#include "partie.h"
#include "map.h"
#include "piece.h"
using namespace std;

/* Prototypes des fonctions */
///======================== */

void openFile(ostream& sortie, ifstream& entree, string& difficulte);	//Ouvre le fichier selon le nom demander
void tournePieces(vector<piece*> & vec);
void printPiece(vector<piece*> & vec, const int & i);


/* Programme principal */
///=================== */
int main()
{
	setlocale(LC_CTYPE, "fra");

	//// Test Carte

	map carte;
	ifstream entree;
	string	difficulte;

	//Initialise la carte grace � un fichier
	openFile(cout, entree, difficulte);
	carte.init(entree);

	//Test des diff�rentes fa�on d'imprimer la carte
	carte.print(cout);
	cout << endl;
	cout << carte;
	cout << endl;

	//Cherche une case dans la carte et imprime son charact�re
	char getCase;
	getCase = carte.getCase(0, 0);
	cout << getCase;
	cout << endl;

	getCase = carte.getCase(2, 3);
	cout << getCase;
	cout << endl;

	system("pause");


	//// Test Pi�ces

	vector<piece*> vec;			// Vecteur comprenant toutes les pi�ces du jeu

	vec.push_back(new piece3cases('U', " PO"));
	vec.push_back(new piece3cases('V', "P O"));
	vec.push_back(new piece3cases('W', " OP"));
	vec.push_back(new piece2cases('X', "PP"));
	vec.push_back(new piece2cases('Y', "PO"));
	vec.push_back(new piece3cases('Z', "O  "));

	// Fait pivoter la pi�ce Z pour qu'elle d�bute de la bonne position
	for (int i = 0; i < 3; i++)
		vec.at(5)->tourneDroite();


	cout << "\n\nVoici toutes les formes sous leur angles d'origine.\n";
	for (int i = 0; i < vec.size(); i++)		// Affichage initial
		printPiece(vec, i);

	for (int i = 0; i < 3; i++)					// Pour tout les autres angles
	{
		cout << "\n\nVoici toutes les formes sous leur angle suivant\n";
		tournePieces(vec);						// Pour toutes les pi�ces
		for (int j = 0; j < vec.size(); j++)
			printPiece(vec, j);
	}

	system("pause");

	return 1;
}

/* Fonctions */
///========= */

// Fait pivoter les pi�ces du jeu
void tournePieces(vector<piece*> & vec)
{
	for (int i = 0; i < vec.size(); i++)
		vec.at(i)->tourneDroite();
}
// Affiche les pi�ces dans la console selon leur type
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
		sortie << endl << "Entrer la carte � solutionner <Ex : Expert27 > : ";
		cin >> difficulte;
		nomFichier = "map" + difficulte + ".txt";
		entree.open(nomFichier.c_str());

		if (!entree.is_open()) // si fichier n�existe pas
			sortie << "Le fichier < " << nomFichier << " > n'existe pas! " << endl;

	} while (!entree.is_open());//tant que le fichier n�a pas �t� ouvert
}