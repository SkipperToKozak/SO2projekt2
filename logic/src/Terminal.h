//
// Created by Skipper on 03.05.2025.
//

#ifndef TERMINAL_H
#define TERMINAL_H


#include "resources/Gate.h"
#include <vector>
#include <memory>
#include <mutex>

#include "Plane.h"
inline std::string terminalTag = "[AT TERMINAL] "; //air traffic control tower tag

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
            if (gate.isGateAvailableForPlanes()) {
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
    void releaseGate(const std::string& planeId) {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto& gate : gates) {
            if (gate.getCurrentPlaneId() == planeId) {
                gate.releaseGate();
                break; // Przerywamy po znalezieniu odpowiedniego gate'a

            }
        }

    }
    void setGateOpenedForPassengers(int gateIndex) {
        gates[gateIndex].setGateOpenedForPassengers();
    }
    void setGateClosedForPassengers(int gateIndex) {
        gates[gateIndex].setGateClosedForPassengers();
    }
    bool isGateOpenedForPassengers(int &gateIndex, int passengerID) {
        for (auto& gate : gates) {
            if (gate.isGateAvailableForPassengers()) {
                gateIndex = gate.getIndex();
                std::cout << terminalTag;
                std::cout << "Passenger " << passengerID << " is boarding at gate " << gateIndex << std::endl;
                return true;
            }
        }
        return false;
    }

};


#endif //TERMINAL_H
