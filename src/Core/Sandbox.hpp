#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl3.h>
#include <ImGui/imgui_impl_sdlrenderer3.h>

#include <glm/glm.hpp>

#include "../Settings.hpp"

class Sandbox
{
public :
	Sandbox();
	Sandbox(SDL_Window* window, SDL_Renderer* renderer);
	
	void clear();
	void update(float dt);
	void render();
	void gui(int fps);

	SDL_Window* window;
	SDL_Renderer* renderer;

private :
	glm::ivec2 m_showResolution;

};