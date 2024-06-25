#include "Animal.h"
#include <iostream>
class Antilope : public Animal {
public:
    Antilope(int posX, int posY);
    void action() override;
};