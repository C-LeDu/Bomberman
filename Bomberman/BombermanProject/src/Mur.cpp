/*
 * Mur.cpp
 *
 *  Created on: 11 mai 2018
 *      Author: user
 */

#include "Mur.h"

Mur::Mur(int x, int y, bool destructible): Case(x,y), destructible(destructible) {

}

Mur::~Mur() {
}

bool Mur::isDestructible() const{
	return destructible;
}
bool Mur::isCollapsable() const{
	return false;
}
char Mur::getCharAffichage() const{
	if (destructible){
		return '%';
	} else {
		return '#';
	}
}
