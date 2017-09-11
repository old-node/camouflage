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
	int _x = 0;				// Coordon�e horizontale de la tuile dans la pi�ce
	int _y = 0;				// Coordon�e verticale de la tuile dans la pi�ce
	char _code = '\0';	// Code qui identifie la tuile dans le jeu
	bool _valide = false;	// Variable pour s'assurer que la tuile est ad�quate

	section() {}
	section(int x, int y, char code)	// Initialiseur
	{
		_x = x;
		_y = y;
		_code = toupper(code);
		if (code != '\0')
			_valide = true;
		else
			_valide = false;
	}
	section(const section & s)		// Copieur
	{
		_x = s._x;
		_y = s._y;
		_code = s._code;
		_valide = s._valide;
	}
	const section & operator=
		(const section & s)			// Copieur par l'op�rateur =
	{
		section c(s);
		return c;
	}
	~section()						// Destructeur
	{
		_x = _y = _valide = 0;
		_code = '\0';
	}
};


//struct base {
//	virtual base * clone() const = 0;
//	virtual ~base() {}
//};
//struct derivation : base {
//	virtual derivation * clone() const { return new derivation(*this); }
//};

// Affiche le code d'une section avec l�op�rateur <<.
ostream & operator<<(ostream & sortie, const section & s)
{
	return sortie << s._code;
}
// Affiche le code d'une section avec l�op�rateur <<.
ostream & operator<<(ostream & sortie, const vector<section> & t)
{
	for (auto tuile : t)
		sortie << tuile << " ";
	return sortie;
}


// Objet parent des pi�ces du jeu de base.
class piece
{
protected:
	char _nom = '\0';
	int _x = 0;				// Coordonn�e horizontale de la pi�ce dans la map
	int _y = 0;				// Coordonn�e verticale de la pi�ce dans la map
	int _angle = 0;			// Angle de la pi�ce dans la map
	vector<section> _tuile;	// �l�ments formant la pi�ce

public:
	virtual piece * create			// Initialisateur permettant la surcharge de param�tres
	(const char & nom, const char * t) = 0;
	piece() {
		create('T', "_");
	}
	piece(const char & nom, const char * t)
	{
		create(nom, t);
	}

	virtual piece * clone() const = 0;	// Copieur h�r�ditaire
	piece(const piece & p)			// Copieur
	{
		_nom = p.getNom();
		_x = p.getX();
		_y = p.getY();
		_angle = p.getAngle();
		_tuile = p.getTuile();
	}
	piece & operator=(const piece & p)	// Copieur par l'op�rateur =
	{
		return *this->clone();
	}

	virtual ~piece() = default;		// Destructeur	*/*

	/// * Analyse
	virtual void depose(int x, int y, int angle) = 0;// Positionne la pi�ce aux coordon�es et � l'angle souhait�
	virtual void deplace() = 0;		// Itt�re vers la prochaine position que la pi�ce peut prendre dans la map

	/// Manipulation de la pi�ce dans la map
	virtual void ajoute() = 0;		// D�bute le positionnement manuel
	virtual void retire() = 0;		// Termine le positionnement manuel
	virtual void place() = 0;		// Fixe la pi�ce � son endroit �tabli 
	void bougeGauche()				// ** D�place la pi�ce vers la gauche dans la map
	{
		setX(_x - 1);
	}
	virtual void bougeDroite() = 0;	// * D�place la pi�ce vers la droite dans la map
	void bougeHaut()				// ** D�place la pi�ce vers le haut dans la map
	{
		setY(_y - 1);
	}
	virtual void bougeBas() = 0;	// * D�place la pi�ce vers le bas dans la map
	virtual void tourneGauche() = 0;// Fait pivoter la pi�ce sur elle-m�me dans le sens anti-horaire
	virtual void tourneDroite() = 0;// * Fait pivoter la pi�ce sur elle-m�me dans le sens horaire

	/// Setteur
	void setNom(char nom) { _nom = nom; }
	void setX(int x)				// Positionne la pi�ce � une coordonn�e horizontale
	{
		assert(x >= 0);
		_x = x;
	}
	void setY(int y)				// Positionne la pi�ce � une coordonn�e verticale
	{
		assert(y >= 0);
		_y = y;
	}
	void setAngle(int angle)		// Change l'angle de la pi�ce
	{
		assert(angle >= 0 && angle <= 4);
		_angle = angle;
	}
	void setTuile(vector<section> tuile)
	{
		_tuile.resize(0);
		for (auto & t : tuile)
			_tuile.push_back(t);
	}

