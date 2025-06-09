//
// Created by Skipper on 19.05.2025.
//

#ifndef SO2PROJEKT2_GROUNDSERVICES_H
#define SO2PROJEKT2_GROUNDSERVICES_H
#include <vector>

#include "resources/RefuellingTruck.h"
#include "resources/TechnicalSupport.h"


class GroundServices {
    int numCars;
    RefuellingTruck refuellingTruck;
    std::vector<TechnicalSupport> techSupportCars;

public:
    explicit GroundServices(int numCars) : numCars(numCars), refuellingTruck(0) {
        ;
        techSupportCars.reserve(numCars);
        for (int i = 0; i < numCars; ++i) {
            techSupportCars.emplace_back();
        }
    }

    RefuellingTruck getRefuellingTruck() {
        return refuellingTruck;
    }

    bool requestTechSupportAvailability(std::string planeID, int &gateIndex) {
        for (auto &car: techSupportCars) {
            if (!car.isInUse()) {
                car.performTurnaroundCheck(planeID, gateIndex);
                return true; // Found an available technical support car
            }
        }
        return false; // No available technical support cars
    };

    std::vector<TechnicalSupport> &getTechSupportCars() {
        return techSupportCars;
    }
};


#endif //SO2PROJEKT2_GROUNDSERVICES_H
