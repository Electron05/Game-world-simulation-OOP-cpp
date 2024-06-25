#include "World.h"
#include <iostream>
#include <string>
#include "consoleUtils.h"


#include "Sheep.h"
#include "Wolf.h"
#include "Grass.h"
#include "Guarana.h"
#include "SowThisle.h"
#include "Nightshade.h"
#include "SosnowskyHogWeed.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antilope.h"
#include "Human.h"

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <conio.h>
World* World::instance = nullptr; //Singleton pattern (private constructor, always one instance)

vector<string> splitStringBySpaces(const string& input) {
    vector<string> tokens;
    istringstream iss(input);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}


World::World(int width, int height) : width(width), height(height) {
    srand(time(0));
    turn = 0;
    curr_turn_iterration = 0;
    OrganismToDelete = nullptr;
    iterationsAdjustments = 0;
    isGameOver = false;
    isLoadingToHuman = false;
    organismsMap = new Organism **[width];
    for (int i = 0; i < width; ++i) {
        organismsMap[i] = new Organism*[height];
        for (int j = 0; j < height; ++j) {
            organismsMap[i][j] = nullptr; 
        }
    }
};

World* World::getInstance(int width, int height) {
    instance = new World(width, height);
    return instance;
}

World* World::getInstance() {
    if (!instance) {
        cout << "Error! Asked for instance before setting it!" << endl;
    }
    return instance;
}

void World::StartingPopulation() {
    new Human(0, 0);
    int numOrganisms = 2;
    enum OrganismType { WOLF, SHEEP, TURTLE, FOX, ANTELOPE, GRASS, GUARANA, NIGHTSHADE, SOSNOWSKY_HOGWEED, SOW_THISLE };
    for (int i = 0; i < numOrganisms; i++) {
        for (int organismType = WOLF; organismType <= SOW_THISLE; organismType++) {
            int finalX = 1, finalY = 1;
            do {
                finalX = rand() % width;
                finalY = rand() % height;
            } while (GetOrganismAtTile(finalX, finalY) != nullptr);
            Organism* newOrganism = nullptr;
            switch (organismType) {
            case WOLF:
                newOrganism = new Wolf(finalX, finalY);
                break;
            case SHEEP:
                newOrganism = new Sheep(finalX, finalY);
                break;
            case TURTLE:
                newOrganism = new Turtle(finalX, finalY);
                break;
            case FOX:
                newOrganism = new Fox(finalX, finalY);
                break;
            case ANTELOPE:
                newOrganism = new Antilope(finalX, finalY);
                break;
            case GRASS:
                newOrganism = new Grass(finalX, finalY);
                break;
            case GUARANA:
                newOrganism = new Guarana(finalX, finalY);
                break;
            case NIGHTSHADE:
                newOrganism = new Nightshade(finalX, finalY);
                break;
            case SOSNOWSKY_HOGWEED:
                newOrganism = new SosnowskyHogWeed(finalX, finalY);
                break;
            case SOW_THISLE:
                newOrganism = new SowThisle(finalX, finalY);
                break;
            default:
                break;
            }
            newOrganism->fixPositionOnMap();
        }
    }
    //_getch();
}

void World::MoveOrganismOnMap(Organism* o,int finalX,int finalY) {
    organismsMap[o->getX()][o->getY()] = nullptr;
    organismsMap[finalX][finalY] = o;
}

void World::RemoveFromMap(Organism* o) {
    organismsMap[o->getX()][o->getY()] = nullptr;
}

void World::AddOrganism(Organism* o) {
    int s = organisms.size();
    iterationsAdjustments++;
    for (int i = 0;i < s;i++) {
        if (organisms[s - 1 - i]->getInitiative() >= o->getInitiative()) {
            organisms.insert(organisms.end() - i, o);
            organismsMap[o->getX()][o->getY()] = o;
            gotoxy(100, 41);
            return;
        }
    }
    organisms.insert(organisms.begin(),o);
    organismsMap[o->getX()][o->getY()] = o;
    gotoxy(100, 41);
}

void World::RemoveOrganismAndFreeTile(Organism* o) {

    o->eraseFromWorld();
    RemoveFromMap(o);
    auto it = std::find(organisms.begin(), organisms.end(), o);

    if (it != organisms.end()) {
        size_t index = std::distance(organisms.begin(), it);

        organisms.erase(it);

        iterationsAdjustments--;
        if (index <= curr_turn_iterration) {
            curr_turn_iterration--;
        }
    }
}

void World::ProcessTurn() {
    turn++;
    iterationsAdjustments = 0;
    int s = organisms.size();

    //The program will break if the organism generates another organism with greater initiative
    //For example if wolf somehow will manage to generate fox

    for (curr_turn_iterration = 0;curr_turn_iterration < s + iterationsAdjustments;curr_turn_iterration++) {

        if (isLoadingToHuman) {
            if (organisms[curr_turn_iterration]->getSymbol() != 'H')
                continue;
        }

        if (organisms[curr_turn_iterration]->getAge() == 0) {
            //Organism was spawned this turn, this means we ignore it and increase number of organisms to iterate
            organisms[curr_turn_iterration]->increaseAge();
            continue;
        }
        organisms[curr_turn_iterration]->action();
        
        /*
        gotoxy(0, height + 2);
        cout << "                 ";
        gotoxy(0, height + 2);
        cout << s + iterationsAdjustments << " " << curr_turn_iterration;
        */

        if (OrganismToDelete != nullptr) {
            //Safe place to release memory
            delete OrganismToDelete;
            OrganismToDelete = nullptr;
        }

        if (isLoadingToHuman)
            EndLoadSkipping();

        if (isGameOver) {
            break;
        }
    }
}

