#include "Antilope.h"
#include "World.h"

#include <cstdlib>
#include <ctime>
Antilope::Antilope(int x, int y) : Animal('A', 4, 4, x, y)
{
	std::srand(time(0));
}
void Antilope::action() {
	increaseAge();

	vector<char> neighbouringTiles = { 'N','n','E','e','S','s','W','w' };
	int rolledTile, finalX, finalY;
	while (neighbouringTiles.size()) {
		finalX = x, finalY = y;
		rolledTile = rand() % neighbouringTiles.size();

		switch (neighbouringTiles[rolledTile]) {
		case 'N':
			finalY-=2;
			break;
		case 'E':
			finalX+=2;
			break;
		case 'S':
			finalY+=2;
			break;
		case 'W':
			finalX-=2;
			break;
		case 'n':
			finalY--;
			break;
		case 'e':
			finalX++;
			break;
		case 's':
			finalY++;
			break;
		case 'w':
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
				collision(tileHabitant, finalX, finalY);
			}

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
