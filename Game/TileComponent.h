#pragma once
#include "Vector2D.h"
#include "TextureManager.h"
#include "Game.h"

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect scrRect, destRect;
	Vector2D position;
	TileComponent() = default;
	
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int scrX, int scrY, int xpos, int ypos, int tsize, int tscale, std::string id) {
		texture = Game::assets->GetTexture(id);
		position.x = xpos;
		position.y = ypos;

		scrRect.x = scrX;
		scrRect.y = scrY;
		scrRect.w = scrRect.h = tsize;
		
		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale;
	}

	void update() override {
		destRect.x = static_cast<int>(position.x - Game::camera.x);
		destRect.y = static_cast<int>(position.y - Game::camera.y);
	}

	void draw() override {
		TextureManager::Draw(texture, scrRect, destRect, SDL_FLIP_NONE);
	}
};