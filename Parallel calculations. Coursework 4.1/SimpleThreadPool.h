#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class SimpleThreadPool {
public:
    explicit SimpleThreadPool(size_t threadCount);
    ~SimpleThreadPool();
    void Enqueue(std::function<void()> task);

private:
    void WorkerTask();

    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop = false;
};
