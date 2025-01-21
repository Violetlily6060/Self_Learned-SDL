#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "AssetManager.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect scrRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(std::string id) {
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated) {
		animated = isAnimated;

		Animation idle = Animation(0, 10, 100);
		Animation forward = Animation(1, 4, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Forward", forward);

		Play("Idle");
		setTex(id);
	}

	~SpriteComponent() {}

	void setTex(std::string id) {
		texture = Game::assets->GetTexture(id);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		scrRect.x = scrRect.y = 0;
		scrRect.w = transform->width;
		scrRect.h = transform->height;
	}

	void update() override {
		if (animated) {
			scrRect.x = scrRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		scrRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = static_cast<int>(transform->width * transform->scale);
		destRect.h = static_cast<int>(transform->height * transform->scale);
	}

	void draw() override {
		TextureManager::Draw(texture, scrRect, destRect, spriteFlip);
	}

	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};