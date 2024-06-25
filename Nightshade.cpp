#include "Nightshade.h"
#include "World.h"
#include <string>
using namespace std;
Nightshade::Nightshade(int x, int y) : Plant('%', 99, x, y) {};

void Nightshade::GetEaten(Organism* o) {
	string log;
	log += o->getSymbol();
	log.append(" ate % (deadly nightshade) and died. :(");
	world->addLog(log);

	//no organism removal here
	//special case because of deleting two organisms in one action, See animal.cpp collision()
}