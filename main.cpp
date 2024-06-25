#include <iostream>
#include <cstdlib>
#include <stdlib.h> 
#include "World.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <conio.h>
#include "consoleUtils.h"

#define MAX_WORLD_WIDTH 90
#define MAX_WORLD_HEIGHT 40
#define WARNING_HEIGHT 27

using namespace std;





int main()
{
	int x, y, accept;
	char mode = ' ';
	World* w;

	changeCursorVisibility(false);
	
	cout << "Welcome to world simulation!" << endl;
	cout << "1. New Game" << endl;
	cout << "2. Load Game" << endl;

	while (true) {
		mode = _getch();
		if (mode == '1') {
			changeCursorVisibility(true);

			while (true) {
				cout << "Enter world width: ";
				cin >> x;
				while (x > MAX_WORLD_WIDTH) {
					cout << "Width cannot exceed " << MAX_WORLD_WIDTH << "!" << endl << "Enter world width : ";
					cin >> x;
				}
				cout << "Enter world height: ";
				cin >> y;
				while (y > MAX_WORLD_HEIGHT) {
					cout << "Height cannot exceed " << MAX_WORLD_HEIGHT << "!" << endl << "Enter world height : ";
					cin >> y;
				}
				if (x * y < 25)
					cout << "World minimum size is 25 tiles, Enter bigger map." << endl;
				else
					break;
			}

			if (y > WARNING_HEIGHT) {
				cout << "World height is above " << WARNING_HEIGHT<<". Please make sure you are in fullscreen console before going further.";
				accept = _getch();
			}
			changeCursorVisibility(false);
			w = World::getInstance(x, y);
			w->DrawWorld();
			w->StartingPopulation();
			break;
		}
		if (mode == '2') {
			ifstream save;
			save.open("save.txt");
			save >> x;
			save >> y;
			if (y > WARNING_HEIGHT) {
				cout << "World height is above " << WARNING_HEIGHT << ". Please make sure you are in fullscreen console before going further.";
				accept = _getch();
			}
			w = World::getInstance(x, y);
			w->TriggerLoadSkipping();
			w->DrawWorld();
			w->ReadSave();
			break;
		}
	}



	while (!w->IsGameOver()) {
		w->ProcessTurn();

	}
	w->printLog();
	w->PrintOrganismCount();
	gotoxy(0, y + 4);
	w->ClearMemory();
	//w->printLog();
	changeCursorVisibility(true);
	return 0;
}