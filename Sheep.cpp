#include "Sheep.h"
#include "World.h"
//#include <conio.h>
Sheep::Sheep(int x, int y) : Animal('S',4, 4, x, y)
{
}
void Sheep::lookAtWorld() {
	std::cout <<"World looks like this: width = " << world->getWidth() << " height = "<<world->getHeight()<<" animals count: "<< world->getCount() << endl;
	if (world->GetOrganismAtTile(10, 10)) {
		cout << "I see myself"<<endl;
		//_getch();
	}
	else {
		cout << "I don't see myself";
		//_getch();
	}
}