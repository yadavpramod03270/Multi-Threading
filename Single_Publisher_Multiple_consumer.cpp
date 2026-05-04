#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cv;
bool finished = false;

// The Producer: Adds items to the queue
void producer(int items) {
    for (int i = 1; i <= items; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            buffer.push(i);
            std::cout << "Produced: " << i << std::endl;
        }
        // Wake up ONE waiting consumer
        cv.notify_one(); 
    }

    // Signal that production is done
    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    // Wake up ALL consumers to check the finished flag
    cv.notify_all(); 
}

// The Consumer: Processes items from the queue
void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // Wait until queue is not empty OR production is finished
        cv.wait(lock, []{ return !buffer.empty() || finished; });

        while (!buffer.empty()) {
            int val = buffer.front();
            buffer.pop();
            std::cout << "Consumer " << id << " processed: " << val << std::endl;
        }

        if (finished) break;
    }
}

int main() {
    std::thread prod(producer, 10);
    std::vector<std::thread> consumers;

    // Launch 3 consumer threads
    for (int i = 0; i < 3; ++i) {
        consumers.emplace_back(consumer, i);
    }

    prod.join();
    for (auto& t : consumers) {
        t.join();
    }

    return 0;
}
/*
The Single Producer, Multiple Consumer 
(SPMC) pattern is a concurrency architectural pattern used to distribute work or data from a single source to multiple worker threads
or processes efficiently
------------------------------------------------------
the Single Producer, Multiple Consumer (SPMC) pattern is the core architectural engine inside most thread pools.
 The Core Difference
 SPMC Pattern:
 A low-level synchronization strategy using a queue, a mutex, and a condition variable to pass data from one thread to many.
 ----------------------------------------------------------------
 Thread Pool: 
 A high-level manager that uses the SPMC pattern to distribute "work" (functions or tasks) to a fixed set of pre-allocated "worker" threads
*/
