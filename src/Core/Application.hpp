#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl3.h>
#include <ImGui/imgui_impl_sdlrenderer3.h>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include "Timer.hpp"

class Application
{
public :
	Application();
	void run();
	
private :
	void countFramerate();
	void computeDeltaTime();

	Sandbox m_sandbox;

	SDL_Window* p_window;
	SDL_Renderer* p_renderer;

	Timer m_dtTimer;
	float m_dt;

	Timer m_fpsTimer;
	int m_fps;
	int m_renderedFPS;
};