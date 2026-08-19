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


	/*
	m_viewport.position = { 13, 2,  3 };
	m_viewport.lookAt = { 0, 0, 0 };
	m_viewport.fov = 20;
	m_viewport.reset();

	Lambertian* groundm = new Lambertian({ 0.5, 0.5, 0.5 });
	Sphere* ground = new Sphere({ 0, -1000, 0 }, 1000, groundm);
	m_world.push_back(ground);

	for (int a = -5; a < 5; a++)
	{
		for (int b = -5; b < 5; b++)
		{
			float chooseMat = Math::random();
			glm::vec3 center(a + 0.9 * Math::random(), 0.2, b + 0.9 * Math::random());

			if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9)
			{
				Material* material;
				if (chooseMat < 0.8)
				{
					//Diffuse
					glm::vec3 albedo = Math::randomv() * Math::randomv();
					material = new Lambertian(albedo);
					Sphere* sphere = new Sphere(center, 0.2, material);
					m_world.push_back(sphere);
				}
				else if (chooseMat < 0.95) 
				{
					//Metal
					glm::vec3 albedo = Math::randomv(0.5, 1.0);
					float fuzz = Math::random(0.0, 0.5);
					material = new Metal(albedo, fuzz);
					Sphere* sphere = new Sphere(center, 0.2, material);
					m_world.push_back(sphere);
				}
				else 
				{
					//Glass
					material = new Dieletric(1.5);
					Sphere* sphere = new Sphere(center, 0.2, material);
					m_world.push_back(sphere);
				}
			}
		}
	}

	Material* mat11 = new Dieletric(1.5);
	Sphere* sphere11 = new Sphere({0, 1, 0}, 1.0, mat11);
	m_world.push_back(sphere11);

	Material* mat12 = new Lambertian({ 0.4, 0.2, 0.1 });
	Sphere* sphere12 = new Sphere({ -4, 1, 0 }, 1.0, mat12);
	m_world.push_back(sphere12);

	Material* mat13 = new Metal({ 0.7, 0.6, 0.5 }, 0.0);
	Sphere* sphere13 = new Sphere({ 4, 1, 0 }, 1.0, mat13);
	m_world.push_back(sphere13);
	
	m_world.push_back(sphere11);
	*/

	m_viewport.position = { 0, 0,  0.29 };
	m_viewport.lookAt = { 0, 0, -1 };
	m_viewport.reset();


	//Materials and world
	m_mGround = Lambertian({ 0.8, 0.8, 0.0 });
	m_mBlueOne = Lambertian({ 0.1, 0.2, 0.5 });
	m_mMirror = Metal({ 0.8, 0.8, 0.8 }, 0.3);
	m_mAirBubble = Dieletric(1.5);
	m_mHollowOut = Dieletric(1.5);
	m_mHollowIn = Dieletric(1.0 / 1.5);

	m_ground = Sphere({ 0, -100.5, -1 }, 100, &m_mGround);
	m_blueOne = Sphere({ 0, 0.0, -1.2 }, 0.5, &m_mBlueOne);
	m_mirror = Sphere({ 0.48, 0.9, -1.0 }, 0.5, &m_mMirror);
	m_airBubble = Sphere({ 1.0, 0.0, -1.0 }, 0.5, &m_mAirBubble);
	m_hollowOut = Sphere({ -1.0, 0.0, -1.0 }, 0.5, &m_mHollowOut);
	m_hollowIn = Sphere({ -1.0, 0.0, -1.0 }, 0.4, &m_mHollowIn);

	m_world.push_back(&m_ground);
	m_world.push_back(&m_blueOne);
	m_world.push_back(&m_mirror);
	m_world.push_back(&m_airBubble);
	m_world.push_back(&m_hollowOut);
	m_world.push_back(&m_hollowIn);
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
	if (Settings::pathTracing)
	{
		m_framebuffer.sampleCount++;
		for (size_t y = 0; y < Settings::iResolution.y; y++)
		{
			for (size_t x = 0; x < Settings::iResolution.x; x++)
			{
				//Compute pixel color between [0;1] foreach components
				Ray ray = m_viewport.generateAA(x, y);
				glm::vec3 sample = Raytracer::trace(ray, m_world, 0);
				m_framebuffer.addAccumulation(x, y, sample);

				glm::vec3 pixelColor = m_framebuffer.getAccumulation(x, y) / (float)m_framebuffer.sampleCount;	
				pixelColor = Math::clamp(pixelColor, 0, 1);
				pixelColor = Settings::gammaCorrection ? Math::linearToGamma2(pixelColor) : pixelColor;

				m_framebuffer.setPixel(x, y, pixelColor * 255);
			}
		}	
		
	}
	else
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

				pixelColor = Settings::gammaCorrection ? Math::linearToGamma2(pixelColor) : pixelColor;
				m_framebuffer.setPixel(x, y, pixelColor * 255);
			}
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
		ImGui::Text("FPS                       : %i", fps);
		ImGui::Text("Last rendering time       : %f ms", m_renderingTime);
		ImGui::Text("Path tracing sample count : %i", m_framebuffer.sampleCount);

		//Graphics settings
		ImGui::SeparatorText("Graphics");
		if (ImGui::Checkbox("Patch tracing", &Settings::pathTracing))
		{
			m_framebuffer.reset();
		}
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

		ImGui::DragInt(  "Bounce limit",		&Settings::bounceLimit, 1, 1, 50);
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

		if (ImGui::DragFloat3("Position", &m_viewport.position.x, 0.01))
		{
			m_viewport.reset();
		}

		if (ImGui::DragFloat3("Look at", &m_viewport.lookAt.x, 0.01))
		{
			m_viewport.reset();
		}

		/*
		//World settings
		ImGui::SeparatorText("World");
		ImGui::DragFloat3("1", &m_mirror.position.x,  0.01);
		ImGui::DragFloat3("2", &m_airBubble.position.x, 0.01);

		if (ImGui::TreeNode("Materials"))
		{
			ImGui::DragFloat3("Metallic left", &m_mMirror.albedo.x, 0.01, 0, 1);
			ImGui::DragFloat("Fuzz left", &m_mMirror.fuzz, 0.01, 0, 10);
			ImGui::DragFloat("Refraction index", &m_mAirBubble.refractionIndex, 0.01, 0.0, 3);
			ImGui::TreePop();
		}
		*/
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