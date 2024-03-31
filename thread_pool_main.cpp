#include <iostream>
#include <cmath>
#include <chrono>
#include "thread_pool.h"

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast; // do pomiaru czasu trwania 'obliczeń'
    using std::chrono::duration;
    using std::chrono::milliseconds;

    std::vector<int> numbers;
    for (int i = 1; i < 100; i++) numbers.push_back(i);

    // Wykorzystanie thread_pool
    auto t1 = high_resolution_clock::now();
    
    thread_pool pool1(4);

    for (const auto& num : numbers) 
    {
        pool1.add_task([num] {
            std::this_thread::sleep_for(milliseconds(10)); 
            return std::sqrt(num);
        });
    }

    double res = pool1.average();
    std::cout << "Average root: " << res << std::endl;

    auto t2 = high_resolution_clock::now();
    auto dur1 = duration_cast<milliseconds>(t2 - t1);
    std::cout << "Duration with thread_pool: " << dur1.count() << "ms\n";

    // Dla porównania to samo zadanie na pojedynczym wątku
    auto t3 = high_resolution_clock::now();

    double sum = 0.0;
    for (const auto& num : numbers) {
        std::this_thread::sleep_for(milliseconds(10));
        sum += std::sqrt(num);
    }

    res = sum / numbers.size();
    std::cout << "Average root: " << res << std::endl;

    auto t4 = high_resolution_clock::now();
    auto dur2 = duration_cast<milliseconds>(t4 - t3);
    std::cout << "Duration with single thread: " << dur2.count() << "ms\n";

    return 0;
}
