/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
// Ficher:	map.cpp
// But:		Objet du jeu utilisé pour compléter la map.
*/

#pragma once
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


// Constantes de la map (à déplacer)
const int LARGEUR_MAP = 4;
const int HAUTEUR_MAP = 4;
// Largeur \ hauteur de la map (peut être mis en paramêtre caché si les pièces font parti de la map)



// Structure de tuile des pièces.
struct section
{
public:
	char _code = '\0';		// Code qui identifie la tuile dans le jeu
	bool _valide = false;	// Variable pour s'assurer que la tuile est adéquate

	section() {}					// Initialisateur par défaut
	section(char code)				// Initialiseur
	{
		_code = toupper(code);
		if (code != '\0')
			_valide = true;
		else
			_valide = false;
	}
	section(const section & t)		// Copieur
	{
		_code = t._code;
		_valide = t._valide;
	}
	const section * operator=
		(section & t)				// Copieur par l'opérateur =
	{
		return new section(t);	// Bug: mauvaise opération pour copier ?
	}
	~section()						// Destructeur
	{
		_code = '\0';
		_valide = 0;
	}
};



// Objet parent des pièces du jeu de base.
class piece
{
protected:
	char _nom = '\0';			// Caractère qui représente la pièce
	int _angle = 0;				// Angle de la pièce dans la map
	section _tuile[2][2];		// Éléments formant la pièce

	void initTuile				// Initialise le nombre de tuile nécessaire pour la pièce
	(const char * t, const int NB_TUILE);
	virtual void pivote() = 0;	// Effectue les modifications principale avant les rotations

public:
	virtual piece * create		// Initialisateur par virtualisation
	(const char & nom, const char * t);
	piece();					// Initialisateur par défaut
	piece(const char & nom, const char * t);

	virtual piece *				// Copieur héréditaire
		piece::clone() = 0;
	piece & operator=			// Copieur par l'opérateur =
		(const piece & p);

	virtual ~piece() = default;	// Destructeur

	virtual void tourneDroite() = 0;// Fait pivoter la pièce sur elle-même dans le sens horaire

	/// Setteur
	void setNom(char nom);		// Change le caractère qui représente la pièce
	virtual void setTuile		// Change le contenu des tuiles de la pièce
	(const char * t);

	char getNom() const;		// Retourne le caractère qui représente la pièce
	section getTuile(int i, int j) const;	// Retourne une des tuile de la pièce

	void print(ostream & sortie) const;	// Affiche le contenu de toutes les tuiles de la pièce
};




// Pièces formées de 2 tuiles.
class piece2cases : public piece
{
private:
	const int NB_TUILE = 2;	// Nombre de tuiles des objets pieces2cases.

	void pivote() {}		// 

public:
	piece2cases * create	// Initialisateur permettant la surcharge de paramètres
	(const char & nom, const char * t);
	piece2cases
	(const char & nom, const char * t);	// Initialisateur

	piece2cases * clone();	// Copieur héréditaire

	~piece2cases();			// Destructeur

	void setTuile(const char * t);	// Change le nombre de tuile nécessaire de la pièce

	void tourneDroite();	// Fait pivoter la pièce sur elle-même dans le sens horaire
};

// Pièces formées de 3 tuiles.
class piece3cases : private piece
{
private:
	const int NB_TUILE = 3;	// Nombre de tuiles des objets pieces3cases.

	void pivote();			// Effectue les modifications principale avant les rotations

public:
	piece3cases * create	// Initialisateur permettant la surcharge de paramètres
	(const char & nom, const char * t);
	piece3cases
	(const char & nom, const char * t);	// Initialisateur

	piece3cases * clone();	// Copieur héréditaire

	~piece3cases();			// Destructeur

	void setTuile(const char * t);

	void tourneDroite();	// Fait pivoter la pièce sur elle-même dans le sens horaire
};




///===============///
// AUTRES MÉTHODES //
///===============///
ostream & operator<<(ostream & sortie, piece & p);