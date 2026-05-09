#include <iostream>
#include <thread>
#include <vector>
#include <semaphore> // C++20

// Imagine we have a pool of 3 "Permits"
std::counting_semaphore<3> office_desks(3); 

void work(int id) {
    // Binary semaphore would block everyone but one.
    // This allows up to 3 people to work simultaneously.
    office_desks.acquire(); 
    
    std::cout << "Employee " << id << " is using a desk.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    std::cout << "Employee " << id << " is leaving.\n";
    office_desks.release(); // Returns the "key" to the pool
}

int main() {
    std::vector<std::thread> employees;
    for (int i = 1; i <= 6; ++i) {
        employees.emplace_back(work, i);
    }

    for (auto& t : employees) t.join();
    return 0;
}
