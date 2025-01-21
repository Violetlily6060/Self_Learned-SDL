#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>;

SDL_Renderer* Game::renderer = nullptr;
Manager manager;
SDL_Event Game::Event;
Map* map;

SDL_Rect Game::camera = { 0, 0, 800, 640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& tenshi(manager.addEntity());
auto& label(manager.addEntity());

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised" << '\n';
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) { std::cout << "Window Created" << '\n'; }

		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
		if (renderer) {
			std::cout << "Renderer Created" << '\n';
		}

		isRunning = true;
	}
	else { isRunning = false; }

	if (TTF_Init() == -1) {
		std::cout << "ERROR : SDL_TTF" << '\n';
	}

	assets->AddTexture("terrain", "Textures/terrain_ss.png");
	assets->AddTexture("tenshi", "Textures/Tenshi.png");
	assets->AddTexture("Projectile", "Textures/bullet.png");
	assets->AddFont("arial", "Textures/ARLRDBD.TTF", 16);

	map = new Map("terrain", 3, 32);
	map->LoadMap("Textures/map.map", 25, 20);

	tenshi.addComponent<TransformComponent>(0.7);
	tenshi.addComponent<SpriteComponent>("tenshi", true);
	tenshi.addComponent<KeyboardController>();
	tenshi.addComponent<ColliderComponent>("tenshi");
	tenshi.addGroup(groupPlayers);

	SDL_Color white = { 255, 255 ,255, 255 };
	label.addComponent<UILabel>(10, 10, "Testing", "arial", white);

	assets->CreateProjectile(Vector2D(600, 600), Vector2D(1, 0), 200, 2, "Projectile");
	assets->CreateProjectile(Vector2D(620, 600), Vector2D(1, 1), 200, 2, "Projectile");
	assets->CreateProjectile(Vector2D(640, 600), Vector2D(1, 1), 200, 2, "Projectile");
	assets->CreateProjectile(Vector2D(660, 600), Vector2D(0, 1), 200, 2, "Projectile");
	assets->CreateProjectile(Vector2D(670, 600), Vector2D(1, 0), 200, 2, "Projectile");
	assets->CreateProjectile(Vector2D(680, 600), Vector2D(0, 1), 200, 2, "Projectile");
	assets->CreateProjectile(Vector2D(690, 600), Vector2D(1, 1), 200, 2, "Projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents() {
	
	SDL_PollEvent(&Event);

	switch (Event.type) {
		case SDL_QUIT: {
			isRunning = false;
			break;
		}

		default:
			break;
	}
}

void Game::update() {
	SDL_Rect tenshiCol = tenshi.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = tenshi.getComponent<TransformComponent>().position;

	std::stringstream ss;
	ss << "Player position: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, tenshiCol)) {
			tenshi.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles) {
		SDL_Rect pCol = p->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(pCol, tenshiCol)) {
			p->destroy();
			std::cout << "Tenshi hit" << '\n';
		}
	}

	camera.x = tenshi.getComponent<TransformComponent>().position.x - 400;
	camera.y = tenshi.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0) {
		camera.x = 0;
	}

	if (camera.y < 0) {
		camera.y = 0;
	}

	if (camera.x > camera.w) {
		camera.x = camera.w;
	}

	if (camera.y > camera.h) {
		camera.y = camera.h;
	}
}



void Game::render() {
	SDL_RenderClear(renderer);

	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& c : colliders) {
		c->draw();
	}

	for (auto& p : projectiles) {
		p->draw();
	}

	for (auto& p : players) {
		p->draw();
	}

	label.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << '\n';
}