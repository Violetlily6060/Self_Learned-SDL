#pragma once
#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* texture);
	static void Draw(SDL_Texture* tex, SDL_Rect scr, SDL_Rect dest, SDL_RendererFlip flip);
};