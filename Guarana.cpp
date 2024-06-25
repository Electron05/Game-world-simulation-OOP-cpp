#include "Guarana.h"
#include "World.h"
#include <string>
using namespace std;
Guarana::Guarana(int x, int y) : Plant('&', 0, x, y) {};

void Guarana::GetEaten(Organism* o) {
	o->setStrength(o->getStrength() + 3);

	string log;
	log += o->getSymbol();
	log.append(" ate & and gained 3 strength points!");
	world->addLog(log);
	log.clear();
	log.append("It has ");
	log += to_string(o->getStrength());
	log.append(" strength points!");
	world->addLog(log);

}