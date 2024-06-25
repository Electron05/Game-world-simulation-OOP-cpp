#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
    Animal(char symbol, int strength, int initiative, int x, int y);
    virtual void action();
protected:
    virtual void collision(Organism* o, int x, int y);
    void breed();
    void moveLog(int finalX, int finalY);
};
