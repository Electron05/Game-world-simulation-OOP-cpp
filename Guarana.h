#include "Plant.h"
class Guarana : public Plant {
public:
    Guarana(int posX, int posY);
    void GetEaten(Organism* o) override;
};