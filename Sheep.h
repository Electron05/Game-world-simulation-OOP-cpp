#include "Animal.h"
#include <iostream>
class Sheep : public Animal {
public:
    Sheep(int posX, int posY);

    void lookAtWorld();
};