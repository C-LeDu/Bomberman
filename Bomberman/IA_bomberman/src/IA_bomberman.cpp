//============================================================================
// Name        : IA_bomberman.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <list>
#include <utility>
#include <algorithm>
#include <string>
using namespace std;

int getNumero(){
	std::string buffer;
	int j = 0;
	getline(cin, buffer);
	getline(cin, buffer);
	j =  atoi(buffer.c_str());
	getline(cin, buffer);
	return j;
}

void getSetting(){
	std::string buffer;
	getline(cin, buffer);
	// pour le moment on fait rien avec les settings on laisse tomber
	while (buffer != "STOP settings"){
		getline(cin, buffer);
	}
}

int main() {
	srand(time(NULL));
	char** tab;
	int joueur = getNumero();
	getSetting();
	int X = 0;
	int Y = 0;
	int posX = -1;
	int posY = -1;
	std::string buffer;
	while(1){
		// le tour du joueur on attend le message
		getline(cin, buffer); // START <turn #tour>
		cin >> buffer; // X
		X = atoi(buffer.c_str());
		cin >> buffer; // Y
		Y = atoi(buffer.c_str());
		tab = new char*[X]();
		for(int i = 0; i < X; i++){
			tab[i] = new char[Y]();
		}
		for(int i = 0; i < X; i++){
			for(int j = 0; j < Y; j++){
				cin >> buffer;
				tab[i][j] = buffer[0];
				if ('1' <= tab[i][j] && '9' >= tab[i][j] && (atoi(buffer.c_str()) == joueur || atoi(buffer.c_str()) == joueur+4)){
					posX = i;
					posY = j;
				}
			}
		}
		cin >> buffer; // STOP
		cin >> buffer; // turn
		cin >> buffer; // #tour
		// On recupere le tour
		int turn = atoi(buffer.c_str());
		//On choisi où on va
		if (posX != -1 && posY != -1){
			char actions[10] = {'U','U','D','D','L','L','R','R','B','N'};
			char dir;
			bool notOk = true;
			do {
				dir = actions[rand()%10];
				if(dir == 'U' && tab[posX-1][posY] == '_') notOk = false;
				else if (dir == 'D' && tab[posX+1][posY] == '_') notOk = false;
				else if (dir == 'R' && tab[posX][posY+1] == '_') notOk = false;
				else if (dir == 'L' && tab[posX][posY-1] == '_') notOk = false;
				else if (dir == 'B' || dir == 'N') notOk = false;
			} while (notOk);
			cout << "START action " << to_string(turn) << endl;
			cout << dir << endl;
			cout << "STOP action " << to_string(turn) << endl;
		} else {
			cout << "START action " << to_string(turn) << endl;
			cout << "N" << endl;
			cout << "STOP action " << to_string(turn) << endl;
		}
	}
}
