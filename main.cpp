#include "Core.h"
#include "ComFunc.h"
#include "Bird.h"
#include "Time.h"
#include "Threat.h"
#include "TextShow.h"

Core Lbackground;	
Core LLand;
Core LGameOver;
Core LMenu;
Core Smic;
Bird bird;
Threat threat[3];
TTF_Font* font_text = NULL;
TTF_Font* font_MENU = NULL;
Mix_Chunk* sound = NULL;
SDL_Rect khungbird;
SDL_Rect khungthreat[3];
TextShow text_count;

//Window
bool Init()
{
	khungbird.w=50;
	khungbird.h=35;
	khungthreat[0].w=50;
	khungthreat[1].w=50;
	khungthreat[2].w=50;
	khungthreat[0].h=38;
	khungthreat[1].h=38;
	khungthreat[2].h=38;
	bool success = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret < 0)
		return false;
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); //thiet lap che do ti le voi chat luong
	//tao cua so window
	window = SDL_CreateWindow("Dodgy Dog", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		success = false;
	}
	else
	{
		screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (screen == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor(screen, 0, 255, 0, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags)) && imgFlags)
				success = false;
		}

		if (TTF_Init() == -1)
		{
			success = false;
		}

		font_text = TTF_OpenFont("font//ARCADE.ttf", 50);
		if (font_text == NULL)
		{
			success = false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		{
			success = false;
		}
		else
		{
			sound = Mix_LoadWAV("sound//Dod.mp3");
		}


		font_MENU = TTF_OpenFont("font//ARCADE.ttf", 80);
		if (font_MENU == NULL)
		{
			return false;
		}
	}
		
	

	return success;
}
//Load Background
bool LoadBackground()
{
	bool ret = Lbackground.LoadImage("image//background-night.png", screen);
		if (ret == false)
			return false;
	return true;
}
//Load land
bool loadLand()
{
	bool ret = LLand.LoadImage("image//land - Copy.png", screen);
	if (ret == false)
		return false;
	return true;
}
//load menu
bool LoadGameOver()
{
	bool ret = LGameOver.LoadImage("image//end.jpg", screen);

	if (ret == false)
		return false;
	return true;
}
void endGameZ(int diem){
	bool checka=true;
	while (checka)
	{
		LGameOver.Render(screen, NULL);
		std::string count_str2 = std::to_string(diem);
		text_count.RenderText(screen, 180, 260);
		SDL_RenderPresent(screen);
		if (SDL_PollEvent(&event) != 0)
        {
        if (event.type == SDL_QUIT)
        {
            checka = false;
			break;
        }}
	}
	
}
bool ShowMenu()
{
    bool ret = LMenu.LoadImage("image//menu.png", screen);
    if (ret == false)
        return false;
	return true;
   
}
bool isMute = true;
bool ShowMic(){
	bool ret;
	if (isMute)
	{
		ret = Smic.LoadImage("image//soundon.png", screen);
	}else{
		ret = Smic.LoadImage("image//soundoff.png", screen);
	}
	Smic.Render(screen, NULL);
    if (ret == false)
        return false;
	return true;
}

bool loadThreat()
{
	bool ret = threat[0].LoadImage("image//shi.png", screen);
	bool ret1 = threat[1].LoadImage("image//shi.png", screen);
	bool ret2 = threat[2].LoadImage("image//shi.png", screen);
	if (ret == false && ret1 == false && ret2 == false)
		return false;
	return true;
}

void close()
{
	Lbackground.Free();
	LLand.Free();
	bird.Free();
	LGameOver.Free();
	threat->Free();

	SDL_DestroyRenderer(screen);
	screen = NULL;

	SDL_DestroyWindow(window);
	window = NULL;
    
	IMG_Quit();
	SDL_Quit();
}

// Check collision
bool checkCollision() {
	khungbird.x=bird.getXPOS();
	khungbird.y=bird.getYPOS();
	khungbird.w=bird.getWidth();	
	for (int i = 0; i < 3; i++)
	{
		khungthreat[i].x=threat[i].getXPOS();
		khungthreat[i].y=threat[i].getYPOS();
		if (SDL_HasIntersection(&khungbird, &khungthreat[i]))
		return true;	
	}
	return false;
}

