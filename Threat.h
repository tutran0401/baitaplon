#pragma once

#include "ComFunc.h"
#include "Core.h"

class Threat : public Core
{
public:
	void MoveThreat();

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void MoveThreatLvUp();
private:
	
};
	int RandomPOS();