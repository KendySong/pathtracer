#include "Application.hpp"

Application::Application()
{
	m_fps = 0;
	m_renderedFPS = 0;

	SDL_Init(SDL_INIT_VIDEO);
	p_window = SDL_CreateWindow("Physically based path tracer", Settings::screen.x, Settings::screen.y, SDL_WINDOW_RESIZABLE);
	p_renderer = SDL_CreateRenderer(p_window, nullptr);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplSDL3_InitForSDLRenderer(p_window, p_renderer);
	ImGui_ImplSDLRenderer3_Init(p_renderer);

	SDL_SetRenderLogicalPresentation(p_renderer, Settings::iResolution.x, Settings::iResolution.y, SDL_LOGICAL_PRESENTATION_STRETCH);
}

void Application::run()
{
	bool run = true;
	SDL_Event event;
	Sandbox sandbox(p_window, p_renderer);

	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
				run = false;
		}

		this->computeDeltaTime();
		this->countFramerate();

		sandbox.update(m_dt);
		
		//Render scene
		SDL_SetRenderLogicalPresentation(p_renderer, Settings::iResolution.x, Settings::iResolution.y, SDL_LOGICAL_PRESENTATION_STRETCH);	
		if (Settings::continiousRendering)
		{
			sandbox.clear();
			sandbox.draw();
		}
		sandbox.render();

		//Render GUI
		SDL_SetRenderLogicalPresentation(p_renderer, Settings::screen.x, Settings::screen.y, SDL_LOGICAL_PRESENTATION_DISABLED);
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
		sandbox.gui(m_renderedFPS);
		ImGui::Render();
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), p_renderer);
			

		SDL_RenderPresent(p_renderer);
	}

	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(p_renderer);
	SDL_DestroyWindow(p_window);
	SDL_Quit();
}

void Application::countFramerate()
{
	m_fps++;
	if (m_fpsTimer.getElapsedTime() >= 1)
	{
		m_renderedFPS = m_fps;
		m_fps = 0;
		m_fpsTimer.restart();
	}
}

void Application::computeDeltaTime()
{
	m_dt = m_dtTimer.getElapsedTime();
	m_dtTimer.restart();
}