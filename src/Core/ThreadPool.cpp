#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int nbThread) : nbThread(nbThread)
{
	m_stop = false;
	m_taskRemaining = 0;

	for (size_t i = 0; i < nbThread; i++)
	{
		m_threads.emplace_back([this]() -> void {

			while (true)
			{
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(m_tasksMutex);

					m_cv.wait(lock, [this]() -> bool { return !m_tasks.empty() || m_stop; });
					if (m_stop && m_tasks.empty())
					{
						return;
					}

					task = move(m_tasks.front());
					m_tasks.pop();
				}

				task();
				if (--m_taskRemaining == 0)
				{
					m_finishedcv.notify_all();
				}
			}
		});
	}
}

ThreadPool::~ThreadPool()
{
	{
		{
			std::unique_lock<std::mutex> lock(m_tasksMutex);
			m_stop = true;
		}

		m_cv.notify_all();
		for (size_t i = 0; i < nbThread; i++)
		{
			m_threads[i].join();
		}
	}
}

void ThreadPool::enqueue(std::function<void()> task)
{
	m_taskRemaining++;
	{
		std::unique_lock lock(m_tasksMutex);
		m_tasks.push(task);
	}
	m_cv.notify_one();
}

void ThreadPool::finish()
{
	std::unique_lock<std::mutex> lock(m_finishedMutex);
	m_finishedcv.wait(lock, [this]() -> bool {
		return m_taskRemaining == 0;
	});
}