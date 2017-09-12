/* Auteur:	Olivier Lemay Dostie et Olivier G.F.
// Date:	30 août 2017
// Ficher:	map.cpp
// But:		Objet du jeu dont les pièces se posent dessus.
*/

#pragma once
using namespace std;
#include <iostream>
#include <fstream>	
#include <string>
#include <vector>


class map
{
private:
	ifstream _entree;
	vector<vector<char>> _map;
public:
	map();
	~map();
	string openFile(ostream& sortie);	//Ouvre le fichier et apelle la fonction de lecture de fichier
	void initMap();		//Lit le fichier et initialise la carte avec
	void print(ostream& sortie)const;	//Affiche le contenu de la carte
	char getCase(int x, int y)const;	//Retourne le contenu d'une case de la carte selon sa position X,Y
};
//afficher le contenu du vecteur avec l’opérateur <<
ostream& operator<<(ostream& sortie, const map& printMap);