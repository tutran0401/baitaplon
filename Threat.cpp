#include "Threat.h"
int RandomPOS() {
	int minVal=0;
	 int maxVal=380;
	  int minDist=20;
    static bool initialized = false;
    if (!initialized) {
        std::srand(std::time(nullptr));
        initialized = true;
    }

    int rangeSize = maxVal - minVal;
    int dist = rangeSize / ((rangeSize / minDist) + 1);
    int randomValue = (std::rand() % (rangeSize / dist)) * dist + minVal;
    return randomValue;
}


bool Threat::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = Core::LoadImage(path, screen);
	return ret;
}

void Threat::Show(SDL_Renderer* des)
{
	Core::Render(des);
}

void Threat::MoveThreat()
{
	rect.x -= 10;
	//create random
	// std:: random_device rd;
	// std:: mt19937 gen(rd());
	// std:: uniform_int_distribution<> dis(0, 400 - THREAT_HEIGHT);
	//
	if (rect.x + THREAT_WIDTH < 0) {
		rect.x = SCREEN_W;
		int bien=RandomPOS();
		
		rect.y = bien;
	}
}

void Threat::MoveThreatLvUp()
{
	rect.x -= 5;
	// std::random_device rd;
	// std::mt19937 gen(rd());
	// std::uniform_int_distribution<> dis(0, 400 - THREAT_HEIGHT);
	if (rect.x + THREAT_WIDTH < 0) {
		rect.x = SCREEN_W;
		rect.y = RandomPOS();
	}
}

