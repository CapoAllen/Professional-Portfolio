#include "GravityWellScene.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <MMath.h>
#include <iostream>
#include "Entity.h"

Scene2::Scene2(SDL_Window* sdlWindow_) :
	window(sdlWindow_)
	, renderer(nullptr)
	, planet(nullptr)
	, star1(nullptr)
	, star2(nullptr)
	, xAxis(30.0f)
	, yAxis(30.0f)
{

}

Scene2::~Scene2() {
	std::cout << "deleting child Scene2 class\n";
}

bool Scene2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, -1.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	// Create screen renderer
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	planet = new Entity();
	planet->pos = Vec3(10.0f, 20.0f, 0.0f);
	planet->SetImage("textures/ball.png", renderer);
	planet->mass = 1;

	star1 = new Entity();
	star1->pos = Vec3(5.0f, 10.0f, 0.0f);
	star1->SetImage("textures/star.png", renderer);
	star1->mass = 75;

	star2 = new Entity();
	star2->pos = Vec3(15.0f, 25.0f, 0.0f);
	star2->SetImage("textures/star.png", renderer);
	star2->mass = 100;

	return true;
}

void Scene2::OnDestroy() {
	// Destroy renderer
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	// Destroy objects
	delete planet;
	planet = nullptr;

	delete star1;
	star1 = nullptr;

	delete star2;
	star2 = nullptr;
}

void Scene2::HandleEvents(const SDL_Event& event) {
	switch (event.type) {

	case SDL_EVENT_KEY_DOWN:
		switch (event.key.scancode) {

		case SDL_SCANCODE_O:
			star1->angleDeg -= 10.0f;
			break;

		case SDL_SCANCODE_P:
			star2->angleDeg += 10.0f;
			break;
		case SDL_SCANCODE_S:
			stop = !stop; 
			break;


		}


	default:
		break;
	}
}

void Scene2::Update(const float deltaTime) {
	if (stop) return;

	const float G = 1.0f;

	// Step 1: vectors
	Vec3 PS1 = star1->pos - planet->pos;
	Vec3 PS2 = star2->pos - planet->pos;

	// Step 2: distances
	float r1 = sqrt((PS1.x * PS1.x) + (PS1.y * PS1.y));
	float r2 = sqrt((PS2.x * PS2.x) + (PS2.y * PS2.y));

	// Step 3: force magnitudes
	float fg1_magnitude = (G * planet->mass * star1->mass / r1);
	float fg2_magnitude = (G * planet->mass * star2->mass / r2);

	// Step 4: directions
	Vec3 fg1_direction = PS1 / r1;
	Vec3 fg2_direction = PS2 / r2;

	// Step 5: full forces
	Vec3 fg1 = fg1_magnitude * fg1_direction;
	Vec3 fg2 = fg2_magnitude * fg2_direction;

	// Step 7: total force
	Vec3 totalForce = fg1 + fg2;

	planet->ApplyForce(totalForce);
	planet->Update(deltaTime);

	
}

void Scene2::Render() const {
	SDL_RenderClear(renderer);

	//Planet
	{
		Vec3 screenCoords = projectionMatrix * planet->pos;

		SDL_FRect square;
		square.x = screenCoords.x;
		square.y = screenCoords.y;

		float scale = 0.4f;
		square.w = planet->GetSurface()->w * scale;
		square.h = planet->GetSurface()->h * scale;

		SDL_RenderTextureRotated(renderer, planet->GetTexture(),
			nullptr, &square, planet->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Star 1
	{
		Vec3 screenCoords = projectionMatrix * star1->pos;

		SDL_FRect square;
		square.x = screenCoords.x;
		square.y = screenCoords.y;

		float scale = 0.5f;
		square.w = star1->GetSurface()->w * scale;
		square.h = star1->GetSurface()->h * scale;

		SDL_RenderTextureRotated(renderer, star1->GetTexture(),
			nullptr, &square, star1->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Star 2
	{
		Vec3 screenCoords = projectionMatrix * star2->pos;

		SDL_FRect square;
		square.x = screenCoords.x;
		square.y = screenCoords.y;

		float scale = 0.5f;
		square.w = star2->GetSurface()->w * scale;
		square.h = star2->GetSurface()->h * scale;

		SDL_RenderTextureRotated(renderer, star2->GetTexture(),
			nullptr, &square, star2->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	SDL_RenderPresent(renderer);
}
