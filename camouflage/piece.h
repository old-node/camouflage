/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 ao�t 2017
// Ficher:	map.cpp
// But:		Objet du jeu utilis� pour compl�ter la map.
*/

#pragma once
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


// Constantes de la map (� d�placer)
const int LARGEUR_MAP = 4;
const int HAUTEUR_MAP = 4;
// Largeur \ hauteur de la map (peut �tre mis en param�tre cach� si les pi�ces font parti de la map)



// Structure de tuile des pi�ces.
struct section
{
public:
	char _code = '\0';		// Code qui identifie la tuile dans le jeu
	bool _valide = false;	// Variable pour s'assurer que la tuile est ad�quate

	section() {}					// Initialisateur par d�faut
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
		(section & t)				// Copieur par l'op�rateur =
	{
		return new section(t);	// Bug: mauvaise op�ration pour copier ?
	}
	~section()						// Destructeur
	{
		_code = '\0';
		_valide = 0;
	}
};



// Objet parent des pi�ces du jeu de base.
class piece
{
protected:
	char _nom = '\0';			// Caract�re qui repr�sente la pi�ce
	int _angle = 0;				// Angle de la pi�ce dans la map
	section _tuile[2][2];		// �l�ments formant la pi�ce

	void initTuile				// Initialise le nombre de tuile n�cessaire pour la pi�ce
	(const char * t, const int NB_TUILE);
	virtual void pivote() = 0;	// Effectue les modifications principale avant les rotations

public:
	virtual piece * create		// Initialisateur par virtualisation
	(const char & nom, const char * t);
	piece();					// Initialisateur par d�faut
	piece(const char & nom, const char * t);

	virtual piece *				// Copieur h�r�ditaire
		piece::clone() = 0;
	piece & operator=			// Copieur par l'op�rateur =
		(const piece & p);

	virtual ~piece() = default;	// Destructeur

	virtual void tourneDroite() = 0;// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire

	/// Setteur
	void setNom(char nom);		// Change le caract�re qui repr�sente la pi�ce
	virtual void setTuile		// Change le contenu des tuiles de la pi�ce
	(const char * t);

	char getNom() const;		// Retourne le caract�re qui repr�sente la pi�ce
	section getTuile(int i, int j) const;	// Retourne une des tuile de la pi�ce

	void print(ostream & sortie) const;	// Affiche le contenu de toutes les tuiles de la pi�ce
};




// Pi�ces form�es de 2 tuiles.
class piece2cases : public piece
{
private:
	const int NB_TUILE = 2;	// Nombre de tuiles des objets pieces2cases.

	void pivote() {}		// 

public:
	piece2cases * create	// Initialisateur permettant la surcharge de param�tres
	(const char & nom, const char * t);
	piece2cases
	(const char & nom, const char * t);	// Initialisateur

	piece2cases * clone();	// Copieur h�r�ditaire

	~piece2cases();			// Destructeur

	void setTuile(const char * t);	// Change le nombre de tuile n�cessaire de la pi�ce

	void tourneDroite();	// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire
};

// Pi�ces form�es de 3 tuiles.
class piece3cases : private piece
{
private:
	const int NB_TUILE = 3;	// Nombre de tuiles des objets pieces3cases.

	void pivote();			// Effectue les modifications principale avant les rotations

public:
	piece3cases * create	// Initialisateur permettant la surcharge de param�tres
	(const char & nom, const char * t);
	piece3cases
	(const char & nom, const char * t);	// Initialisateur

	piece3cases * clone();	// Copieur h�r�ditaire

	~piece3cases();			// Destructeur

	void setTuile(const char * t);

	void tourneDroite();	// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire
};




///===============///
// AUTRES M�THODES //
///===============///
ostream & operator<<(ostream & sortie, piece & p);