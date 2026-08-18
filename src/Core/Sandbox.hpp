#pragma once
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl3.h>
#include <ImGui/imgui_impl_sdlrenderer3.h>

#include <glm/glm.hpp>

#include "Timer.hpp"
#include "../Settings.hpp"
#include "../Graphics/Color.hpp"
#include "../Graphics/Framebuffer.hpp"
#include "../Graphics/Ray.hpp"
#include "../Graphics/Viewport.hpp"
#include "../Graphics/Raytracer.hpp"
#include "../Graphics/Sphere.hpp"
#include "../Graphics/Material.hpp"
#include "../Graphics/Gui/Resolution.hpp"

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
	void updateResolution();

	Viewport    m_viewport;
	FrameBuffer m_framebuffer;
	
	std::vector<Hittable*> m_world;

	Lambertian	m_mGround;
	Lambertian	m_mCenter;
	Metal		m_mLeft;
	Metal		m_mRight;

	Sphere m_groundSphere;
	Sphere m_centerSphere;
	Sphere m_leftSphere;
	Sphere m_rightSphere;

	//Settings
	glm::ivec2 m_showResolution;
	Timer m_renderingTimer;
	float m_renderingTime;
	int   m_resolutionIndex;
};