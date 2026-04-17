#include <iostream>

#include <thread>

#include <vector>

#include <queue>

#include <functional>

#include <mutex>

#include <condition_variable>

using namespace std;

class ThreadPool {
    vector < thread > workers;
    queue < function < void() >> tasks;

    mutex mtx;
    condition_variable cv;
    bool stop;

    public:
        ThreadPool(int numThreads): stop(false) {

            for (int i = 0; i < numThreads; i++) {
                workers.emplace_back([this]() {

                    while (true) {
                        function < void() > task;

                        {
                            unique_lock < mutex > lock(mtx);

                            cv.wait(lock, [this]() {
                                return !tasks.empty() || stop;
                            });

                            if (stop && tasks.empty())
                                return;

                            task = move(tasks.front());
                            tasks.pop();
                        }

                        task(); // execute
                    }
                });
            }
        }

    void enqueue(function < void() > task) {
            {
                unique_lock < mutex > lock(mtx);
                tasks.push(move(task));
            }
            cv.notify_one();
        }

        ~ThreadPool() {
            {
                unique_lock < mutex > lock(mtx);
                stop = true;
            }

            cv.notify_all();

            for (thread & t: workers)
                t.join();
        }
};

int main() {
    ThreadPool pool(3);

    for (int i = 0; i < 10; i++) {
        pool.enqueue([i]() {
            cout << "Task " << i << " executed by thread " <<
                this_thread::get_id() << endl;
        });
    }

    return 0;
}