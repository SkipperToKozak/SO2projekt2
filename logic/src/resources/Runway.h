//
// Created by Skipper on 04.05.2025.
//


#ifndef RUNWAY_H
#define RUNWAY_H
#include <memory>
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

    //przenoszenie aby mutex mogł byc w klasie
    Runway(Runway&&) = default;
    Runway& operator=(Runway&&) = default;

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
};


#endif //RUNWAY_H
