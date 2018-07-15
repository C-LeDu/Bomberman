/*
 * Bombe.h
 *
 *  Created on: 11 mai 2018
 *      Author: user
 */

#ifndef BOMBE_H_
#define BOMBE_H_
#include "Case.h"

class Joueur;

class Bombe: public Case {
private:
	int rayon;
	int owner;
	int tours;

public:
	Bombe(int x, int y, int r, int o, int t);
	virtual ~Bombe();
	virtual bool isDestructible() const;
	virtual bool isCollapsable() const;
	virtual char getCharAffichage() const;
	int getRayon() const;
	void setRayon(int r);
	int getOwner() const;
	void setOwner(int o);
	int getTours() const;
	void setTours(int t);
	bool diminuerTours();
};

#endif /* BOMBE_H_ */
