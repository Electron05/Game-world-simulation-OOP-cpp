#include "SowThisle.h"
#include "World.h"
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
SowThisle::SowThisle(int x, int y) : Plant('@', 0, x, y) {
	std::srand(time(0));
};

void SowThisle::action() {
	increaseAge();
	if (noSpace) {
		return;
	}
	for (int i = 0;i < 3;i++) {
		int roll = 1 + rand() % 1000;
		if (roll == 1000) {
			ExpandInNewPlace();
		}

		if (roll > 13)
			continue;
		TryToGrow();
	}
}