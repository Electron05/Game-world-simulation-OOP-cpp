#include "Plant.h"
class SowThisle : public Plant {
public:
    SowThisle(int posX, int posY);
    void action() override;
};