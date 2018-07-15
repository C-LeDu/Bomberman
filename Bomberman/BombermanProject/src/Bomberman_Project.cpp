//============================================================================
// Name        : Bomberman_Project.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include <string>
using namespace std;
#include "Plateau.h"

int getNbJoueurs(){
	std::string buffer;
	int j = 0;
	getline(cin, buffer);
	getline(cin, buffer);
	j =  atoi(buffer.c_str());
	getline(cin, buffer);
	return j;
}

void communiqueSettings(){
	cout << "START settings" << endl;
	cout << "NB_BOMBS 3" << endl;
	cout << "BOMB_DURATION 4" << endl;
	cout << "BOMB_RADIUS 3" << endl;
	cout << "STOP settings" << endl;
}

int main() {
	int j = getNbJoueurs();
	communiqueSettings();
	Plateau* p = new Plateau(21,21, false, j);
	int i = 1;
	while(p->getGagnant() == 0) {
		p->tourAllJoueurs(i);
		p->explosionBombes();
		i++;
	}
	char g = '0' + p->getGagnant();
	cout << "Victory of player " << g;
	return 0;
}
