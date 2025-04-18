#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>

class ColliderComponent;
class AssetManager;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }


	static SDL_Renderer* renderer;
	static SDL_Event Event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;

	enum groupLables : std::size_t {
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};

private:
	SDL_Window* window;
};