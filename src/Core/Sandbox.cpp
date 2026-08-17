#include "Sandbox.hpp"

Sandbox::Sandbox(SDL_Window* window, SDL_Renderer* renderer) : m_framebuffer(renderer), m_viewport(90)
{
	this->window = window;
	this->renderer = renderer;
	this->m_showResolution = Settings::iResolution;

	m_renderingTimer.stop();
	m_renderingTime = 0;

	m_viewport.position = { 0, 0, 5 };
	m_viewport.reset();

	m_sphere = Sphere({ 0, 0, 0 }, 1, { 1, 0, 0 });
	m_groundSphere = Sphere({ 0, -101, 0 }, 100, { 1, 1, 1 });

	m_world.push_back(&m_sphere);
	m_world.push_back(&m_groundSphere);
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
			//Compute pixel color between [0;1] foreach components
			glm::vec3 pixelColor = glm::vec3(0);
			if (Settings::antialiasing)
			{		
				for (size_t i = 0; i < Settings::sampleAA; i++)
				{
					Ray ray = m_viewport.generateAA(x, y);
					pixelColor += Raytracer::trace(ray, m_world, 0);
				}
				pixelColor = (pixelColor / Settings::sampleAA);
			}
			else
			{
				Ray ray = m_viewport.generate(x, y);
				pixelColor = Raytracer::trace(ray, m_world, 0);				
			}

			if (Settings::gammaCorrection)
			{
				pixelColor = Math::linearToGamma2(pixelColor);
			}

			m_framebuffer.setPixel(x, y, pixelColor * 255);
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
		ImGui::Text("FPS                 : %i", fps);
		ImGui::Text("Last rendering time : %f ms", m_renderingTime);

		//Graphics settings
		ImGui::SeparatorText("Graphics");
		ImGui::Checkbox("Continious rendering", &Settings::continiousRendering);
		if (!Settings::continiousRendering)
		{
			if (ImGui::Button("Render scene"))
			{
				m_renderingTimer.start();
				this->draw();
				m_renderingTimer.stop();
				m_renderingTime = m_renderingTimer.getElapsedTime() * 1000;
			}
		}
		ImGui::Checkbox( "Gamma correction",	&Settings::gammaCorrection);
		ImGui::Checkbox( "Antialiasing",		&Settings::antialiasing);
		ImGui::DragInt(  "Sample per pixel",	&Settings::sampleAA, 1, 1, 100);	
		ImGui::DragInt(  "Bounce limit",		&Settings::bounceLimit, 1, 1, 10);
		ImGui::DragFloat("Minimum t",			&Settings::minT, 0.01, 0, 1);	
		ImGui::SetNextItemWidth(100);



		ImGui::InputInt2("Resolution", &m_showResolution.x);
		if (ImGui::Button("Apply new resolution"))
		{
			Settings::iResolution  = m_showResolution;
			Settings::resolution   = m_showResolution;
			Settings::aspectRatio  = (float)m_showResolution.x / (float)m_showResolution.y;

			SDL_SetRenderLogicalPresentation(renderer, Settings::iResolution.x, Settings::iResolution.y, SDL_LOGICAL_PRESENTATION_STRETCH);
			m_viewport.reset();
			m_framebuffer.reset();
			this->draw();
		}	

		//Camera settings
		ImGui::SeparatorText("Camera");
		if (ImGui::DragFloat("FOV", &m_viewport.fov, 0.1, 45, 180))
		{
			m_viewport.reset();
		}

		if (ImGui::DragFloat3("Origin", &m_viewport.position.x))
		{
			m_viewport.reset();
		}

		//World settings
		ImGui::SeparatorText("World");
		ImGui::DragFloat3("Main sphere position", &m_sphere.position.x, 0.05);
		ImGui::DragFloat("Main sphere radius", &m_sphere.radius, 0.05);

		ImGui::DragFloat3("Ground position ", &m_groundSphere.position.x, 0.05);
		ImGui::DragFloat("Ground radius", &m_groundSphere.radius, 0.05);
	ImGui::End();
}