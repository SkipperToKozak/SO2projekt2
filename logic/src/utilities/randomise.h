//
// Created by Skipper on 12.05.2025.
//

#ifndef SO2PROJEKT2_RANDOMISE_H
#define SO2PROJEKT2_RANDOMISE_H
#include <mutex>
#include <random>

inline int randInt(int min, int max) {
    // std::lock_guard<std::mutex> lock(std::mutex);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(mt);
}

#endif //SO2PROJEKT2_RANDOMISE_H
