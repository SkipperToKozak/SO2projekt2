//
// Created by Skipper on 19.05.2025.
//

#ifndef SO2PROJEKT2_REFUELLINGTRUCK_H
#define SO2PROJEKT2_REFUELLINGTRUCK_H

#include "Vehicle.h"
#include <iostream>

class RefuellingTruck : public Vehicle {
public:
    void performTask(const std::string &planeId) override {
        std::cout << "[REFUELLING-TRUCK " << vehicleID << "] ";
        std::cout << "Refuelling plane with ID: " << planeId << std::endl;
    }

    std::string getType() const override {
        return "Refuelling Truck";
    }
};


#endif //SO2PROJEKT2_REFUELLINGTRUCK_H
