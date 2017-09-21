/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
// Ficher:	piece.h
// But:		Objets du jeu utilisé pour compléter la map.
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


// Structure de tuile des pièces.
struct section
{
public:
	char _code = '\0';		// Code qui identifie la tuile dans le jeu
	bool _valide = false;	// Variable pour s'assurer que la tuile est adéquate

	section() {}			// Initialisateur par défaut
	section(char code)		// Initialiseur
	{
		_code = toupper(code);
		if (code != '\0')
			_valide = true;
		else
			_valide = false;
	}
};


// Objet parent des pièces du jeu de base.
class piece
{
protected:
	int _nbTuile = 0;				// Nombre de tuiles présentes dans la pièce.
	char _nom = '\0';				// Caractère qui représente la pièce.
	section _tuile[2][2];			// Éléments formant la pièce.
	
	void initTuile(const char * t);	// Initialise le nombre de tuile nécessaire pour la pièce
	virtual void pivote() = 0;		// Effectue les modifications principale avant les rotations

public:
	virtual piece * create(const char & nom, const char * t); // Initialisateur par virtualisation
	piece();						// Initialisateur par défaut
	piece(const char & nom, const char * t);
	virtual piece *	piece::clone() = 0;		// Copieur héréditaire
	
	virtual ~piece() = default;		// Destructeur

	
	// Setteur
	void setNom(char nom);			// Change le caractère qui représente la pièce
	virtual void tourne() = 0;		// Fait pivoter la pièce sur elle-même dans le sens horaire

	// Getteurs
	char getNom() const;			// Retourne le caractère qui représente la pièce
	int getNbTuile() const;			// Obtient le nombre de tuiles de la pièce
	char getTuile(int i, int j) const;		// Retourne une des tuile de la pièce
	
	void print(ostream & sortie) const;		// Affiche le contenu de toutes les tuiles de la pièce
};



// Pièces formées de 2 tuiles.
class piece2cases : virtual public piece
{
private:
	bool _angle = false;			//

	void pivote() override {}		// 

public:
	// Initialisateur permettant la surcharge de paramètres
	piece2cases * create(const char & nom, const char * t) override;
	piece2cases(const char & nom, const char * t);	// Initialisateur
	piece2cases * clone() override;	// Copieur héréditaire

	~piece2cases() override;		// Destructeur

	bool getAngle() const;			

	void tourne() override;	// Fait pivoter la pièce sur elle-même dans le sens horaire
};

// Pièces formées de 3 tuiles.
class piece3cases : virtual public piece
{
private:
	void pivote() override;			// Effectue les modifications principale avant les rotations

public:
	// Initialisateur permettant la surcharge de paramètres
	piece3cases * create(const char & nom, const char * t) override;
	piece3cases	(const char & nom, const char * t);	// Initialisateur
	piece3cases * clone() override;	// Copieur héréditaire

	~piece3cases() override;		// Destructeur

	void tourne() override;	// Fait pivoter la pièce sur elle-même dans le sens horaire
};




///===============///
// AUTRES MÉTHODES //
///===============///
ostream & operator<<(ostream & sortie, const piece & p);
