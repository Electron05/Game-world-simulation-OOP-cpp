#include "Plant.h"
class Nightshade : public Plant {
public:
    Nightshade(int posX, int posY);
    void GetEaten(Organism* o) override;
};