int main(int argc, char* argv[])
{
	//land & background loop
	int land_x = 0;
	
	//khoi tao
	if (Init() == false)
		return -1;

	//Set fps
	Time fps;

	//Text
	TextShow text_count_;
	text_count_.SetColor(TextShow::WHITE_TEXT);
	bool is_running = true;
	//load background va khoi tao vi tri
	if (LoadBackground() == false)
		return -1;
	Lbackground.SetRect(0, -60);

	//load land va khoi tao vi tri
	if (loadLand() == false)
		return -1;
	LLand.SetRect(0, groundOfMap);

	//Load gameover
	if (LoadGameOver() == false)
		return -1;
	LGameOver.SetRect(0, 0);

	// if (ShowMenu() == false)
	// 	return -1;
	// Menu.SetRect(0, 0);
/************************************Bird***************************************/
	//load anh va khoi tao vi tri
	bool ret = bird.LoadImg("image//shiba.png", screen);
	bird.SetRect(30, 200);
	if (ret == false)
	{
		return -1;
	}

/********************************************************************************/
	//Threat: load anh va khoi tao vi tri
	if (loadThreat() == false)
		return -1;
	threat[0].SetRect(SCREEN_W, RandomPOS());
	threat[1].SetRect(SCREEN_W - 50, RandomPOS());
	threat[2].SetRect(SCREEN_W + 55, RandomPOS());

	//text
	text_count.SetColor(TextShow::WHITE_TEXT);
	//Game
	bool endgame = false;
	int up_level_count = 0; // bien tang do kho game
	
	Mix_PlayChannel(-1, sound, 0);
	
	bool iis_running = false;
	bool quit = false;	
	// Hiển thị menu
	while (!quit)
		{
			ShowMenu();
			LMenu.Render(screen, NULL);
			ShowMic();
			Smic.SetRect(SCREEN_W-32,0);
			//Smic.Render(screen, &toadomic);
			while (SDL_PollEvent(&event))
		{
			switch (event.type)
		{
			case SDL_QUIT: // Nếu nhấn nút thoát
			quit = true;
			close();
			break;
			case SDL_MOUSEBUTTONDOWN: // Nếu nhấn chuột
			int x, y;
			SDL_GetMouseState(&x, &y); // Lấy tọa độ chuột
		if (x >= 133 && x < 223 && y >= 302 && y < 346)
		{
			SDL_DestroyTexture(LMenu.GetTexture());
			iis_running = true; // Bắt đầu trò chơi
			quit = true;
		}
		if(x>=SCREEN_W-32 && x<SCREEN_W && y<=24 && y>=0 ){
			// Click vào hình ảnh loa
                isMute = !isMute; // Đảo trạng thái của loa
                if (isMute) {
					Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
					Mix_PlayChannel(-1, sound, 0);
					ShowMic();
                } else {
					 Mix_CloseAudio();
					ShowMic();
                }
		}
		break;
	
		}
	}
	SDL_RenderPresent(screen);
	}
	while (iis_running)
	{
		 fps.start(); //set fps
        if (SDL_PollEvent(&event) != 0)
        {
        if (event.type == SDL_QUIT)
        {
            is_running = false;
			break;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_x)
            {
                is_running = false;
            }
        }
			bird.Action(event, screen); // move
			
		}
		
		SDL_SetRenderDrawColor(screen, 0, 255, 0, 255);
		SDL_RenderClear(screen);

		bool is_fallling = bird.GetFalling();
		
		if (bird.getXPOS() < 0 || bird.getYPOS() < 0 || bird.getXPOS() > SCREEN_W || bird.getYPOS() > SCREEN_W)
		{
			is_running = false;
		}
		

		Lbackground.Render(screen, NULL); //dua background len man hinh

/*********************land loop******************************/

			land_x -= 2;
			LLand.SetRect(land_x, groundOfMap);
			LLand.Render(screen, NULL);
			LLand.SetRect(land_x + SCREEN_W, groundOfMap);
			LLand.Render(screen, NULL);
			if (land_x <= -SCREEN_W)
			{
				land_x = 0;
			}
		
/***************************************************************/
			

		bird.Falling(screen);

		//Threat move
		if (up_level_count <= 5)
		{
			threat[0].MoveThreat();
			threat[1].MoveThreat();
		}
		else if (up_level_count <= 8)
		{
			threat[0].MoveThreat();
			threat[1].MoveThreat();
			threat[2].MoveThreat();
			threat[0].MoveThreatLvUp();
		}
		else if (up_level_count <= 15)
		{
			threat[0].MoveThreat();
			threat[1].MoveThreat();
			threat[2].MoveThreat();
			threat[1].MoveThreatLvUp();
		}
		else
		{
			threat[0].MoveThreat();
			threat[1].MoveThreatLvUp();
			threat[1].MoveThreat();
			threat[2].MoveThreat();
			threat[2].MoveThreatLvUp();
			threat[0].MoveThreatLvUp();
		}
		if (threat[0].getXPOS() == bird.getXPOS() || threat[1].getXPOS() == bird.getXPOS() || threat[2].getXPOS() == bird.getXPOS()) {
    // Kiểm tra xem các đối tượng threat có kề nhau không
		if(up_level_count==6) up_level_count++;
    	if ((threat[0].getXPOS() == threat[1].getXPOS() + threat[1].getWidth()) ||
        	(threat[0].getXPOS() + threat[0].getWidth() == threat[1].getXPOS()) ||
        	(threat[0].getXPOS() == threat[2].getXPOS() + threat[2].getWidth()) ||
        	(threat[0].getXPOS() + threat[0].getWidth() == threat[2].getXPOS()) ||
        	(threat[1].getXPOS() == threat[2].getXPOS() + threat[2].getWidth()) ||
        	(threat[1].getXPOS() + threat[1].getWidth() == threat[2].getXPOS())) {
        	up_level_count += 2;
   	 	} else {
        up_level_count++;
    	}
}


		//Check va cham
		if (checkCollision()) {
			//std::cout << "You lose! Your score is: " << up_level_count << std::endl;
			is_running = false;
			// up_level_count = 0;
		}
		
		//Show
		bird.Show(screen);
		if (up_level_count <= 5)
		{
			threat[0].Show(screen);
			threat[1].Show(screen);
		}
		else
		{
			threat[0].Show(screen);
			threat[1].Show(screen);
			threat[2].Show(screen);

		}
		//Show game score
		int count = up_level_count;
		std::string count_str = std::to_string(count);
		text_count.SetText(count_str);
		text_count.LoadText(font_text, screen);
		text_count.RenderText(screen, SCREEN_W * 0.49, 434);
		


		if (is_running == false) {
			Mix_CloseAudio();
			endGameZ(count);
			// SDL_Delay(1000);
			Mix_FreeChunk(sound);
			break;
		}
		SDL_RenderPresent(screen);
		text_count.Free();
		//Set fps, can bang thoi gian tat ca frame
		int val1 = fps.get_ticks(); // real time
		if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) // 1000 / frame... 1 lan chay mat ? ms
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());  // delay time 
		}

	}

	Mix_FreeChunk(sound);
	Mix_CloseAudio();
	close();
	return 0;
}
