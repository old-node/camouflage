/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 ao�t 2017
// Ficher:	partie.cpp
// But:		Objet qui manipule les diff�rentes versions du jeu.
*/

#pragma once
using namespace std;

// 
class partie
{
private:
	bool _terminee = false;
	bool _menu = true;
	bool _nouvellePartie = false;


public:
	partie();
	~partie();

};

partie::partie()
{
}

partie::~partie()
{
}