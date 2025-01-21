#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent *transform;
	SpriteComponent *sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::Event.type == SDL_KEYDOWN) {
			switch (Game::Event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = -1;
				break;

			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("Forward");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;

			case SDLK_s:
				transform->velocity.y = 1;
				break;

			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("Forward");
				break;

			default:
				break;
			}
		}
		if (Game::Event.type == SDL_KEYUP) {
			switch (Game::Event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = 0;
				break;

			case SDLK_a:
				transform->velocity.x = 0;
				sprite->spriteFlip = SDL_FLIP_NONE;
				sprite->Play("Idle");
				break;

			case SDLK_s:
				transform->velocity.y = 0;
				break;

			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;

			case SDLK_ESCAPE:
				Game::isRunning = false;

			default:
				break;
			}
		}
	}
};