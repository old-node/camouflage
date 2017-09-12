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
const int NB_CHAR_CODE = 3;
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
	const section & operator=
		(section & t)				// Copieur par l'opérateur =
	{
		return *(new section(t));	// Bug: mauvaise opération pour copier ?
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

	/// * Analyse
	//virtual void depose(int x, int y, int angle) = 0;// Positionne la pièce aux coordonées et à l'angle souhaité
	//virtual void deplace() = 0;		// Ittère vers la prochaine position que la pièce peut prendre dans la map

	/// Manipulation de la pièce dans la map
	//virtual void ajoute() = 0;		// Débute le positionnement manuel
	//virtual void retire() = 0;		// Termine le positionnement manuel
	//virtual void place() = 0;		// Fixe la pièce à son endroit établi 
	//void bougeGauche()				// ** Déplace la pièce vers la gauche dans la map
	//{
	//	setX(_x - 1);
	//}
	//virtual void bougeDroite() = 0;	// * Déplace la pièce vers la droite dans la map
	//void bougeHaut()				// ** Déplace la pièce vers le haut dans la map
	//{
	//	setY(_y - 1);
	//}
	//virtual void bougeBas() = 0;	// * Déplace la pièce vers le bas dans la map

	virtual void tourneGauche() = 0;// Fait pivoter la pièce sur elle-même dans le sens anti-horaire
	virtual void tourneDroite() = 0;// Fait pivoter la pièce sur elle-même dans le sens horaire


	/// Setteur
	void setNom(char nom);		// Change le caractère qui représente la pièce
	//void setX(int x)			// Positionne la pièce à une coordonnée horizontale
	//{
	//	assert(x >= 0);
	//	_x = x;
	//}
	//void setY(int y)			// Positionne la pièce à une coordonnée verticale
	//{
	//	assert(y >= 0);
	//	_y = y;
	//}
	//void setAngle(int angle)	// Change l'angle de la pièce
	//{
	//	assert(angle >= 0 && angle <= 4);
	//	_angle = angle;
	//

	virtual void setTuile		// Change le contenu des tuiles de la pièce
	(const char * t);

	/// Getteur
	//virtual bool aPosition	// Vérifie si l'une des tuile est placé aux coordonnées ciblées
	//	(int x, int y) const = 0;
	char getNom() const;		// Retourne le caractère qui représente la pièce
	//int getX() const { return _x; }		// Retourne la coordonnée horizontale de la pièce dans la map
	//int getY() const { return _y; }		// Retourne la coordonnée verticale de la pièce dans la map
	//int getAngle() const { return _angle; }// Retourne l'angle de la pièce (de 1 à 4)
	//virtual bool compatible() const = 0;	// Retourne si la pièce peut être déposé à son endroit
	section getTuile(int i, int j) const;	// Retourne une des tuile de la pièce

	/// virtual bool p() const = 0;	// 

	void print(ostream & sortie) const;	// Affiche le contenu de toutes les tuiles de la pièce
};




// Pièces formées de 2 tuiles.
class piece2cases : public piece
{
private:
	const int NB_TUILE = 2;	// Nombre de tuiles des objets pieces2cases.

	void pivote() {}

public:
	piece2cases * create	// Initialisateur permettant la surcharge de paramètres
	(const char & nom, const char * t);
	piece2cases
	(const char & nom, const char * t);	// Initialisateur

	piece2cases * clone();	// Copieur héréditaire

	~piece2cases();			// Destructeur

	/// Analyse
	//void depose(int x, int y, int angle)	// Positionne la pièce aux coordonées et à l'angle souhaité
	//{
	//	setX(x);
	//	setY(y);
	//	setAngle(angle);
	//}
	//void deplace()		// Ittère vers la prochaine position que la pièce peut prendre dans la map
	//{
	//}

	///// Manipulation de la pièce dans la map
	//void ajoute()		// Débute le positionnement manuel
	//{
	//}
	//void retire()		// Termine le positionnement manuel
	//{
	//}
	//void place()		// Fixe la pièce à son endroit établi 
	//{
	//}
	//void bougeDroite()	// * Déplace la pièce vers la droite dans la map
	//{
	//	setX(_x + 1);
	//}
	//void bougeBas()		// * Déplace la pièce vers le bas dans la map
	//{
	//	setY(_y + 1);
	//}

	//void setX(int x)
	//{
	//	piece::setX(x);
	//	assert(x <= LARGEUR_MAP - (_angle % 2) ? 0 : 1);
	//	_x = x;
	//}
	//void setY(int y)
	//{
	//	piece::setY(y);
	//	assert(y <= HAUTEUR_MAP - (_angle % 2) ? 1 : 0);
	//	_y = y;
	//}
	//void setAngle(int angle)
	//{
	//	piece::setAngle(angle);
	//	//if ()
	//	//	_angle = angle;
	//}
	void setTuile(const char * t);	// Change le nombre de tuile nécessaire de la pièce

	void tourneGauche();	// Fait pivoter la pièce sur elle-même dans le sens anti-horaire
	void tourneDroite();	// Fait pivoter la pièce sur elle-même dans le sens horaire

	/// Getteur
	//bool aPosition(int x, int y) const	// Vérifie si l'une des tuile est placé aux coordonnées ciblées
	//{
	//	return 0;
	//}
	//bool compatible() const	// Retourne si la pièce peut être déposé à son endroit
	//{
	//	return 0;
	//}

};

// Pièces formées de 3 tuiles.
class piece3cases : private piece
{
private:
	const int NB_TUILE = 3;	// Nombre de tuiles des objets pieces3cases.

	void pivote();			// Effectue les modifications principale avant les rotations

public:
	//piece3cases(const char & id, const char & t1, const char & t2, const char & t3)	// Initialisateur
	//{
	//	assert(!isspace(id) | !iswspace(t1) | !iswspace(t2) | !iswspace(t3));
	//	section tuile1(id, t1), tuile2(id, t2), tuile3(id, t3);
	//	_tuile.push_back(tuile1);
	//	_tuile.push_back(tuile2);
	//	_tuile.push_back(tuile3);
	//}
	piece3cases * clone();	// Copieur héréditaire

	~piece3cases() { delete this; }	// Destructeur


	void tourneGauche();	// Fait pivoter la pièce sur elle-même dans le sens anti-horaire
	void tourneDroite();	// Fait pivoter la pièce sur elle-même dans le sens horaire
};


///===============///
// AUTRES MÉTHODES //
///===============///
