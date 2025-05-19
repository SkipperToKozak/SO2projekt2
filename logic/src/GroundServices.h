//
// Created by Skipper on 19.05.2025.
//

#ifndef SO2PROJEKT2_GROUNDSERVICES_H
#define SO2PROJEKT2_GROUNDSERVICES_H

#include <vector>
#include <memory>
#include "resources/Vehicle.h"
#include "resources/RefuellingTruck.h"
#include "resources/TechnicalSupport.h"

class GroundServices {
public:
    void initializeServices() {


        vehicles.push_back(std::make_unique<RefuellingTruck>());
        vehicles.push_back(std::make_unique<TechnicalSupport>());
        //moze jednak zrobic te klasy osobno
    }

private:
    std::vector<std::unique_ptr<Vehicle>> vehicles;


};


#endif //SO2PROJEKT2_GROUNDSERVICES_H
