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
    bool isAvailableForPlanes = true;
    bool isAvailableForPassengers = false;
    mutable std::mutex mutex; //mutable aby modyfikowac w constach
    std::string currentPlaneId;

public:
    Gate(int index)
        : index(index) {
    }
    //blokowanie kopiowania aby mutex mogł byc w klasie
    Gate(const Gate&) = delete;
    Gate& operator=(const Gate&) = delete;

    ~Gate() {
        std::cout << "Destruktor: " << index << std::endl;
    }


    //przenoszenie aby mutex mogł byc w klasie
    Gate(Gate&& other) noexcept
        : index(other.index),
          isAvailableForPlanes(other.isAvailableForPlanes),
          currentPlaneId(std::move(other.currentPlaneId)) {}

    //operator przenoszenia (na przyszlosc)
    Gate& operator=(Gate&& other) noexcept {
        if (this != &other) {
            index = other.index;
            isAvailableForPlanes = other.isAvailableForPlanes;
            currentPlaneId = std::move(other.currentPlaneId);
            // Mutex nie jest przenoszony, pozostaje bez zmian
        }
        return *this;
    }


    void blockGate(const std::string& planeId) {
        std::lock_guard<std::mutex> lock(mutex);
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

    const std::string& getCurrentPlaneId() const {
        std::lock_guard<std::mutex> lock(mutex);
        return currentPlaneId;
    }
    bool isGateAvailableForPassengers() const {
        std::lock_guard<std::mutex> lock(mutex);
        return isAvailableForPassengers;
    }
    void setGateOpenedForPassengers() {
        std::lock_guard<std::mutex> lock(mutex);
        isAvailableForPassengers = true;
    }
    void setGateClosedForPassengers() {
        std::lock_guard<std::mutex> lock(mutex);
        isAvailableForPassengers = false;
    }
};




#endif //GATE_H
