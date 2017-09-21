/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 ao�t 2017
// Ficher:	piece.h
// But:		Objets du jeu utilis� pour compl�ter la map.
*/

#pragma once
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


// Constantes de la map
const int LARGEUR_MAP = 4;
const int HAUTEUR_MAP = 4;
// Largeur \ hauteur de la map


// Structure de tuile des pi�ces.
struct section
{
public:
	char _code = '\0';		// Code qui identifie la tuile dans le jeu
	bool _valide = false;	// Variable pour s'assurer que la tuile est ad�quate

	section() {}			// Initialisateur par d�faut
	section(char code)		// Initialiseur
	{
		_code = toupper(code);
		if (code != '\0')
			_valide = true;
		else
			_valide = false;
	}
};


// Objet parent des pi�ces du jeu de base.
class piece
{
protected:
	int _nbTuile = 0;				// Nombre de tuiles pr�sentes dans la pi�ce.
	char _nom = '\0';				// Caract�re qui repr�sente la pi�ce.
	section _tuile[2][2];			// �l�ments formant la pi�ce.
	
	void initTuile(const char * t);	// Initialise le nombre de tuile n�cessaire pour la pi�ce
	virtual void pivote() = 0;		// Effectue les modifications principale avant les rotations

public:
	virtual piece * create(const char & nom, const char * t); // Initialisateur par virtualisation
	piece();						// Initialisateur par d�faut
	piece(const char & nom, const char * t);
	virtual piece *	piece::clone() = 0;		// Copieur h�r�ditaire
	
	virtual ~piece() = default;		// Destructeur

	
	// Setteur
	void setNom(char nom);			// Change le caract�re qui repr�sente la pi�ce
	virtual void tourne() = 0;		// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire

	// Getteurs
	char getNom() const;			// Retourne le caract�re qui repr�sente la pi�ce
	int getNbTuile() const;			// Obtient le nombre de tuiles de la pi�ce
	char getTuile(int i, int j) const;		// Retourne une des tuile de la pi�ce
	
	void print(ostream & sortie) const;		// Affiche le contenu de toutes les tuiles de la pi�ce
};



// Pi�ces form�es de 2 tuiles.
class piece2cases : virtual public piece
{
private:
	bool _angle = false;			//

	void pivote() override {}		// 

public:
	// Initialisateur permettant la surcharge de param�tres
	piece2cases * create(const char & nom, const char * t) override;
	piece2cases(const char & nom, const char * t);	// Initialisateur
	piece2cases * clone() override;	// Copieur h�r�ditaire

	~piece2cases() override;		// Destructeur

	bool getAngle() const;			

	void tourne() override;	// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire
};

// Pi�ces form�es de 3 tuiles.
class piece3cases : virtual public piece
{
private:
	void pivote() override;			// Effectue les modifications principale avant les rotations

public:
	// Initialisateur permettant la surcharge de param�tres
	piece3cases * create(const char & nom, const char * t) override;
	piece3cases	(const char & nom, const char * t);	// Initialisateur
	piece3cases * clone() override;	// Copieur h�r�ditaire

	~piece3cases() override;		// Destructeur

	void tourne() override;	// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire
};




///===============///
// AUTRES M�THODES //
///===============///
ostream & operator<<(ostream & sortie, const piece & p);
