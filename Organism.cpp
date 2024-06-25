#include "Organism.h"
#include "World.h"
#include <iostream>
#include "consoleUtils.h"

Organism::Organism(char symbol, int strength, int initiative, int x, int y) {
	this->world = World::getInstance();
	this->symbol = symbol;
	this->strength = strength;
	this->initiative = initiative;
	this->x= x;
	this->y=y;
	this->age = 0;
	drawOnWorld();
	world->AddOrganism(this);
}

Organism::~Organism() {
	if (getSymbol() == 'H') {
		world->TriggerGameOver();
	}
	/*
	string l = "Destructor ";
	l += symbol;
	world->addLog(l);
	*/
	//cout << endl<< "Destructor " << symbol;
}

void Organism::fixPositionOnMap() {
	world->MoveOrganismOnMap(this, x, y);
}

void Organism::getBURNED() {
	string l = "H BURNED ";
	l += symbol;
	world->addLog(l);
	
	changeColor(GRAY);
	gotoxy(x+1, y+1);
	cout << "#";
	changeColor(DEFAULT);
	
}

int Organism::getStrength() const {
	return strength;
}
int Organism::getInitiative() const {
	return initiative;
}
int Organism::getX() const {
	return x;
}
int Organism::getY() const {
	return y;
}

int Organism::getAge() const {
	return age;
}

char Organism::getSymbol() const {
	return symbol;
}

void Organism::increaseAge() {
	age++;
}

void Organism::setPosition(int newX, int newY) {
	eraseFromWorld();
	x = newX;
	y = newY;
	drawOnWorld();
}
void Organism::setStrength(int newStrength) {
	strength = newStrength;
}


void Organism::drawOnWorld() {
	gotoxy(1 + x, 1 + y);
	switch (symbol) {
	case '#':
		changeColor(GREEN);
		break;

	case '@':
		changeColor(YELLOW);
		break;

	case '&':
		changeColor(DARK_GREEN);
		break;
	case '!':
		changeColor(DARK_GREEN);
		break;
	case '%':
		changeColor(DARK_RED);
		break;
	}
	cout << symbol;
	changeColor(DEFAULT);
	gotoxy(world->getWidth() + 2, world->getHeight() + 2);
}

void Organism::eraseFromWorld() {
	gotoxy(1 + x, 1 + y);
	cout << " ";
}