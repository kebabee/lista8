#include "thread_pool.h"

thread_pool::thread_pool(int numOfThreads) 
{
    stopFlag = false;
    manageThreads(numOfThreads);
    std::cout << "Constructed\n";
}

thread_pool::~thread_pool() 
{
    stop();
    std::cout << "Destructed\n";
}

void thread_pool::add_task(std::function<double()> task) 
{
    {
        std::unique_lock<std::mutex> lock(queueMutex); // ochrona dostępu kolejki zadań
        tasks.push(std::move(task)); // task trafia do kolejki
    }
    taskAvailable.notify_one(); // sygnał dla jednego wątku o nowym oczekującym tasku
}

double thread_pool::average() 
{
    stopFlag = true;
    taskAvailable.notify_all();

    for (auto& thread : threads) 
    {
        thread.join(); // czekamy na zakończenie wszystkich wątków
    }

    std::lock_guard<std::mutex> lock(queueMutex);
    double sum = 0.0;
    int count = 0;

    while (!endedTasks.empty()) // ilość zakończonych tasków i suma wyników
    {
        sum += endedTasks.back();
        endedTasks.pop_back();
        ++count;
    }

    return sum / count;
}

void thread_pool::stop() 
{
    if (!stopFlag) 
    {
        stopFlag = true;
        taskAvailable.notify_all();

        for (auto& thread : threads) 
        {
            thread.join();
        }
    }
}

void thread_pool::manageThreads(int numThreads) 
{
    if (threads.empty()) // stwórz numThreads wątków tylko jeśli jeszcze ich nie ma
    {
        for (int i = 0; i < numThreads; ++i) 
        {
            threads.emplace_back([this] 
            {
                while (true) // każdy wątek czeka na zadanie
                {
                    std::function<double()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        taskAvailable.wait(lock, [this] { // czekaj na zadanie albo stopFlag
                            return stopFlag || !tasks.empty();
                        });

                        if (stopFlag && tasks.empty()) {
                            return;
                        }

                        task = std::move(tasks.front()); // weź i usuń taska z kolejki
                        tasks.pop();
                    }
                    double result = task();                        
                    std::lock_guard<std::mutex> lock(queueMutex);
                    endedTasks.push_back(result); // wykonaj taska i zapisz wynik do endedTasks
                }
            });
        }
    }
}
