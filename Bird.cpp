
#include "Bird.h"
#include "ComFunc.h"

Bird::Bird()
{
    is_falling = false;
    y_val = 0;
    x_val = 0;
    is_die = false;
    x_pos = 100;
    y_pos = 100;
}

Bird::~Bird()
{
    Free();
}

void Bird::Action(SDL_Event events, SDL_Renderer* screen)
{
    keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_DOWN]){

        if (is_falling == false)
        {
            y_val = 10;
        }
    }
    else if(keyState[SDL_SCANCODE_UP]){
        if (is_falling == false)
        {
            y_val = -10;
        }

    }
    else if(keyState[SDL_SCANCODE_LEFT]){
        if (is_falling == false)
        {
            x_val = -10;
        }
    }
    else if(keyState[SDL_SCANCODE_RIGHT]){
        if (is_falling == false)
        {
            x_val = 10;
        }
    }
    else
    {
        x_val=0;
        y_val=0;
    }
}


bool Bird::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Core::LoadImage(path, screen);
    return ret;
}

void Bird::Show(SDL_Renderer* des)
{
    Core::Render(des);
}

void Bird::Falling(SDL_Renderer* des)
{  
    rect.y += y_val;
    rect.x += x_val;
    if ((rect.y + rect.h) >= groundOfMap)
    {
        LoadImg("image//shiba-dark.png", des);
        is_falling = true;
        Ground(des);
    } 
}


void Bird::Ground(SDL_Renderer* screen)
{
    y_val = 0;
    x_val = 0;
    rect.y = groundOfMap - rect.h;
    is_die = true;
}
