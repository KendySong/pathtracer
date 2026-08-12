#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl3.h>
#include <ImGui/imgui_impl_sdlrenderer3.h>

#include <glm/glm.hpp>

#include "../Settings.hpp"
#include "../Graphics/Color.hpp"
#include "../Graphics/Framebuffer.hpp"
#include "../Graphics/Ray.hpp"

class Sandbox
{
public :
	Sandbox(SDL_Window* window, SDL_Renderer* renderer);
	
	void clear();
	void update(float dt);
	void draw();
	void render();
	void gui(int fps);

	SDL_Window* window;
	SDL_Renderer* renderer;

private :
	glm::ivec2 m_showResolution;

	FrameBuffer m_framebuffer;
};