/*
 * Joueur.cpp
 *
 *  Created on: 7 juil. 2018
 *      Author: user
 */

#include "Joueur.h"

Joueur::Joueur(int x, int y, int n, int b): Case(x,y), numero(n), maxBombe(b), nbBombe(b), bombeOn(0), mort(false) {

}

Joueur::~Joueur() {
}

bool Joueur::isDestructible() const{
	return true;
}
bool Joueur::isCollapsable() const{
	return false;
}

char Joueur::getCharAffichage() const{
	int n =  bombeOn != 0? numero+4: numero;
	return '0'+ n;
}

Bombe* Joueur::poserBombe(){
	nbBombe--;
	//TODO : Item bombe
	bombeOn = new Bombe(this->x, this->y, 3, numero, 4);
	return bombeOn;
}

int Joueur::getNbBombe() const{
	return nbBombe;
}
int Joueur::getNumero() const{
	return numero;
}
int Joueur::getMaxBombe() const{
	return maxBombe;
}
void Joueur::setMaxBombe(int b){
	maxBombe = b;
	if(nbBombe > b){
		nbBombe = b;
	}
}
void Joueur::addItem(Item* i){
	items.push_back(i);
}
std::list<Item*> Joueur::getItems() const{
	return items;
}
bool Joueur::isOnBombe() const{
	return bombeOn != 0;
}

Bombe* Joueur::popBombeOn(){
	Bombe* tmp = bombeOn;
	bombeOn = 0;
	return tmp;
}

void Joueur::upNbBombe(){
	nbBombe++;
}

void Joueur::setMort(bool b){
	mort = b;
}
bool Joueur::isMort() const{
	return mort;
}
