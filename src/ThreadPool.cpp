#include "../inc/ThreadPool.hpp"

ThreadPool::ThreadPool(size_t threads) : _size(threads), _busy(0)
{
	for (size_t i = 0; i < threads; ++i)
	{
		_threads.emplace_back([this]
		{
			while (true)
			{
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(_queue_mutex);
					_cv.wait(lock,
							[this]{ return (!_tasks.empty() || _stop); });
					if (_stop && _tasks.empty())
						return ;
					task = std::move(_tasks.front());
					_tasks.pop();
				}
				_busy++;
				task();
				_busy--;
				_finished.notify_one();
			}
		});
	}
}

ThreadPool::~ThreadPool(void)
{
	{
		std::unique_lock<std::mutex> lock(_queue_mutex);
		_stop = true;
	}
	_cv.notify_all();
	for (auto& thread : _threads)
		thread.join();
}

void	ThreadPool::enqueue(std::function<void()> task)
{
	{
		std::unique_lock<std::mutex> lock(_queue_mutex);
		_tasks.emplace(std::move(task));
	}
	_cv.notify_one();
}

void	ThreadPool::wait(void)
{
	std::unique_lock<std::mutex> lock(_queue_mutex);
	_finished.wait(lock, [this](){ return _tasks.empty() && _busy == 0; });
}

size_t	ThreadPool::getSize(void) const
{
	return (_size);
}
