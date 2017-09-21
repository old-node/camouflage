/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
// Ficher:	piece.cpp
*/

#include "piece.h"

// Permet l'écriture des pièces avec l'opérater <<
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
// Initialisateur par défaut
piece::piece()
{
	create('T', "_");
}
// Initialisateur
piece::piece(const char & nom, const char * t)
{
	create(nom, t);
}
// Initialise le nombre de tuile nécessaire pour la pièce
void piece::initTuile(const char * t)
{
	int pos = 0;					// Position du caractère à ajouter dans la tuile

	for (int i = 0; i < 2; i++)		// Pour toute la matrice
	{
		for (int j = 0; j < 2; j++)
		{
			if (pos < _nbTuile)		// Rempli la tuile selon le caractère de la chaine
			{
				assert(!iswspace(t[i]) | t[i] == ' ');	// Si un mauvais type de caractère est présent
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

// Change le caractère qui représente la pièce
void piece::setNom(char nom)
{
	assert(!isspace(nom));
	_nom = nom;
}

// Retourne le caractère qui représente la pièce
char piece::getNom() const
{
	return _nom;
}
// Obtient le nombre de tuiles de la pièce
int piece::getNbTuile() const
{
	return _nbTuile;
}
// Retourne une des tuile de la pièce
char piece::getTuile(int i, int j) const
{
	assert(i >= 0 && i < 2 && j >= 0 && j < 2);
	return _tuile[i][j]._code;
}

// Affiche le contenu de toutes les tuiles de la pièce
void piece::print(ostream & sortie) const
{
	for (int i = 0; i < 2; i++)		// Pour la matrice au complet
	{
		for (int j = 0; j < 2; j++)
		{
			if (_tuile[i][j]._valide)
				// Affiche le contenu de la tuile avec le nom de la pièce
				sortie << _nom << _tuile[i][j]._code << " ";
			else
				sortie << "   ";	// Remplace les tuiles invalide par des espaces
		}
		sortie << endl;
	}
	sortie << endl;
}


///============= */
/* PIECE 2 CASES */
///============= */

// Initialisateur permettant la surcharge de paramètres
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

// Copieur héréditaire
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

// Fait pivoter la pièce sur elle-même dans le sens horaire
void piece2cases::tourne()
{
	if (_angle)				// Déplacement simple de l'extrémité de la pièce
	{
		_angle = false;
		swap(_tuile[0][1]._code, _tuile[1][0]._code);
		swap(_tuile[0][1]._valide, _tuile[1][0]._valide);
	}
	else					// Rotation complète normale
	{
		_angle = true;
		swap(_tuile[0][0]._code, _tuile[0][1]._code);
		swap(_tuile[0][0]._valide, _tuile[0][1]._valide);
		swap(_tuile[1][0]._code, _tuile[0][0]._code);
		swap(_tuile[1][0]._valide, _tuile[0][0]._valide);
	}
}

///=============== */
/* PIÈCE À 3 CASES */
///=============== */

// Initialisateur permettant la surcharge de paramètres
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

// Copieur héréditaire
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
// Fait pivoter la pièce sur elle-même dans le sens horaire
void piece3cases::tourne()
{
	pivote();
	swap(_tuile[0][0]._code, _tuile[1][1]._code);
	swap(_tuile[0][0]._valide, _tuile[1][1]._valide);
}