void World::DrawFrame() {
    gotoxy(0, 0);
    cout << "+";
    gotoxy(width,0);
    cout << "+";
    cout << "+";
    for (int i = 0;i < width;i++) {
        gotoxy(1 + i, 0);
        cout << "-";
        gotoxy(1 + i, height+1);
        cout << "-";
    }
    for (int i = 0; i < height;i++) {
        gotoxy(0, 1 + i);
        cout << "|";
        gotoxy(width + 1, 1 + i);
        cout << "|";
    }
    gotoxy(0, height+1);
    cout << "+";
    gotoxy(width + 1, height+1);
    cout << "+";
}

void World::DrawWorld() {
    clrscr();
    DrawFrame();

    gotoxy(0, height + 3);
}

Organism* World::GetOrganismAtTile(int x, int y) {
    return (organismsMap[x][y]) ;
}

void World::PrintOrganismCount() {
    gotoxy(0, height + 3);
    cout << "                     ";
    gotoxy(0, height + 3);
    cout << "Organisms count: " << organisms.size();
}

void World::addLog(string msg) {
    log.push_back(msg);
}

void World::printLog() {

    for (size_t i = 0; i < log.size(); i++) {
        gotoxy(width + 2, i);
        if (i == height+1) {
            cout << "And " << log.size()-height <<" more";
            break;
        }
        cout << log[i];
        continue;
    }
}

void World::clearLog(){
    for (size_t i = 0; i < log.size(); i++) {
        gotoxy(width + 2, i);
        cout << "                                                              ";
        if (i == height+1)
            break;
    }
    log.clear();
}

void World::ClearMemory() {
    int s = organisms.size();
    for(int i=0;i<s;i++) {
        delete organisms[i];
    }
}

void World::TriggerGameOver() {
    isGameOver = true;
}

bool World::IsGameOver() {
    return isGameOver;
}

void World::SetOrganismToDelete(Organism* o) {
    OrganismToDelete = o;
}

void World::ReadSave() {
    string line;
    ifstream save;
    save.open("save.txt");
    while (getline(save, line)) {
        vector<string> tokens = splitStringBySpaces(line);

        if (tokens.size() > 2) {
            Organism* a = nullptr;
            Human* h = nullptr;
            switch (tokens[2][0]) {
                // Animals
            case 'A':
                a = new Antilope(stoi(tokens[0]), stoi(tokens[1]));
                a->setStrength(stoi(tokens[3]));
                break;
            case 'F':
                a = new Fox(stoi(tokens[0]), stoi(tokens[1]));
                a->setStrength(stoi(tokens[3]));
                break;
            case 'H':
                a = new Human(stoi(tokens[0]), stoi(tokens[1]));
                a->setStrength(stoi(tokens[3]));
                h = dynamic_cast<Human*>(a);
                h->setBurnDuration(stoi(tokens[4]));
                h->setBurnCooldown(stoi(tokens[5]));
                break;
            case 'T':
                a = new Turtle(stoi(tokens[0]), stoi(tokens[1]));
                a->setStrength(stoi(tokens[3]));
                break;
            case 'W':
                a = new Wolf(stoi(tokens[0]), stoi(tokens[1]));
                a->setStrength(stoi(tokens[3]));
                break;
            case 'S':
                a = new Sheep(stoi(tokens[0]), stoi(tokens[1]));
                a->setStrength(stoi(tokens[3]));
                break;
                // Plants
            case '#':
                a = new Grass(stoi(tokens[0]), stoi(tokens[1]));
                break;
            case '&':
                a = new Guarana(stoi(tokens[0]), stoi(tokens[1]));
                break;
            case '%':
                a = new Nightshade(stoi(tokens[0]), stoi(tokens[1]));
                break;
            case '!':
                a = new SosnowskyHogWeed(stoi(tokens[0]), stoi(tokens[1]));
                break;
            case '@':
                a = new SowThisle(stoi(tokens[0]), stoi(tokens[1]));
                break;
            default:
                cout << "Unrecognized organism in save file." << endl;
            }
            a->increaseAge();

        }
    }
}

void World::WriteSave() {
    ofstream save("save.txt");
    save << width << " " << height << endl;
    for (Organism* o : organisms) {
        save << o->getX() << " " << o->getY() << " " << o->getSymbol();
        Human* humanPtr = dynamic_cast<Human*>(o);
        if (humanPtr) {
            save << " " << o->getStrength() << " " << humanPtr->getBurnDuration() << " " << humanPtr->getBurnCooldown() << endl;
            continue;
        }
        Animal* animalPtr = dynamic_cast<Animal*>(o);
        if (animalPtr) {
            save <<" " << o->getStrength();
        }
        save << endl;
    }
    save.close();
}

void World::TriggerLoadSkipping() {
    isLoadingToHuman = true;
}

void World::EndLoadSkipping() {
    isLoadingToHuman = false;
}

bool World::IsLoadSkipping() {
    return isLoadingToHuman;
}

World::~World() {

}