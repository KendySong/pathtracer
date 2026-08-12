#include "Sandbox.hpp"

Sandbox::Sandbox(SDL_Window* window, SDL_Renderer* renderer) : m_framebuffer(renderer)
{
	this->window = window;
	this->renderer = renderer;
	this->m_showResolution = Settings::resolution;
}

void Sandbox::clear() 
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);
	m_framebuffer.clear();
}

void Sandbox::update(float dt)
{
	
}

void Sandbox::draw()
{
	glm::vec2 fResolution = Settings::resolution;

	for (size_t y = 0; y < Settings::resolution.y; y++)
	{
		for (size_t x = 0; x < Settings::resolution.x; x++)
		{
			glm::vec3 normalized = glm::vec3(x / fResolution.x, y / fResolution.y, 0);
			
			m_framebuffer.setPixel(x, y, normalized * 255.0f);
		}
	}
}

void Sandbox::render()
{
	SDL_UpdateTexture(m_framebuffer.texture, NULL, m_framebuffer.data(), Settings::resolution.x * sizeof(std::uint32_t));
	SDL_RenderTexture(renderer, m_framebuffer.texture, nullptr, nullptr);
}

void Sandbox::gui(int fps)
{
	ImGui::Begin("Settings");
		ImGui::Text("FPS : %i", fps);

		ImGui::Separator();		
		ImGui::SetNextItemWidth(100);
		ImGui::InputInt2("Resolution", &m_showResolution.x);
		if (ImGui::Button("Apply"))
		{
			Settings::resolution  = m_showResolution;
			Settings::aspectRatio = m_showResolution.x / m_showResolution.y;
			SDL_SetRenderLogicalPresentation(renderer, Settings::resolution.x, Settings::resolution.y, SDL_LOGICAL_PRESENTATION_STRETCH);
			m_framebuffer.reset();
		}
		
	ImGui::End();
}