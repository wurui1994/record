#include <mutex>
#include <thread>
#include <queue>
#include <vector>
#include <iostream>
#include <functional>

class ThreadPool
{
public:
    ThreadPool(size_t);
    ~ThreadPool();
    void workerRun();
    void enqueue(void (int), int arg);
    
private:
    bool stop;
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
};

ThreadPool::ThreadPool(size_t threads)
    : stop(false)
{
    for (size_t i = 0; i < threads; ++i)
        workers.emplace_back([this]{ workerRun(); });
}

void ThreadPool::workerRun()
{
    std::function<void()> task;
    while (1)
    {
        {
            std::unique_lock<std::mutex> lock(this->queue_mutex);
            this->condition.wait(lock, [this]{ return stop || !this->tasks.empty(); });
            if (this->tasks.empty()) return;
            task = this->tasks.front();
            this->tasks.pop();
        }
        task();
    }
}

void ThreadPool::enqueue(void func(int), int arg)
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.emplace([func, arg]{ (*func)(arg); });
    }
    condition.notify_one();
}

ThreadPool::~ThreadPool()
{
    stop = true;
    condition.notify_all();
    for (std::thread &worker : workers)
        worker.join();
}

void func(int i)
{
    std::cout << "hello " << i << std::endl;
    std::cout << "world " << i << std::endl;
}

int main()
{
    ThreadPool pool(4);
    for (int i = 0; i < 8; ++i)
        pool.enqueue(func, i);
    return 0;
}
