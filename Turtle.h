#include "Animal.h"
#include <iostream>
class Turtle : public Animal {
public:
    Turtle(int posX, int posY);
    void action() override;
};