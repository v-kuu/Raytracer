#pragma once
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

// based on the example from geeksforgeeks.org
class	ThreadPool
{
	public:
		ThreadPool(size_t threads = std::thread::hardware_concurrency());
		~ThreadPool(void);
		ThreadPool(const ThreadPool &other) = delete;
		ThreadPool	&operator=(const ThreadPool &other) = delete;

		void	enqueue(std::function<void()> task);
		void	wait(void);

		size_t	getSize(void) const;

	private:
		size_t _size;
		std::atomic<size_t> _busy;
		std::vector<std::thread> _threads;
		std::queue<std::function<void()>> _tasks;
		std::mutex _queue_mutex;
		std::condition_variable _cv;
		std::condition_variable _finished;
		bool _stop = false;
};
