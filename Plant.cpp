#include "Plant.h"
#include "World.h"
#include "Grass.h"
#include "SowThisle.h"
#include "Animal.h"
#include "Guarana.h"
#include "Nightshade.h"
#include "SosnowskyHogWeed.h"

#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
Plant::Plant(char symbol, int strength, int x, int y) : Organism(symbol,strength,0,x,y) {
	std::srand(time(0));
	noSpace = false;
}

Plant::~Plant() {
	if(!world->IsGameOver())
		SendNewSpaceSignal();
}

void GrowNew(int finalX, int finalY,char symbol) {
	switch (symbol) {
	case '#':
		new Grass(finalX, finalY);
		break;
	case '@':
		new SowThisle(finalX, finalY);
		break;
	case '&':
		new Guarana(finalX, finalY);
		break;
	case '%':
		new Nightshade(finalX, finalY);
		break;
	case '!':
		new SosnowskyHogWeed(finalX, finalY);
		break;
	}
}

void Plant::TryToGrow() {
	bool maybeSpace = false;
	vector<char> neighbouringTiles = { 'N','E','S','W' };
	int rolledTile, finalX, finalY;
	while(neighbouringTiles.size()) {
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
		if (finalX < 0 || finalX >= world->getWidth() || finalY < 0 || finalY >= world->getHeight()) // check if outside borders
		{
			neighbouringTiles.erase(neighbouringTiles.begin() + rolledTile); // pop rolled tile
			continue;
		}
		if (world->GetOrganismAtTile(finalX, finalY) == nullptr) {
			GrowNew(finalX, finalY, symbol);
			return;
		}
		else {
			//If there is a nearby animal, set that maybe in next turn there will be space to grow
			Animal* animalPtr = dynamic_cast<Animal*>(world->GetOrganismAtTile(finalX, finalY));
			if (animalPtr) {
				maybeSpace = true;
			}
		}
		neighbouringTiles.erase(neighbouringTiles.begin() + rolledTile); // pop rolled tile
	}
	if(!maybeSpace)
		noSpace = true;
}

void Plant::ExpandInNewPlace() {
	int finalX, finalY;
	for (int i = 0;i < 3;i++) {
		finalX = rand() % world->getWidth();
		finalY = rand() % world->getHeight();
		if (world->GetOrganismAtTile(finalX, finalY) == nullptr) {
			GrowNew(finalX, finalY, symbol);
			break;
		}
	}
}

void Plant::action() {
	increaseAge();
	if (noSpace) {
		return;
	}
	int roll = 1 + rand() % 1000;
	if (roll == 1000) {
		ExpandInNewPlace();
	}

	if (roll > 13)
		return;
	TryToGrow();
}

void Plant::SendNewSpaceSignal() {
	vector<char> neighbouringTiles = { 'N','E','S','W' };
	int rolledTile, finalX, finalY;
	while (neighbouringTiles.size()) {
		finalX = x, finalY = y;
		switch (neighbouringTiles[neighbouringTiles.size()-1]) {
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
		neighbouringTiles.pop_back(); // pop rolled tile
		if (finalX < 0 || finalX >= world->getWidth() || finalY < 0 || finalY >= world->getHeight()) // check if outside borders
			continue;
		Plant* plantPtr = dynamic_cast<Plant*>(world->GetOrganismAtTile(finalX, finalY));
		if (plantPtr) {
			plantPtr->SetNewSpace();
		}
	}
}

void Plant::SetNewSpace() {
	noSpace = false;
}

void Plant::GetEaten(Organism* o) {
	string log;
	log += o->getSymbol();
	log.append(" ate ");
	log += getSymbol();
	world->addLog(log);
};

void Plant::collision(Organism* o, int x, int y) {};