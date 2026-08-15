#include "Sandbox.hpp"

Sandbox::Sandbox(SDL_Window* window, SDL_Renderer* renderer) : m_framebuffer(renderer), m_viewport(90)
{
	this->window = window;
	this->renderer = renderer;
	this->m_showResolution = Settings::iResolution;








	m_sphere = Sphere({0, 0, -5}, 2);
	m_sphere.color = { 1, 0, 0 };
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
	for (size_t y = 0; y < Settings::iResolution.y; y++)
	{
		for (size_t x = 0; x < Settings::iResolution.x; x++)
		{
			//glm::vec3 coord = glm::vec3(x / Settings::resolution.x, y / Settings::resolution.y, 0);
			Ray ray = m_viewport.generate(x, y);

			m_framebuffer.setPixel(x, y, Raytracer::trace(ray, m_sphere) * 255);
		}
	}
}

void Sandbox::render()
{
	SDL_UpdateTexture(m_framebuffer.texture, NULL, m_framebuffer.data(), Settings::iResolution.x * sizeof(std::uint32_t));
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
			Settings::iResolution  = m_showResolution;
			Settings::resolution   = m_showResolution;
			Settings::aspectRatio  = (float)m_showResolution.x / (float)m_showResolution.y;

			SDL_SetRenderLogicalPresentation(renderer, Settings::iResolution.x, Settings::iResolution.y, SDL_LOGICAL_PRESENTATION_STRETCH);
			m_viewport.reset();
			m_framebuffer.reset();
		}	

		if (ImGui::DragFloat("FOV", &m_viewport.fov, 0.1, 45, 180))
		{
			m_viewport.reset();
		}
		ImGui::DragFloat3("Position", &m_sphere.position.x, 0.05);

	ImGui::End();
}