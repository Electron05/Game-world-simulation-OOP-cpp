#pragma once
#include "Organism.h"
#include <vector>
#include <string>
using namespace std;
class World
{
private:
	int width, height;
	int turn;
	bool isGameOver, isLoadingToHuman; //when loaded skip turns so player returns to point when he stopped

	World(int width, int height);
	static World* instance;

	vector<Organism*> organisms; //used to iterate organisms so each one makes an action
	Organism*** organismsMap; //used to quickly check if destination square is free (during movement)

	int curr_turn_iterration;
	size_t iterationsAdjustments;
	Organism* OrganismToDelete;

	vector<string> log;

public:

	int getWidth() { return width; };
	int getHeight() { return height; };
	size_t getCount() { return organisms.size(); };

	static World* getInstance();
	static World* getInstance(int szerokosc, int wysokosc);

	void MoveOrganismOnMap(Organism* o,int finalX,int finalY);
	void RemoveFromMap(Organism* o);

	void StartingPopulation();

	void AddOrganism(Organism* o);
	void RemoveOrganismAndFreeTile(Organism* o);
	void ClearMemory();


	void ProcessTurn();
	void DrawWorld();
	void DrawFrame();

	void PrintOrganismCount();

	void addLog(string msg);
	void printLog();
	void clearLog();
	void TriggerGameOver();
	bool IsGameOver();

	void SetOrganismToDelete(Organism* o);
	Organism* GetOrganismAtTile(int x,int y);


	void ReadSave();
	void WriteSave();

	void TriggerLoadSkipping();
	void EndLoadSkipping();
	bool IsLoadSkipping();
	~World();
};