/*
 * Plateau.cpp
 *
 *  Created on: 11 mai 2018
 *      Author: user
 */

#include "Plateau.h"

Plateau::Plateau(const int l,const int h, bool t, int nbJoueurs): X(l), Y(h), isTor(t), gagnant(0) {
	tab = new Case**[l];
	for(int i = 0; i < l; ++i){
		tab[i] = new Case*[h];
		for(int j = 0; j <h ; ++j){
			tab[i][j] = new Case(i,j);
		}
	}
	initTab();
	initJoueurs(nbJoueurs);
}

Plateau::~Plateau() {
	delete[] tab;
}

void Plateau::initTab(){
	initTourTab();
	initMillieuTab();
	initMurDestructible();
}

void Plateau::initTourTab(){
	// 1er ligne
	for(int i = 0; i<X; i++){
		tab[i][0] = new Mur(i, 0, false);
	}
	// 1er col et derniere col
	for(int i = 1; i<Y-1; i++){
		tab[0][i] = new Mur(0, i, false);
		tab[X-1][i] = new Mur(X-1, i, false);
	}
	//derniere ligne
	for(int i = 0; i< X; i++){
		tab[i][Y-1] = new Mur(i, Y-1, false);
	}
}

void Plateau::initJoueurs(int nb){
	for (int i = 1; i <= nb; i++){
		int x=rand()%X;
		int y=rand()%Y;
		if (isOkPlacerJoueurIci(x,y)){
			tab[x][y]= new Joueur(x, y, i,3);
			joueurs.push_back((Joueur*)tab[x][y]);
		} else{
			i--;
		}
	}
}

bool Plateau::isOkPlacerJoueurIci(int x, int y) const{
	return tab[x][y]->getCharAffichage() == '_';
}

void Plateau::initMillieuTab(){
	for (int i = 2; i < X-2 ; i+=2){
		for (int j= 2; j<Y-2; j+=2){
			tab[i][j] = new Mur(i, j, false);
		}
	}
}

void Plateau::initMurDestructible(){
	srand(time(NULL));
	int nbMur = ((2*X)+(2*Y)+(X*Y/4)-(Y/2)-(X/2)-3)/2;
	for (int i = 0; i<nbMur; i++) {
		int x=rand()%X;
		int y=rand()%Y;
		if (tab[x][y]->getCharAffichage() == '_'){
			tab[x][y] = new Mur(x, y, true);
		}else {
			i--;
		}
	}
}

std::pair<int,int> Plateau::getDirPosition(int x, int y, char dir) const{
	if (!isTor){
		if(dir == 'U') return std::make_pair(x-1, y);
		else if (dir == 'D') return std::make_pair(x+1, y);
		else if (dir == 'R') return std::make_pair(x, y+1);
		else if (dir == 'L') return std::make_pair(x, y-1);
		else return std::make_pair(-1, -1);
	}
	else{
		if(dir == 'U') return std::make_pair(x-1 >=0? x-1: X-1, y);
		else if (dir == 'D') return std::make_pair(x+1<X? x+1:0, y);
		else if (dir == 'R') return std::make_pair(x, y+1<Y? y+1:0);
		else if (dir == 'L') return std::make_pair(x, y-1>=0? y-1: Y-1);
		else return std::make_pair(-1, -1);
	}
}

std::ostream& operator<<(std::ostream& ostr, const Plateau& p){
	for(int i=0; i<p.X; i++){
		for (int j=0; j<p.Y; j++){
			ostr << p.tab[i][j]->getCharAffichage() << " ";
		}
		ostr << std::endl;
	}
	return ostr;
}

void Plateau::deplacerJoueur(Joueur* j, char direction){
	std::pair<int,int> newEmp = getDirPosition(j->getX(), j->getY(), direction);

	if (j->isOnBombe()){
		Bombe* b = j->popBombeOn();
		tab[b->getX()][b->getY()] = b;
	}
	else {
		tab[j->getX()][j->getY()] = new Case(j->getX(), j->getY());
	}
	j->setX(newEmp.first);
	j->setY(newEmp.second);
	if(tab[newEmp.first][newEmp.second]->getCharAffichage() != '_'){
		j->addItem((Item*)tab[newEmp.first][newEmp.second]);
	}
	tab[newEmp.first][newEmp.second] = (Case *) j;
}

void Plateau::tourAllJoueurs(int tour){
	for (int i = 0; i<joueurs.size(); i++){
		tourJoueur(tour);
	}
}

