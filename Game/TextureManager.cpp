#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* objTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	SDL_SetTextureColorMod(objTexture, 255, 0, 255);

	return objTexture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect scr, SDL_Rect dest, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, tex, &scr, &dest, NULL, NULL, flip);
}