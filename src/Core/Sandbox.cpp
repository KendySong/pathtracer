#include "Sandbox.hpp"

Sandbox::Sandbox(SDL_Window* window, SDL_Renderer* renderer) : m_framebuffer(renderer), m_viewport(90)
{
	this->window		= window;
	this->renderer		= renderer;
	this->m_sampleIndex = 7;

	m_renderingTimer.stop();
	m_renderingTime = 0;
	
	//Resolution and viewport
	this->m_resolutionIndex = 4;
	Settings::iResolution	= Resolution::getFromIndex(m_resolutionIndex);
	Settings::resolution	= Settings::iResolution;
	this->m_showResolution	= Settings::iResolution;
	this->updateResolution();

	m_viewport.position = { 0, 0, 1 };
	m_viewport.reset();
	
	//Materials and world
	m_mGround = Lambertian({ 0.8, 0.8, 0.0 });
	m_mCenter = Lambertian({ 0.1, 0.2, 0.5 });
	m_mLeft   = Metal({ 0.8, 0.8, 0.8 }, 0.3);
	m_mRight  = Dieletric(1.0 / 1.33);

	m_groundSphere  = Sphere({ 0, -100.5, -1 },  100,  &m_mGround);
	m_centerSphere  = Sphere({ 0, 0.0, -1.2 },  0.5,   &m_mCenter);
	m_leftSphere	= Sphere({ -1.0, 0.0, -1.0 }, 0.5, &m_mLeft);
	m_rightSphere	= Sphere({ 1.0, 0.0, -1.0 }, 0.5,  &m_mRight);

	m_world.push_back(&m_groundSphere);
	m_world.push_back(&m_centerSphere);
	m_world.push_back(&m_leftSphere);
	m_world.push_back(&m_rightSphere);
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


		if (ImGui::BeginCombo("Sample per pixel", Sample::quantity[m_sampleIndex]))
		{
			for (size_t i = 0; i < Sample::size; i++)
			{
				bool selected = i == m_sampleIndex;
				if (ImGui::Selectable(Sample::quantity[i], selected))
				{
					m_sampleIndex = i;
					Settings::sampleAA = std::stoi(Sample::quantity[i]);
				}

				if (selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		ImGui::DragInt(  "Bounce limit",		&Settings::bounceLimit, 1, 1, 10);
		ImGui::DragFloat("Minimum t",			&Settings::minT, 0.01, 0, 1);	
		ImGui::SetNextItemWidth(100);

		if (ImGui::BeginCombo("Resolutions", Resolution::format[m_resolutionIndex]))
		{
			for (size_t i = 0; i < Resolution::size; i++)
			{
				bool selected = i == m_resolutionIndex;
				if (ImGui::Selectable(Resolution::format[i], selected))
				{
					m_resolutionIndex = i;
					m_showResolution = Resolution::getFromIndex(i);
				}

				if (selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		if (ImGui::Button("Apply new resolution"))
		{
			this->updateResolution();
			this->draw();
		}	

		//Camera settings
		ImGui::SeparatorText("Camera");
		if (ImGui::DragFloat("FOV", &m_viewport.fov, 0.1, 45, 180))
		{
			m_viewport.reset();
		}

		if (ImGui::DragFloat3("Origin", &m_viewport.position.x, 0.01))
		{
			m_viewport.reset();
		}

		//World settings
		ImGui::SeparatorText("World");
		ImGui::DragFloat3("1", &m_leftSphere.position.x,  0.01);
		ImGui::DragFloat3("2", &m_rightSphere.position.x, 0.01);

		if (ImGui::TreeNode("Materials"))
		{
			ImGui::DragFloat3("Metallic left", &m_mLeft.albedo.x, 0.01, 0, 1);
			ImGui::DragFloat("Fuzz left", &m_mLeft.fuzz, 0.01, 0, 10);
			ImGui::DragFloat("Refraction index", &m_mRight.refractionIndex, 0.01, 0.0, 3);
			ImGui::TreePop();
		}
	ImGui::End();
}

void Sandbox::updateResolution()
{
	Settings::iResolution = m_showResolution;
	Settings::resolution = m_showResolution;
	Settings::aspectRatio = (float)m_showResolution.x / (float)m_showResolution.y;

	SDL_SetRenderLogicalPresentation(renderer, Settings::iResolution.x, Settings::iResolution.y, SDL_LOGICAL_PRESENTATION_STRETCH);
	m_viewport.reset();
	m_framebuffer.reset();
}