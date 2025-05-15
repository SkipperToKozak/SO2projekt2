//
// Created by Skipper on 03.05.2025.
//

#ifndef GATE_H
#define GATE_H

#include <iostream>

#include <mutex>
#include <string>


class Gate {
    int index = 0;
    int limit = 0;
    bool isAvailableForPlanes = true;
    bool isAvailableForEnteringPassengers = false;
    bool isAvailableForExitingPassengers = false;
    mutable std::mutex mutex; //mutable aby modyfikowac w constach
    std::string currentPlaneId;

public:
    Gate(int index)
        : index(index) {
    }

    //blokowanie kopiowania aby mutex mogł byc w klasie
    Gate(const Gate &) = delete;

    Gate &operator=(const Gate &) = delete;

    ~Gate() {
        std::cout << "Destruktor: " << index << std::endl;
    }


    //przenoszenie aby mutex mogł byc w klasie
    Gate(Gate &&other) noexcept
        : index(other.index),
          isAvailableForPlanes(other.isAvailableForPlanes),
          currentPlaneId(std::move(other.currentPlaneId)) {
    }

    //operator przenoszenia (na przyszlosc)
    Gate &operator=(Gate &&other) noexcept {
        if (this != &other) {
            index = other.index;
            isAvailableForPlanes = other.isAvailableForPlanes;
            currentPlaneId = std::move(other.currentPlaneId);
            // Mutex nie jest przenoszony, pozostaje bez zmian
        }
        return *this;
    }


    void blockGate(const std::string &planeId, int planeLimit) {
        std::lock_guard<std::mutex> lock(mutex);
        limit = planeLimit;
        isAvailableForPlanes = false;
        currentPlaneId = planeId;
    }

    void releaseGate() {
        std::lock_guard<std::mutex> lock(mutex);
        currentPlaneId.clear();
        isAvailableForPlanes = true;
    }

    bool isGateAvailableForPlanes() const {
        std::lock_guard<std::mutex> lock(mutex);
        return isAvailableForPlanes;
    }

    int getIndex() const {
        return index;
    }

    const std::string &getCurrentPlaneId() const {
        std::lock_guard<std::mutex> lock(mutex);
        return currentPlaneId;
    }

    bool isGateAvailableForEnteringPassengers() const {
        std::lock_guard<std::mutex> lock(mutex);
        return isAvailableForEnteringPassengers;
    }

    void setGateOpenedForPassengers() {
        std::lock_guard<std::mutex> lock(mutex);
        isAvailableForEnteringPassengers = true;
    }

    void setGateClosedForPassengers() {
        std::lock_guard<std::mutex> lock(mutex);
        isAvailableForEnteringPassengers = false;
    }

    bool enterThroughGate(int passengerSize) {
        if (limit < passengerSize) {
            return false;
        }
        limit -= passengerSize;
        return true;
    }
};


#endif //GATE_H
