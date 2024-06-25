#include "Fox.h"
#include "World.h"

#include <cstdlib>
#include <ctime>
Fox::Fox(int x, int y) : Animal('F', 3, 7, x, y)
{
	std::srand(time(0));
}
void Fox::action() {
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


		Organism* tileHabitant = world->GetOrganismAtTile(finalX, finalY);
		if (tileHabitant != nullptr) {
			//collision
			if (tileHabitant->getSymbol() == getSymbol())
				breed();
			else {
				if (tileHabitant->getStrength() > getStrength())
					continue;
				collision(tileHabitant, finalX, finalY);
			}

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
