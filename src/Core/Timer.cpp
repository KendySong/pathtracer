#include "Timer.hpp"

Timer::Timer()
{
	start();
}

void Timer::start() noexcept
{
	m_start = std::chrono::system_clock::now();
	m_isRunning = true;
}

void Timer::restart() noexcept
{
	start();
}

void Timer::stop() noexcept
{
	m_stop = std::chrono::system_clock::now();
	m_isRunning = false;
}

double Timer::getElapsedTime() noexcept
{
	if (m_isRunning)
	{
		m_elapsed = std::chrono::system_clock::now();
	}
	else
	{
		m_elapsed = m_stop;
	}

	return std::chrono::duration<double>(m_elapsed - m_start).count();
}