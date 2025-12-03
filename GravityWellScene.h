#ifndef SCENE2_H
#define SCENE2_H
#include <SDL.h>
#include <Matrix.h>
#include "Scene.h"
#include "Entity.h"
#include <SDL3/SDL.h>

using namespace MATH;
class Scene2 : public Scene {
private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	Entity* planet;
	Entity* star1;
	Entity* star2;
	SDL_Renderer* renderer;
	float xAxis;
	float yAxis;
	bool stop = false;
public:
	Scene2(SDL_Window* sdlWindow);
	~Scene2();
	bool OnCreate() override;
	void OnDestroy() override;
	void HandleEvents(const SDL_Event& event) override;
	void Update(const float time) override;
	void Render() const override;
};

#endif

	#pragma once
