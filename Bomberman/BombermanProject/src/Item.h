/*
 * Item.h
 *
 *  Created on: 11 mai 2018
 *      Author: Pierre
 */

#ifndef ITEM_H_
#define ITEM_H_
#include "Case.h"

class Item: public Case {
private:
	char type;
public:
	Item(int x, int y, char t);
	virtual ~Item();
	virtual bool isDestructible() const;
	virtual bool isCollapsable() const;
	virtual char getCharAffichage() const;
	char getType() const;
	void setType(char t);
};

#endif /* ITEM_H_ */
