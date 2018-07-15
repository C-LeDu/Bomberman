/*
 * Case.cpp
 *
 *  Created on: 11 mai 2018
 *      Author: user
 */

#include "Case.h"

Case::Case(int x, int y): x(x), y(y){
}

Case::~Case() {
}

bool Case::isDestructible() const{
	return true;
}

bool Case::isCollapsable() const{
	return false;
}

char Case::getCharAffichage() const{
	return '_';
}

int Case::getX() const{
	return x;
}
int Case::getY() const{
	return y;
}
void Case::setX(int x){
	this->x = x;
}
void Case::setY(int y){
	this->y = y;
}
