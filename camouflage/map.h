/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
// Ficher:	map.h
// But:		Objet du jeu où la solution des pièces doit être compatible.
*/

#pragma once
#include <iostream>
#include <fstream>	
#include <assert.h>
#include <vector>
using namespace std;

class map
{
private:
	vector<vector<char>> _map;			//matrice 2D dynamique de char

public:
	map();								//Constructeur par défaut
	map(int nbLigne, int nbCol);
	~map();								//Destructeur par défaut
	
	void init(ifstream& entree);		//Lit le fichier et initialise la carte avec
	void resize(int nbLigne, int nbCol);	//resize la matrice selon les dimensions

	char getCase(int x, int y)const;	//Retourne le contenu d'une case de la carte selon sa position X,Y
	int getSizeLine()const;					//Retourne le nombre de ligne du vecteur (Taille du grand vecteur)
	int getSizeCol()const;					//Retourne le nombre de colonnes du vecteur (Taille des petits vecteurs)
	void setCase(char val, int x, int y);	//Modifie le contenu d'une case de la carte selon sa position X,Y


	void print(ostream& sortie)const;	//Affiche le contenu de la carte
};
//afficher le contenu du vecteur avec l’opérateur <<
ostream& operator<<(ostream& sortie, const map& printMap);