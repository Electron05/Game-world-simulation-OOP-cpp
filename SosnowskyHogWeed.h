#include "Plant.h"
class SosnowskyHogWeed : public Plant {
public:
    SosnowskyHogWeed(int posX, int posY);
    void action() override;
    void GetEaten(Organism* o) override;
private:
    void killNeighbours();
};