/*
Klasa thread_pool  zawiera listę zadań do wykonania (obiekty klasy std::function<double()>) oraz zestaw wątków procesujących, 
które będą te zadania pobierają z listy i wykonują. Konstruktor tej klasy startuje zadaną w argumencie liczbę wątków procesujących.
Klasa ma trzy publiczne metody:
 1. void add_task(std::function<double()> task) - dodaje nowe zadanie do listy
 2.double average() - zwraca wartość średnią wyników wykonanych zadań
 3. void stop() - zatrzymująe procesowanie, czeka na zakończenie wszystkich wątków
*/

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <chrono>

class thread_pool 
{
public:
    thread_pool(int numOfThreads);
    ~thread_pool();
    void add_task(std::function<double()> task);
    double average();
    void stop();

private:
    std::vector<std::thread> threads;
    std::queue<std::function<double()>> tasks;
    std::vector<double> endedTasks; // przechowuje wyniki
    std::mutex queueMutex;
    std::condition_variable taskAvailable;
    int numThreads;
    bool stopFlag;
    void manageThreads(int numThreads);
};
