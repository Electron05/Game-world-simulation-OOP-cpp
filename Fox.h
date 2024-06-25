#include "Animal.h"
#include <iostream>
class Fox : public Animal {
public:
    Fox(int posX, int posY);
    void action() override;
};