#include "Turtle.h"
#include "World.h"
#include <cstdlib>
#include <ctime>
Turtle::Turtle(int x, int y) : Animal('T', 2, 1, x, y)
{
	std::srand(time(0));
}
void Turtle::action() {
	increaseAge();

	vector<char> neighbouringTiles = { 'N','E','S','W' };
	int randVar, finalX, finalY;

	randVar = rand() % 4; //75% not to move
	if (randVar)
		return;

	while (neighbouringTiles.size()) {
		finalX = x, finalY = y;
		randVar = rand() % neighbouringTiles.size();

		switch (neighbouringTiles[randVar]) {
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
		neighbouringTiles.erase(neighbouringTiles.begin() + randVar); // pop rolled tile

		if (finalX < 0 || finalX >= world->getWidth() || finalY < 0 || finalY >= world->getHeight()) // check if outside borders
		{
			continue;
		}

		Organism* tileHabitant = world->GetOrganismAtTile(finalX, finalY);
		if (tileHabitant != nullptr) {
			//collision
			if (tileHabitant->getSymbol() == getSymbol())
				breed();
			else 
				collision(tileHabitant, finalX, finalY);
			break;
		}
		else {

			moveLog(finalX, finalY);
			world->MoveOrganismOnMap(this, finalX, finalY);
			setPosition(finalX, finalY);
			break;
		}
	}
}
