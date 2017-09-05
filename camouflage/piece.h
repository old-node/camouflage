/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
// Ficher:	map.cpp
// But:		Objet du jeu utilisé pour compléter la map.
*/

#pragma once
#include <vector>
#include <cassert>
using namespace std;

// Structure des cases comprises dans une pièces.
struct section
{
	int x = 0;
	int y = 0;
	char code[3] = "\0";
	bool verifie = false;

	section(char id)
	{

		code[0] = id;
	}
	section(char id, char tuile)
	{
		code[0] = id;
		code[1] = tuile;
	}
};

// Objet pièce du jeu de base.
class piece
{
protected:
	int _x = 0;
	int _y = 0;
	int _no = 0;	// 
	int _rotation1 = false;
	vector<section> _tuile;

public:
	piece();	// 
	piece(char id)
	{
		// assert(!iswspace(is));
		section tuile(id);
		_tuile.push_back(tuile);
	}
	~piece();	// 

};

// 
class piece2cases : private piece
{
private:
	int _rotation2 = false;	//

public:
	piece2cases();	//
	piece2cases(char id, char t1, char t2)
	{
		// assert(!iswspace(is) | !iswspace(t1) | !iswspace(t2));
		section tuile1(id, t1), tuile2(id, t2);
		_tuile.push_back(tuile1);
		_tuile.push_back(tuile2);
	}
	~piece2cases();	// 

};

// 
class piece3cases : private piece
{
private:
	bool rotation2 = false;	// 

public:
	piece3cases();	// 
	piece3cases(char id, char tuile1, char tuile2, char tuile3)
	{

	}
	~piece3cases();	// 

};


///========///
// MÉTHODES //
///========///

// piece
///=====
// 
piece::piece()
{
}
// 
piece::~piece()
{
}

// piece2cases
///===========
// 
piece2cases::piece2cases()
{
}
// 
piece2cases::~piece2cases()
{
}


// piece3cases
///===========
// 
piece3cases::piece3cases()
{
}
// 
piece3cases::~piece3cases()
{
}
