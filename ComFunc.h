#pragma once    
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <random>
#include <string>
static SDL_Window* window = NULL;
static SDL_Renderer* screen = NULL;
static SDL_Event event;

//Screen
const int SCREEN_W = 350;
const int SCREEN_H = 485;
//const int SCREEN_BPP = 32;

#define groundOfMap 400
#define bird_w 50
#define bird_h 35
#define FRAMES_PER_SECOND 30
const int THREAT_HEIGHT = 50;
const int THREAT_WIDTH = 38;
const int THREAT_SPEED = 5;

