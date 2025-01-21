#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;
	int speed = 3;
	int height = 175;
	int width = 97;
	float scale = 0.1;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(float sc) {
		position.x = 800;
		position.y = 500;
		scale = sc;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};