	/// Getteur
	virtual bool aPosition(int x, int y) const = 0;	// V�rifie si l'une des tuile est plac� aux coordonn�es cibl�es
	char getNom() const { return _nom; }	// Retourne le caract�re qui repr�sente la pi�ce
	int getX() const { return _x; }			// Retourne la coordonn�e horizontale de la pi�ce dans la map
	int getY() const { return _y; }			// Retourne la coordonn�e verticale de la pi�ce dans la map
	int getAngle() const { return _angle; }// Retourne l'angle de la pi�ce (de 1 � 4)
	virtual bool compatible() const = 0;	// Retourne si la pi�ce peut �tre d�pos� � son endroit
	const vector<section> getTuile() const	// Retourne toutes les tuiles de la pi�ce
	{
		return _tuile;
	}

	/// virtual bool p() const = 0;		// 

	void print(int noTuile) const	// Affiche le contenu de toutes les tuiles de la pi�ce
	{
		for (auto & tuile : _tuile)
			cout << tuile << " ";
	}
};


// Affiche le code d'une section avec l�op�rateur <<.
ostream & operator<<(ostream & sortie, const piece & p)
{
	return sortie << p.getTuile();
}


// Pi�ces form�es de 2 tuiles.
class piece2cases : public piece
{
private:
	const int NB_TUILE = 2;	//

public:
	piece2cases(const char & nom, const char * t)
	{
		create(nom, t);
	}
	piece2cases * create					// Initialisateur permettant la surcharge de param�tres
	(const char & nom, const char * t)
	{
		assert(!isspace(nom));
		setNom(nom);
		vector<section> tuile;
		for (int i = 0; i < NB_TUILE; i++)
		{
			assert(!iswspace(t[0]));
			section t(i, 0, t[i]);
			_tuile.push_back(t);
		}
		setTuile(tuile);
		return this;
	}

	piece2cases * clone() const				// Copieur h�r�ditaire
	{
		return new piece2cases(*this);
	}
	~piece2cases() { delete this; }			// Destructeur

	/// Analyse
	void depose(int x, int y, int angle)	// Positionne la pi�ce aux coordon�es et � l'angle souhait�
	{
		setX(x);
		setY(y);
		setAngle(angle);
	}
	void deplace()		// Itt�re vers la prochaine position que la pi�ce peut prendre dans la map
	{

	}

	/// Manipulation de la pi�ce dans la map
	void ajoute()		// D�bute le positionnement manuel
	{

	}
	void retire()		// Termine le positionnement manuel
	{

	}
	void place()		// Fixe la pi�ce � son endroit �tabli 
	{

	}
	void bougeDroite()	// * D�place la pi�ce vers la droite dans la map
	{
		setX(_x + 1);
	}
	void bougeBas()		// * D�place la pi�ce vers le bas dans la map
	{
		setY(_y + 1);
	}
	void tourneGauche()	// Fait pivoter la pi�ce sur elle-m�me dans le sens anti-horaire
	{
		if (_angle == 0)
			_angle = 4;
		else
			_angle--;

		if (_angle % 2 == 0)
		{
			_tuile[1]._x--;
			_tuile[0]._y++;
		}
		else
		{
			_tuile[1]._x++;
			_tuile[0]._y--;
		}
	}
	void tourneDroite()	// * Fait pivoter la pi�ce sur elle-m�me dans le sens horaire
	{
		if (_angle == 4)
			_angle = 0;
		else
			_angle++;

		if (_angle % 2 == 0)
		{
			_tuile[1]._x--;
			_tuile[0]._y++;
		}
		else
		{
			_tuile[1]._x++;
			_tuile[0]._y--;
		}
	}

	void setX(int x)
	{
		piece::setX(x);
		assert(x <= LARGEUR_MAP - (_angle % 2) ? 0 : 1);
		_x = x;
	}
	void setY(int y)
	{
		piece::setY(y);
		assert(y <= HAUTEUR_MAP - (_angle % 2) ? 1 : 0);
		_y = y;
	}
	void setAngle(int angle)
	{
		piece::setAngle(angle);
		//if ()
		//	_angle = angle;
	}

	/// Getteur
	bool aPosition(int x, int y) const	// V�rifie si l'une des tuile est plac� aux coordonn�es cibl�es
	{
		return 0;
	}
	bool compatible() const	// Retourne si la pi�ce peut �tre d�pos� � son endroit
	{
		return 0;
	}

};

// Pi�ces form�es de 3 tuiles.
class piece3cases : private piece
{
private:
	;	// 

public:
	//piece3cases(const char & id, const char & t1, const char & t2, const char & t3)	// Initialisateur
	//{
	//	assert(!isspace(id) | !iswspace(t1) | !iswspace(t2) | !iswspace(t3));
	//	section tuile1(id, t1), tuile2(id, t2), tuile3(id, t3);
	//	_tuile.push_back(tuile1);
	//	_tuile.push_back(tuile2);
	//	_tuile.push_back(tuile3);
	//}
	~piece3cases() { delete this; }	// Destructeur

};


///========///
// M�THODES //
///========///

// piece
///=====
// 


// piece2cases
///===========
// 

// 



// piece3cases
///===========
// 

// 

