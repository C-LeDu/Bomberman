/*
 * Case.h
 *
 *  Created on: 11 mai 2018
 *      Author: user
 */

#ifndef CASE_H_
#define CASE_H_

class Case {
protected:
	int x;
	int y;

public:
	Case(int x, int y);
	virtual ~Case();
	virtual bool isDestructible() const;
	virtual bool isCollapsable() const;
	virtual char getCharAffichage() const;
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
};

#endif /* CASE_H_ */
