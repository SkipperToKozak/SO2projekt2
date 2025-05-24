//
// Created by Skipper on 24.05.2025.
//

#ifndef TIMER_H
#define TIMER_H


#include <chrono>


static auto startCounter() {
    return std::chrono::high_resolution_clock::now();
}

static auto getCounter(auto start_time) {
    auto end_time = startCounter();
    std::chrono::duration<double, std::micro> elapsed = end_time - start_time;
    return std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
}

#endif //TIMER_H
