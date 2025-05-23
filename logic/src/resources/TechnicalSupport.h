//
// Created by Skipper on 19.05.2025.
//

#ifndef SO2PROJEKT2_TECHNICALSUPPORT_H
#define SO2PROJEKT2_TECHNICALSUPPORT_H

#include "Vehicle.h"
#include <iostream>

class TechnicalSupport : public Vehicle {
public:

    void performTask(const std::string &planeId) override {
        std::cout << "[TECH-SUPPORT " << vehicleID << "] ";
        std::cout << "Providing technical support to plane with ID: " << planeId << std::endl;
    }

    std::string getType() const override {
        return "Technical Support Vehicle";
    }
};

#endif //SO2PROJEKT2_TECHNICALSUPPORT_H
