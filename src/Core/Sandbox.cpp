#include "Sandbox.hpp"

Sandbox::Sandbox()
{
	m_showResolution = Settings::resolution;
}

Sandbox::Sandbox(SDL_Window* window, SDL_Renderer* renderer) : window(window), renderer(renderer)
{
	
}

void Sandbox::clear() 
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);
}

void Sandbox::update(float dt)
{

}

void Sandbox::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderLine(renderer, 0, 0, 350, 200);
}

void Sandbox::gui(int fps)
{
	ImGui::Begin("Settings");
		ImGui::Text("FPS : %i", fps);

		ImGui::Separator();
		ImGui::InputInt2("Resolution", &m_showResolution.x);
		ImGui::SameLine();
		if (ImGui::Button("Apply resolution"))
		{
			Settings::resolution = m_showResolution;
		}
	ImGui::End();
}