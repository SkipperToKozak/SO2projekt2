//
// Created by Skipper on 04.05.2025.
//


#ifndef RUNWAY_H
#define RUNWAY_H
#include <iostream>

#include <mutex>
#include <string>


class Runway {
    int index = 0;
    bool isAvailable = true;
    mutable std::mutex mutex; //mutable aby modyfikowac w constach
    std::string currentPlaneId;
public:
    Runway(int index)
        : index(index) {
    }
    //blokowanie kopiowania aby mutex mogł byc w klasie
    Runway(const Runway&) = delete;
    Runway& operator=(const Runway&) = delete;

    ~Runway() {
        // std::cout << "Destruktor: " << index << std::endl;
    }


    //przenoszenie aby mutex mogł byc w klasie
    Runway(Runway&& other) noexcept
        : index(other.index),
          isAvailable(other.isAvailable),
          currentPlaneId(std::move(other.currentPlaneId)) {}

    //operator przenoszenia (na przyszlosc)
    Runway& operator=(Runway&& other) noexcept {
        if (this != &other) {
            index = other.index;
            isAvailable = other.isAvailable;
            currentPlaneId = std::move(other.currentPlaneId);
            // Mutex nie jest przenoszony, pozostaje bez zmian
        }
        return *this;
    }


    void blockRunway(const std::string& planeId) {
        std::lock_guard<std::mutex> lock(mutex);
        isAvailable = false;
        currentPlaneId = planeId;
    }

    void releaseRunway() {
        std::lock_guard<std::mutex> lock(mutex);
        currentPlaneId.clear();
        isAvailable = true;
    }
    bool isRunwayAvailable() const {
        std::lock_guard<std::mutex> lock(mutex);
        return isAvailable;
    }
    int getIndex() const {
        return index;
    }

    const std::string& getCurrentPlaneID() const {
        std::lock_guard<std::mutex> lock(mutex);
        return currentPlaneId;
    }
};


#endif //RUNWAY_H
