#pragma once
#include "Organism.h"
class Plant : public Organism {
protected:
	bool noSpace;
public:
	Plant(char symbol, int strength,int x, int y);
	~Plant() override;

	virtual void action();
	void collision(Organism* o, int x, int y);

	void TryToGrow();
	void ExpandInNewPlace();

	void SendNewSpaceSignal();
	void SetNewSpace();
	virtual void GetEaten(Organism* o);
};