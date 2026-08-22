#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>

class ThreadPool
{
public :
	ThreadPool(int nbThread = std::thread::hardware_concurrency());
	~ThreadPool();
	
	void enqueue(std::function<void()> task);
	void finish();

	int nbThread;

private :
	std::vector<std::thread> m_threads;

	std::mutex m_tasksMutex;
	std::queue<std::function<void()>> m_tasks;

	std::condition_variable m_cv;
	bool m_stop;

	std::atomic<int> m_taskRemaining;
	std::mutex m_finishedMutex;
	std::condition_variable m_finishedcv;
};