#include "Animal.h"
#include "World.h"
#include "Plant.h"
#include "consoleUtils.h"
#include "Sheep.h"
#include "Wolf.h"
#include "Fox.h"
#include "Antilope.h"
#include "Turtle.h"
#include "Grass.h"
#include "SowThisle.h"


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
Animal::Animal(char symbol, int strength, int initiative, int x, int y) : Organism(symbol, strength, initiative, x, y)
{
	std::srand(time(0));

}

void Animal::moveLog(int finalX,int finalY) {
	string log;
	log += symbol;
	log.append(" moved from ");
	log += to_string(x);
	log += ' ';
	log += to_string(y);
	log.append(" to ");
	log += to_string(finalX);
	log += ' ';
	log += to_string(finalY);
	world->addLog(log);
}

void Animal::action() {
	increaseAge();

	vector<char> neighbouringTiles = { 'N','E','S','W' };
	int rolledTile, finalX, finalY;
	while (neighbouringTiles.size()) {
		finalX = x, finalY = y;
		rolledTile = rand() % neighbouringTiles.size();
		
		switch (neighbouringTiles[rolledTile]) {
		case 'N':
			finalY--;
			break;
		case 'E':
			finalX++;
			break;
		case 'S':
			finalY++;
			break;
		case 'W':
			finalX--;
			break;
		}
		neighbouringTiles.erase(neighbouringTiles.begin() + rolledTile); // pop rolled tile
		if (finalX < 0 || finalX >= world->getWidth() || finalY < 0 || finalY >= world->getHeight()) // check if outside borders
		{
			continue;
		}
		//...

		Organism* tileHabitant = world->GetOrganismAtTile(finalX,finalY);
		if (tileHabitant!=nullptr) {
			//collision
			if (tileHabitant->getSymbol() == getSymbol())
				breed();
			else
				collision(tileHabitant, finalX,finalY);

			break;
		}
		else {

			moveLog(finalX,finalY);
			world->MoveOrganismOnMap(this, finalX, finalY);
			setPosition(finalX, finalY);
			break;
		}
	}
}

void Animal::breed() {
	string log;
	Organism* tileHabitant;
	vector<char> neighbouringTiles = { 'N','E','S','W' };
	int rolledTile, finalX, finalY;
	while (neighbouringTiles.size()) {
		finalX = x, finalY = y;
		rolledTile = rand() % neighbouringTiles.size();

		switch (neighbouringTiles[rolledTile]) {
		case 'N':
			finalY--;
			break;
		case 'E':
			finalX++;
			break;
		case 'S':
			finalY++;
			break;
		case 'W':
			finalX--;
			break;
		}
		neighbouringTiles.erase(neighbouringTiles.begin() + rolledTile); // pop rolled tile
		if (finalX < 0 || finalX >= world->getWidth() || finalY < 0 || finalY >= world->getHeight()) // check if outside borders
			continue;

		tileHabitant = world->GetOrganismAtTile(finalX, finalY);
		Grass* grassPtr = dynamic_cast<Grass*>(tileHabitant);
		SowThisle* sowThislePtr = dynamic_cast<SowThisle*>(tileHabitant);
		if (tileHabitant == nullptr || grassPtr || sowThislePtr) {
			if (grassPtr || sowThislePtr) {
				world->RemoveOrganismAndFreeTile(tileHabitant);
				delete tileHabitant;
			}
			switch (symbol) {
			case 'S':
				new Sheep(finalX, finalY);
				break;
			case 'W':
				new Wolf(finalX, finalY);
				break;

			case 'F':
				new Fox(finalX, finalY);
				break;
			case 'T':
				new Turtle(finalX, finalY);
				break;
			case 'A':
				new Antilope(finalX, finalY);
				break;
			}
			log += symbol;
			log.append(" has breeded! ");
			log += to_string(finalX);
			log += ' ';
			log += to_string(finalY);
			world->addLog(log);
			return;
		}

	}
	/*
	log += symbol;
	log.append(" at: ");
	log += to_string(getX());
	log += ' ';
	log += to_string(getY());
	log.append("Tried to breed. No space.");
	world->addLog(log);
	*/
}

void Animal::collision(Organism* o, int x, int y) {
	string log;
	Plant* plantCollider = dynamic_cast<Plant*>(o);
	if (plantCollider) {

 		plantCollider->GetEaten(this);


		if (plantCollider->getSymbol() == '%' || plantCollider->getSymbol() == '!') { //special case - nightshade: two organisms removal in one action 
			world->RemoveOrganismAndFreeTile(o);
			delete o;
			eraseFromWorld();
			world->RemoveOrganismAndFreeTile(this);
			world->SetOrganismToDelete(this);
			return;
		}
		else {
			world->RemoveOrganismAndFreeTile(o);
			delete o;
		}
		world->MoveOrganismOnMap(this, x, y);
		setPosition(x, y);
		return; // Don't add log - Logs are custom for plants and are added in GetEaten() method
	}

	if (getStrength() < 5 && o->getSymbol() == 'T') {
		log += symbol;
		log.append(" tried to attack a T(urtle) and retreated.");
		world->addLog(log);
		return;
	}

	log += symbol;
	log.append(" started a fight with ");
	log += o->getSymbol();

	if (strength < o->getStrength()) {
		log.append(" and lost!");

		world->RemoveOrganismAndFreeTile(this);
		world->SetOrganismToDelete(this);

	}
	else {
		log.append(" and won!");

		world->RemoveOrganismAndFreeTile(o);
		delete o;

		world->MoveOrganismOnMap(this, x, y);
		setPosition(x, y);
	}
	world->addLog(log);
}