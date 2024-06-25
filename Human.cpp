#include "Human.h"
#include "World.h"
#include <conio.h>
#include "consoleUtils.h"
Human::Human(int x, int y) : Animal('H', 5, 4, x, y)
{
	burnCooldown = 5;
	burnDuration = 0;
}
void Human::action() {
	increaseAge();

	if (!world->IsLoadSkipping()) {
		if (burnDuration) {
			burnDuration--;
		}
		else if (burnCooldown)
			burnCooldown--;
	}
	

	int rolledTile, finalX, finalY;
	char move;

	world->printLog();
	world->PrintOrganismCount();
	
	gotoxy(0, world->getHeight() + 2);
	cout << "              ";
	gotoxy(0, world->getHeight() + 2);
	cout << "Skill Dur:" << burnDuration << " Skill Cool:" << burnCooldown << " E-Save Q-Quit B-Burnsas";
	while (true) {
		finalX = x, finalY = y;
		move = _getch();
		if (move == 0 || move == -32) {  // Arrow key
			move = _getch();
			switch (move) {
			case 72:  // Up arrow
				finalY--;
				break;
			case 80:  // Down arrow
				finalY++;
				break;
			case 75:  // Left arrow
				finalX--;
				break;
			case 77:  // Right arrow
				finalX++;
				break;
			}
		}
		else {
			// WASD keys
			switch (move) {
			case 'w':
			case 'W':
				finalY--;
				break;
			case 'a':
			case 'A':
				finalX--;
				break;
			case 's':
			case 'S':
				finalY++;
				break;
			case 'd':
			case 'D':
				finalX++;
				break;
			case 'b':
			case 'B':
				if (burnCooldown>0)
					continue;
				burnDuration = 5;
				burnCooldown = 5;
				world->clearLog();
				BURN();
				return;
			case 'q':
			case 'Q':
				world->TriggerGameOver();
				return;
			case 'e':
			case 'E':
				world->WriteSave();
				continue;
			default:
				continue;
			}
		}
		if (finalX < 0 || finalX >= world->getWidth() || finalY < 0 || finalY >= world->getHeight()) // check if outside borders
		{
			continue;
		}

		world->clearLog();

		Organism* tileHabitant = world->GetOrganismAtTile(finalX, finalY);
		if (tileHabitant != nullptr) {
			collision(tileHabitant, finalX, finalY);
		}
		else {
			
			moveLog(finalX, finalY);
			world->MoveOrganismOnMap(this, finalX, finalY);
			setPosition(finalX, finalY);
		}
		if (burnDuration)
			BURN();
		break;
	}
}

void Human::BURN() {

	for (int i = -1;i <= 1;i++) {
		for (int j = -1;j <= 1;j++) {
			if (i == 0 && j == 0)
				continue;
			if (x + i < 0 || x + i >= world->getWidth() || y + j < 0 || y + j >= world->getHeight())
				continue;

			Organism* target = world->GetOrganismAtTile(x + i, y + j);
			if (target != nullptr) {
				world->RemoveOrganismAndFreeTile(target);
				target->getBURNED();
			}
			delete target;
		}
	}
	gotoxy(50, 50);
}

void Human::setBurnDuration(int duration) {
	burnDuration = duration;
}

void Human::setBurnCooldown(int cooldown) {
	burnCooldown = cooldown;

}

int Human::getBurnDuration() const {
	return burnDuration;
}

int Human::getBurnCooldown() const {
	return burnCooldown;
}