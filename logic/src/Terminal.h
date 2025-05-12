//
// Created by Skipper on 03.05.2025.
//

#ifndef TERMINAL_H
#define TERMINAL_H


#include "resources/Gate.h"
#include <vector>
#include <memory>
#include <mutex>

class Terminal {
    std::vector<Gate> gates;
    mutable std::mutex mutex;

public:
    explicit Terminal(int numGates) {
        for (int i = 0; i < numGates; ++i) {
            gates.emplace_back(i);
        }
    }
//do przerobienia w kontekście mutexów (lockguard raczej powinien być w gacie)
    //przekminic tez to czy nie lepiej jakos inaczej zarzadzac przypisywaniem indexu gate'a
    Gate* assignGate(const std::string& planeId) {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto& gate : gates) {
            if (gate.isGateAvailable()) {
                gate.blockGate(planeId);
                return &gate;
            }
        }
        return nullptr; // Brak dostępnych gate'ów
    }
//przekminic
    void releaseGate(int gateIndex) {
        std::lock_guard<std::mutex> lock(mutex);
        if (gateIndex >= 0 && gateIndex < gates.size()) {
            gates[gateIndex].releaseGate();
        }
    }
    void releaseGate(std::string planeId) {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto& gate : gates) {
            if (gate.getCurrentPlaneId() == planeId) {
                gate.releaseGate();
                break; // Przerywamy po znalezieniu odpowiedniego gate'a

            }
        }

    }
};


#endif //TERMINAL_H
