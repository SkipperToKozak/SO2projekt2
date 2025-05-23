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
    Gate *assignGate(const std::string &planeId, int planeLimit) {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto &gate: gates) {
            if (gate.isGateAvailableForPlanes()) {
                gate.blockGate(planeId, planeLimit);
                return &gate;
            }
        }
        return nullptr; // Brak dostępnych gate'ów
    }

    //TODO przekminic
    // void releaseGate(int gateIndex) {
    //     std::lock_guard<std::mutex> lock(mutex);
    //     if (gateIndex >= 0 && gateIndex < gates.size()) {
    //         gates[gateIndex].releaseGate();
    //     }
    // }
    //TODO przekminic
    void releaseGate(const std::string &planeId) {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto &gate: gates) {
            if (gate.getCurrentPlaneId() == planeId) {
                gate.releaseGate();
                gate.setGateClosedForEnteringPassengers();
                break; // Przerywamy po znalezieniu odpowiedniego gate'a
            }
        }
    }

    //przekminic czy tu powinny byc inty czy moze gejty czy moze string z nazwa samolotu
    // void setGateOpenedForPassengers(int gateIndex) {
    //     std::lock_guard<std::mutex> lock(mutex);
    //     gates[gateIndex].setGateOpenedForPassengers();
    // }
    void setGateOpenedForPassengers(std::string planeId) {
        for (auto &gate: gates) {
            if (gate.getCurrentPlaneId() == planeId) {
                gate.setGateOpenedForEnteringPassengers();
                break; // Przerywamy po znalezieniu odpowiedniego gate'a
            }
        }
    }

    void setGateClosedForPassengers(int gateIndex) {
        std::lock_guard<std::mutex> lock(mutex);
        gates[gateIndex].setGateClosedForEnteringPassengers();
    }

    bool isGateOpenedForPassengers(int &gateIndex, int passengerID) {
        // std::lock_guard<std::mutex> lock(mutex);
        for (auto &gate: gates) {
            if (gate.isGateAvailableForEnteringPassengers()) {
                gateIndex = gate.getIndex();
                std::cout << terminalTag;
                std::cout << "Passenger " << passengerID << " is boarding at gate " << gateIndex << std::endl;
                return true;
            }
        }
        return false;
    }

    bool goThroughGate(int passengerSize) {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto &gate: gates) {
            if (gate.isGateAvailableForEnteringPassengers()) {
                return gate.enterThroughGate(passengerSize);;
            }
        }
        return false;
    }

    std::vector<Gate> &getGates() {
        return gates;
    }
};


#endif //TERMINAL_H
