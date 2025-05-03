//
// Created by Skipper on 03.05.2025.
//

#ifndef RUNWAY_H
#define RUNWAY_H
#include <mutex>
#include <string>


class Runway {
    int index = 0;
    bool isAvailable = true;
    std::mutex mutex;
    std::string currentPlaneId;
public:
    explicit Runway(int index)
        : index(index) {
    }
    void blockRunway (const std::string& planeId) {
        mutex.lock();
        isAvailable = false;
        currentPlaneId = planeId;
    }
    void releaseRunway() {
        currentPlaneId = "";
        mutex.unlock();
        isAvailable = true;
    }
    bool isRunwayAvailable() const {
        return isAvailable;
    }
    int getIndex() const {
        return index;
    }

    std::string getCurrentPlaneId() const {
        return currentPlaneId;
    }
    void setCurrentPlaneId(const std::string& planeId) {
        currentPlaneId = planeId;
    }
    void setAvailable(bool available) {
        isAvailable = available;
    }

};



#endif //RUNWAY_H
