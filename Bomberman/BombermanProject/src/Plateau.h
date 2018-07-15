/*
 * Plateau.h
 *
 *  Created on: 11 mai 2018
 *      Author: user
 */

#ifndef PLATEAU_H_
#define PLATEAU_H_
#include "Case.h"
#include "Joueur.h"
#include "Bombe.h"
#include "Mur.h"
#include "Item.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <list>
#include <utility>
#include <algorithm>
#include <string>

class Plateau {
private:
	Case*** tab;
	int X;
	int Y;
	bool isTor;
	std::list<Joueur*> joueurs;
	std::list<Bombe*> bombes;
	int gagnant;

	// Julien
	void initTab();
	// Julien
	void initTourTab();
	// Julien
	void initMillieuTab();
	// Julien
	void initMurDestructible();
	// Julien
	void initJoueurs(int nb);
	// Julien
	bool isOkPlacerJoueurIci(int x, int y) const;
	// Charles
	std::pair<int,int> getDirPosition(int x, int y, char dir) const;
	// Charles
	void printTurnTourJoueur(int tour, int joueur) const;
	// Charles
	char getActionTourJoueur() const;
public:
	Plateau(const int l, const int h, bool t, int nbJoueurs);
	virtual ~Plateau();
	// Charles
	friend std::ostream& operator<<(std::ostream& ostr, const Plateau& p);
	// Charlotte
	void tourAllJoueurs(int tour);
	// Charlotte
	void tourJoueur(int tour);
	// Charlotte
	void deplacerJoueur(Joueur* j, char direction);
	// Charlotte
	void explosionBombes();
	// Charlotte
	bool destructionCase(int x, int y);
	// Charles
	int getGagnant();
	// Charles
	void setGagnant();
};

#endif /* PLATEAU_H_ */