void Plateau::tourJoueur(int tour){
	Joueur* j = joueurs.front();
	joueurs.pop_front();
	// TODO : récup direction
	printTurnTourJoueur(tour, j->getNumero());
	char a = getActionTourJoueur();
	if(a != 'N' && a !='B') deplacerJoueur(j,a);
	else if(a =='B'){
		Bombe* b = j->poserBombe();
		if (b != 0) {
			bombes.push_back(b);
		}
	}
	joueurs.push_back(j);
}

void Plateau::explosionBombes(){
	char dir[4] =  {'U', 'D', 'L', 'R'};
	bool bombeTouche = true;
	std::list<Bombe*> newListBombe = bombes;
	for (std::list<Bombe*>::iterator it = bombes.begin(); it != bombes.end(); it++){
		(*it)->diminuerTours();
	}
	while (bombeTouche){
		bombeTouche = false;
		for (std::list<Bombe*>::iterator it = bombes.begin(); it != bombes.end(); it++){
			if((*it)->getTours() == 0){
				// il faut détruire g+r d+r h+r b+r
				// + sur la case!
				for (int j=0; j<4; j++){
					std::pair<int,int> pos = std::make_pair((*it)->getX(), (*it)->getY());
					for(int i=0; i<(*it)->getRayon(); i++){
						pos = getDirPosition(pos.first, pos.second, dir[j]);
						if(pos.first != -1 && pos.second != -1){
							if(tab[pos.first][pos.second]->isDestructible()){
								bombeTouche = bombeTouche || destructionCase(pos.first,pos.second);
								if(bombeTouche){
									i = (*it)->getRayon();
								}
							} else {
								i = (*it)->getRayon();
							}
						}else{
							i = (*it)->getRayon();
						}
					}
				}
				// On a fait les 4 directions du coup on explose la case principale
				// Au cas où y a un joueur sur la case
				destructionCase((*it)->getX(), (*it)->getY());
				tab[(*it)->getX()][(*it)->getY()] = new Case((*it)->getX(), (*it)->getY());
				newListBombe.remove(*it);
				// il faut redonner au joueur une bombe
				for (std::list<Joueur*>::iterator itj = joueurs.begin(); itj != joueurs.end(); itj++){
					if((*itj)->getNumero() == (*it)->getOwner()){
						(*itj)->upNbBombe();
					}
				}
			}
		}
	}
	// On met à jour la liste des bombes en retirant celles qui ont explosé
	bombes = newListBombe;
}

bool Plateau::destructionCase(int x, int y){
	char c = tab[x][y]->getCharAffichage();
	bool b = false;
	if (c == '%'){
		// mur destructible faire aléa pour les item ?
		tab[x][y] = new Case(x,y);
	}
	else if('o' == c){
		// c'est une autre bombe
		b = true;
		((Bombe*)tab[x][y])->setTours(0);
	}
	else if ('1' <= c && c <= '9'){
		// c'est un perso il faut le retirer de la partie
		 ((Joueur*)tab[x][y])->setMort(true);
		 tab[x][y] = new Case(x,y);
		 setGagnant();
	}
	else{
		// c'est un item
		tab[x][y] = new Case(x,y);
	}
	return b;
}

int Plateau::getGagnant(){
	return gagnant;
}

void Plateau::printTurnTourJoueur(int tour, int joueur) const{
	std::cout << "START turn " << std::to_string(tour) << " " << std::to_string(joueur) << std::endl;
	std::cout << std::to_string(X) << " " << std::to_string(Y) << std::endl;
	std::cout << *this;
	std::cout << "STOP turn " << std::to_string(tour) << " " << std::to_string(joueur) << std::endl;
}

char Plateau::getActionTourJoueur() const{
	std::string buffer;
	std::getline(std::cin, buffer); // START action #joueur
	std::getline(std::cin, buffer); // action
	char a = buffer[0];
	std::getline(std::cin, buffer); // STOP action #joueur
	return a;
}

void Plateau::setGagnant(){
	int count = 0;
	int last_joueur_vivant = 0;
	for (std::list<Joueur*>::iterator it = joueurs.begin(); it != joueurs.end(); it++){
		if(!(*it)->isMort()){
			last_joueur_vivant = (*it)->getNumero();
			count ++;
		}
	}
	if (count == 1){
		gagnant = last_joueur_vivant;
	}
}
