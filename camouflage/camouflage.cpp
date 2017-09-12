/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
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

map carte;
/* Programme principal */
///=================== */
int main()
{
	setlocale(LC_CTYPE, "fra");

	//Test Pi�ces
	piece2cases X('X', "PP"), Y('Y', "PO");
	piece3cases U('U', "_PO"), V('V', "P_O"), W('W', "_OP"), Z('Z', "_O_");
	// vector<piece> morceaux = { U, V, W, Z, X, Y };

	// X.tourneDroite();
	cout << X;

	pause();

	//Test Carte
	carte.openFile(cout);
	carte.print(cout);
	cout << endl;
	cout << carte;
	cout << endl;
	char getCase;
	getCase = carte.getCase(0, 0);
	cout << getCase;
	cout << endl;
	system("pause");

	return 1;
}

/* Fonctions */
///========= */
// 
// modification