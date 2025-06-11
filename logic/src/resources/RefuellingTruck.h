//
// Created by Skipper on 09.06.2025.
//

#ifndef REFUELLINGTRUCK_H
#define REFUELLINGTRUCK_H
#include <string>
#include <thread>

#include "src/utilities/randomise.h"


enum class RefuellingTruckStatus {
    Idle, // Truck is not in use
    Refuelling, // Truck is currently refuelling a plane
    GoingForFuel // Truck is undergoing maintenance
};

inline std::string to_string(RefuellingTruckStatus status) {
    switch (status) {
        case RefuellingTruckStatus::Idle: return "Idle";
        case RefuellingTruckStatus::Refuelling: return "Refuelling";
        case RefuellingTruckStatus::GoingForFuel: return "GoingForFuel";
        default: return "Unknown";
    }
}

class RefuellingTruck {
    int truckID = 0; // Unique identifier for the refuelling truck
    bool inUse = false; // Indicates if the truck is currently in use
    RefuellingTruckStatus status = RefuellingTruckStatus::Idle; // Current status of the truck

public:
    explicit RefuellingTruck(int id)
        : truckID(id) {
    }

    void goForFuel(std::atomic<int> &fuelNeeded, int fuelCapacity) {
        inUse = true; // Mark the truck as in use
        status = RefuellingTruckStatus::GoingForFuel;
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Simulate time taken to go for fuel
        status = RefuellingTruckStatus::Refuelling;
        while (fuelNeeded < fuelCapacity) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate time taken to go for fuel
            if (fuelNeeded + 10 > fuelCapacity) {
                fuelNeeded = fuelCapacity; // Ensure we don't exceed the fuel capacity
            } else {
                fuelNeeded += 10; // Truck refuels airport
            }
        }
        status = RefuellingTruckStatus::Idle; // Mark the truck as idle after refuelling
        inUse = false; // Mark the truck as not in use
    }
    [[nodiscard]] int getTruckID() const {
        return truckID;
    }

    [[nodiscard]] bool &isInUse() {
        return inUse;
    }

    [[nodiscard]] RefuellingTruckStatus getStatus() const {
        return status;
    }
};


#endif //REFUELLINGTRUCK_H
