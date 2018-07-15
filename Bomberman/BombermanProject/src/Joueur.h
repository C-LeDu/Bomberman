/*
 * Joueur.h
 *
 *  Created on: 7 juil. 2018
 *      Author: user
 */

#ifndef JOUEUR_H_
#define JOUEUR_H_

#include <vector>
#include "Case.h"
#include "Item.h"
#include <list>
#include <cstddef>
#include "Bombe.h"

class Joueur: public Case{
private:
	int nbBombe;
	int numero;
	int maxBombe;
	std::list<Item*> items;
	Bombe* bombeOn;
	bool mort;

public:
	Joueur(int x, int y, int n, int b);
	virtual ~Joueur();
	virtual bool isDestructible() const;
	virtual bool isCollapsable() const;
	// Charles
	virtual char getCharAffichage() const;
	// Charles
	Bombe* poserBombe();
	int getNbBombe() const;
	int getNumero() const;
	int getMaxBombe() const;
	void setMaxBombe(int b);
	// Pierre
	void addItem(Item* i);
	// Pierre
	std::list<Item*> getItems() const;
	bool isOnBombe() const;
	// Julien
	Bombe* popBombeOn();
	void upNbBombe();
	void setMort(bool b);
	bool isMort() const;

};

#endif /* JOUEUR_H_ */
