#include "GameObject.h"
#include "TextureManager.h"
#include <ctime>
#include <Windows.h>

int direction;
int cycle;

GameObject::GameObject(const char* textureSheet, int x, int y) {
	objTexture = TextureManager::LoadTexture(textureSheet);
	xpos = x;
	ypos = y;
	cycle = 0;

	srand(time(NULL));
}

void GameObject::Update() {
	scrRect.h = 60;
	scrRect.w = 60;
	scrRect.x = 0;
	scrRect.y = 0;

	if (cycle = 0) {
		direction += 1;
		cycle = 1;
	}

	if (cycle = 1) {
		direction += 2;
		cycle = 2;
	}

	if (cycle = 2) {
		direction += 3;
		cycle = 0;
	}

	direction = (direction + rand()) % 4;

	if (direction == 0 && xpos != 1200) {
		xpos++;
	}

	if (direction == 1 && xpos != 0) {
		xpos--;
	}

	if (direction == 2 && ypos != 660) {
		ypos++;
	}

	if (direction == 3 && ypos != 0) {
		ypos--;
	}

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = scrRect.h;
	destRect.w = scrRect.w;
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &scrRect, &destRect);
}