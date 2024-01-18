#include "SimpleThreadPool.h"
#include <stdexcept>
#include <iostream>

SimpleThreadPool::SimpleThreadPool(size_t threadCount) {
    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(&SimpleThreadPool::WorkerTask, this);
    }
}

SimpleThreadPool::~SimpleThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& worker : threads) {
        worker.join();
    }
}

void SimpleThreadPool::Enqueue(std::function<void()> task) {

    std::unique_lock<std::mutex> lock(queueMutex);
    if (stop) {
        throw std::runtime_error("Enqueue on stopped ThreadPool");
    }
    tasks.push(std::move(task));

    condition.notify_one();
}

void SimpleThreadPool::WorkerTask() {
    while (true) {

        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            //std::cout << threads.size() << std::endl;
            condition.wait(lock, [this] { return stop || !tasks.empty(); });

            if (stop && tasks.empty()) {
                return;
            }
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}
