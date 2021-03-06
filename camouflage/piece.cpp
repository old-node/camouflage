/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 ao�t 2017
// Ficher:	piece.cpp
*/

#include "piece.h"

// Permet l'�criture des pi�ces avec l'op�rater <<
ostream & operator<<(ostream & sortie, const piece & p)
{
	p.print(sortie);
	return sortie;
}

///===== */
/* PIECE */
///===== */

// Initialisateur par virtualisation
piece * piece::create(const char & nom, const char * t)
{
	setNom(nom);
	initTuile(t);
	return this;
}
// Initialisateur par d�faut
piece::piece()
{
	create('T', "_");
}
// Initialisateur
piece::piece(const char & nom, const char * t)
{
	create(nom, t);
}
// Initialise le nombre de tuile n�cessaire pour la pi�ce
void piece::initTuile(const char * t)
{
	int pos = 0;					// Position du caract�re � ajouter dans la tuile

	for (int i = 0; i < 2; i++)		// Pour toute la matrice
	{
		for (int j = 0; j < 2; j++)
		{
			if (pos < _nbTuile)		// Rempli la tuile selon le caract�re de la chaine
			{	// Si un mauvais type de caract�re est pr�sent
				assert(!iswspace(t[i]) | t[i] == ' ');
				_tuile[i][j]._code = t[pos];
				_tuile[i][j]._valide = true;
			}
			else
			{
				_tuile[i][j]._code = '\0';
				_tuile[i][j]._valide = false;
			}

			pos++;
		}
	}
}

// Change le caract�re qui repr�sente la pi�ce
void piece::setNom(char nom)
{
	assert(!isspace(nom));
	_nom = nom;
}

// Retourne le caract�re qui repr�sente la pi�ce
char piece::getNom() const
{
	return _nom;
}
// Obtient le nombre de tuiles de la pi�ce
int piece::getNbTuile() const
{
	return _nbTuile;
}
// Retourne une des tuile de la pi�ce
char piece::getTuile(int i, int j) const
{
	assert(i >= 0 && i < 2 && j >= 0 && j < 2);
	return _tuile[i][j]._code;
}

// Affiche le contenu de toutes les tuiles de la pi�ce
void piece::print(ostream & sortie) const
{
	for (int i = 0; i < 2; i++)		// Pour la matrice au complet
	{
		for (int j = 0; j < 2; j++)
		{
			if (_tuile[i][j]._valide)
				// Affiche le contenu de la tuile avec le nom de la pi�ce
				sortie << _nom << _tuile[i][j]._code << " ";
			else
				// Remplace les tuiles invalide par des espaces
				sortie << "   ";
		}
		sortie << endl;
	}
	sortie << endl;
}


///============= */
/* PIECE 2 CASES */
///============= */

// Initialisateur permettant la surcharge de param�tres
piece2cases * piece2cases::create(const char & nom, const char * t)
{
	_nbTuile = 2;
	_angle = true;
	setNom(nom);
	initTuile(t);
	return this;
}
// Initialisateur
piece2cases::piece2cases(const char & nom, const char * t)
{
	create(nom, t);
}

// Copieur h�r�ditaire
piece2cases * piece2cases::clone()
{
	return new piece2cases(*this);
}

// Destructeur
piece2cases::~piece2cases()
{
	_angle = false;
	piece::~piece();
}

bool piece2cases::getAngle() const
{
	return _angle;
}

// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire
void piece2cases::tourne()
{
	if (_angle)				// D�placement simple de l'extr�mit� de la pi�ce
	{
		_angle = false;
		swap(_tuile[0][1]._code, _tuile[1][0]._code);
		swap(_tuile[0][1]._valide, _tuile[1][0]._valide);
	}
	else					// Rotation compl�te normale
	{
		_angle = true;
		swap(_tuile[0][0]._code, _tuile[0][1]._code);
		swap(_tuile[0][0]._valide, _tuile[0][1]._valide);
		swap(_tuile[1][0]._code, _tuile[0][0]._code);
		swap(_tuile[1][0]._valide, _tuile[0][0]._valide);
	}
}

///=============== */
/* PI�CE � 3 CASES */
///=============== */

// Initialisateur permettant la surcharge de param�tres
piece3cases * piece3cases::create(const char & nom, const char * t)
{
	_nbTuile = 3;
	setNom(nom);
	piece::initTuile(t);
	return this;
}
// Initialisateur
piece3cases::piece3cases(const char & nom, const char * t)
{
	create(nom, t);
}

// Copieur h�r�ditaire
piece3cases * piece3cases::clone()
{
	return new piece3cases(*this);
}

// Destructeur
piece3cases::~piece3cases()
{
	piece::~piece();
}

// Effectue les modifications principale avant les rotations
void piece3cases::pivote()
{
	swap(_tuile[0][0]._code, _tuile[0][1]._code);
	swap(_tuile[0][0]._valide, _tuile[0][1]._valide);
	swap(_tuile[1][0]._code, _tuile[1][1]._code);
	swap(_tuile[1][0]._valide, _tuile[1][1]._valide);
}
// Fait pivoter la pi�ce sur elle-m�me dans le sens horaire
void piece3cases::tourne()
{
	pivote();
	swap(_tuile[0][0]._code, _tuile[1][1]._code);
	swap(_tuile[0][0]._valide, _tuile[1][1]._valide);
}