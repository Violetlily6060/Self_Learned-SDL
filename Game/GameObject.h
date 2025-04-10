#pragma once
#include "Game.h"

class GameObject {
public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xpos, ypos;

	SDL_Texture* objTexture;
	SDL_Rect scrRect, destRect;
};
