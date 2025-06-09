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
    RefuellingTruckStatus status = RefuellingTruckStatus::Idle; // Current status of the truck

public:
    explicit RefuellingTruck(int id)
        : truckID(id) {
    }

    void goForFuel(int &fuelNeeded, int fuelCapacity) {
        status = RefuellingTruckStatus::GoingForFuel;
        status = RefuellingTruckStatus::Refuelling;
        while (fuelNeeded < fuelCapacity) {
            std::this_thread::sleep_for(std::chrono::seconds(randInt(2, 5))); // Simulate time taken to go for fuel
            if (fuelNeeded += 15 > fuelCapacity) {
                fuelNeeded = fuelCapacity; // Ensure we don't exceed the fuel capacity
            } else {
                fuelNeeded += 15; // Truck refuels airport
            }
        }
    }
};


#endif //REFUELLINGTRUCK_H
