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
const int NB_CHAR_CODE = 3;
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
	const section & operator=
		(section & t)				// Copieur par l'op�rateur =
	{
		return *(new section(t));	// Bug: mauvaise op�ration pour copier ?
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

	/// * Analyse
	//virtual void depose(int x, int y, int angle) = 0;// Positionne la pi�ce aux coordon�es et � l'angle souhait�
	//virtual void deplace() = 0;		// Itt�re vers la prochaine position que la pi�ce peut prendre dans la map

	/// Manipulation de la pi�ce dans la map
	//virtual void ajoute() = 0;		// D�bute le positionnement manuel
	//virtual void retire() = 0;		// Termine le positionnement manuel
	//virtual void place() = 0;		// Fixe la pi�ce � son endroit �tabli 
	//void bougeGauche()				// ** D�place la pi�ce vers la gauche dans la map
	//{
	//	setX(_x - 1);
	//}
	//virtual void bougeDroite() = 0;	// * D�place la pi�ce vers la droite dans la map
	//void bougeHaut()				// ** D�place la pi�ce vers le haut dans la map
	//{
	//	setY(_y - 1);
	//}
	//virtual void bougeBas() = 0;	// * D�place la pi�ce vers le bas dans la map

	virtual void tourneGauche() = 0;// Fait pivoter la pi�ce sur elle-m�me dans le sens anti-horaire
	virtual void tourneDroite() = 0;// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire


	/// Setteur
	void setNom(char nom);		// Change le caract�re qui repr�sente la pi�ce
	//void setX(int x)			// Positionne la pi�ce � une coordonn�e horizontale
	//{
	//	assert(x >= 0);
	//	_x = x;
	//}
	//void setY(int y)			// Positionne la pi�ce � une coordonn�e verticale
	//{
	//	assert(y >= 0);
	//	_y = y;
	//}
	//void setAngle(int angle)	// Change l'angle de la pi�ce
	//{
	//	assert(angle >= 0 && angle <= 4);
	//	_angle = angle;
	//

	virtual void setTuile		// Change le contenu des tuiles de la pi�ce
	(const char * t);

	/// Getteur
	//virtual bool aPosition	// V�rifie si l'une des tuile est plac� aux coordonn�es cibl�es
	//	(int x, int y) const = 0;
	char getNom() const;		// Retourne le caract�re qui repr�sente la pi�ce
	//int getX() const { return _x; }		// Retourne la coordonn�e horizontale de la pi�ce dans la map
	//int getY() const { return _y; }		// Retourne la coordonn�e verticale de la pi�ce dans la map
	//int getAngle() const { return _angle; }// Retourne l'angle de la pi�ce (de 1 � 4)
	//virtual bool compatible() const = 0;	// Retourne si la pi�ce peut �tre d�pos� � son endroit
	section getTuile(int i, int j) const;	// Retourne une des tuile de la pi�ce

	/// virtual bool p() const = 0;	// 

	void print(ostream & sortie) const;	// Affiche le contenu de toutes les tuiles de la pi�ce
};




// Pi�ces form�es de 2 tuiles.
class piece2cases : public piece
{
private:
	const int NB_TUILE = 2;	// Nombre de tuiles des objets pieces2cases.

	void pivote() {}

public:
	piece2cases * create	// Initialisateur permettant la surcharge de param�tres
	(const char & nom, const char * t);
	piece2cases
	(const char & nom, const char * t);	// Initialisateur

	piece2cases * clone();	// Copieur h�r�ditaire

	~piece2cases();			// Destructeur

	/// Analyse
	//void depose(int x, int y, int angle)	// Positionne la pi�ce aux coordon�es et � l'angle souhait�
	//{
	//	setX(x);
	//	setY(y);
	//	setAngle(angle);
	//}
	//void deplace()		// Itt�re vers la prochaine position que la pi�ce peut prendre dans la map
	//{
	//}

	///// Manipulation de la pi�ce dans la map
	//void ajoute()		// D�bute le positionnement manuel
	//{
	//}
	//void retire()		// Termine le positionnement manuel
	//{
	//}
	//void place()		// Fixe la pi�ce � son endroit �tabli 
	//{
	//}
	//void bougeDroite()	// * D�place la pi�ce vers la droite dans la map
	//{
	//	setX(_x + 1);
	//}
	//void bougeBas()		// * D�place la pi�ce vers le bas dans la map
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
	void setTuile(const char * t);	// Change le nombre de tuile n�cessaire de la pi�ce

	void tourneGauche();	// Fait pivoter la pi�ce sur elle-m�me dans le sens anti-horaire
	void tourneDroite();	// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire

	/// Getteur
	//bool aPosition(int x, int y) const	// V�rifie si l'une des tuile est plac� aux coordonn�es cibl�es
	//{
	//	return 0;
	//}
	//bool compatible() const	// Retourne si la pi�ce peut �tre d�pos� � son endroit
	//{
	//	return 0;
	//}

};

// Pi�ces form�es de 3 tuiles.
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
	piece3cases * clone();	// Copieur h�r�ditaire

	~piece3cases() { delete this; }	// Destructeur


	void tourneGauche();	// Fait pivoter la pi�ce sur elle-m�me dans le sens anti-horaire
	void tourneDroite();	// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire
};


///===============///
// AUTRES M�THODES //
///===============///
