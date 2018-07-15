/*
 * Item.cpp
 *
 *  Created on: 11 mai 2018
 *      Author: Pierre
 */

#include "Item.h"

Item::Item(int x, int y, char t): Case(x,y), type(t){
}

Item::~Item() {
}

bool Item::isDestructible() const{
	return true;
}
bool Item::isCollapsable() const{
	return true;
}
char Item::getCharAffichage() const{
	return type;
}
char Item::getType() const{
	return type;
}
void Item::setType(char t){
	type = t;
}
