all:
	g++ -I src/include -L src/lib -o main main.cpp Core.cpp Bird.cpp ComFunc.cpp GameFunc.cpp TextShow.cpp Threat.cpp Time.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 