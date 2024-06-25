#include "SosnowskyHogWeed.h"
#include "World.h"
#include "Animal.h"
#include "consoleUtils.h"
#include <string>
using namespace std;
SosnowskyHogWeed::SosnowskyHogWeed(int x, int y) : Plant('!', 10, x, y) {};

void SosnowskyHogWeed::killNeighbours() {
	vector<char> neighbouringTiles = { 'N','E','S','W' };
	int finalX, finalY;
	while (neighbouringTiles.size()) {
		finalX = getX(), finalY = getY();
		switch (neighbouringTiles[neighbouringTiles.size() - 1]) {
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
		neighbouringTiles.pop_back();
		if (finalX < 0 || finalX >= world->getWidth() || finalY < 0 || finalY >= world->getHeight()) // check if outside borders
		{
			continue;
		}

		Organism* target = world->GetOrganismAtTile(finalX, finalY);
		Animal* targetAnimal = dynamic_cast<Animal*>(target);
		if (targetAnimal != nullptr) {
			string log;
			log += targetAnimal->getSymbol();
			log.append(" got too close to sosnowsky hog weed and died :( ");
			world->addLog(log);

			world->RemoveOrganismAndFreeTile(targetAnimal);
			delete targetAnimal;
		
			gotoxy(1, 1);
		}

	}
}

void SosnowskyHogWeed::action() {
	increaseAge();
	if (noSpace) {
		return;
	}
	int roll = 1 + rand() % 1000;
	if (roll == 1000) {
		ExpandInNewPlace();
	}

	if (roll > 13)
		killNeighbours();
	else {
		TryToGrow();
		killNeighbours();
	}

	
}

void SosnowskyHogWeed::GetEaten(Organism* o) {
	string log;
	log += o->getSymbol();
	log.append(" ate ! (sosnowsky hog weed) and died.");
	world->addLog(log);

	//no organism removal here
	//special case because of deleting two organisms in one action, See animal.cpp collision()
}