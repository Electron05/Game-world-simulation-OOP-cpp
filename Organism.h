#pragma once

class World; //forward declaration, #include "World.h" does not work because of circullar dependency

class Organism {
protected:
    int strength, initiative, age;
    int x, y;
    char symbol;

    World* world;

public:
    Organism(char symbol, int strength, int initiative, int x, int y);
    virtual ~Organism();
    void fixPositionOnMap();

    void getBURNED();

    int getStrength() const;
    int getInitiative() const;
    int getX() const;
    int getY() const;
    char getSymbol() const;
    int getAge() const;

    void increaseAge();

    virtual void action() = 0;
    virtual void collision(Organism* o, int x, int y) = 0;

    void setPosition(int newX, int newY);
    void setStrength(int newStrength);

    void drawOnWorld();
    void eraseFromWorld();
};