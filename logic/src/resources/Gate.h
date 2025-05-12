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
    bool isAvailable = true;
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
          isAvailable(other.isAvailable),
          currentPlaneId(std::move(other.currentPlaneId)) {}

    //operator przenoszenia (na przyszlosc)
    Gate& operator=(Gate&& other) noexcept {
        if (this != &other) {
            index = other.index;
            isAvailable = other.isAvailable;
            currentPlaneId = std::move(other.currentPlaneId);
            // Mutex nie jest przenoszony, pozostaje bez zmian
        }
        return *this;
    }


    void blockGate(const std::string& planeId) {
        std::lock_guard<std::mutex> lock(mutex);
        isAvailable = false;
        currentPlaneId = planeId;
    }

    void releaseGate() {
        std::lock_guard<std::mutex> lock(mutex);
        currentPlaneId.clear();
        isAvailable = true;
    }
    bool isGateAvailable() const {
        std::lock_guard<std::mutex> lock(mutex);
        return isAvailable;
    }
    int getIndex() const {
        return index;
    }

    const std::string& getCurrentPlaneId() const {
        std::lock_guard<std::mutex> lock(mutex);
        return currentPlaneId;
    }
};




#endif //GATE_H
