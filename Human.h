#include "Animal.h"
#include <iostream>
class Human : public Animal {
private:
    int burnDuration, burnCooldown;
public:
    Human(int posX, int posY);
    void action() override;

    int getBurnDuration() const;
    int getBurnCooldown() const;

    void setBurnDuration(int duration);
    void setBurnCooldown(int cooldown);
private:
    void BURN();
};