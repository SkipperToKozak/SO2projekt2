//
// Created by Skipper on 01.05.2025.
//

#include "FlightControlTower.h"

#include <iostream>

std::string fctTag = "[AT CONTROL TOWER] "; //air traffic control tower tag

void FlightControlTower::initialize() {
    for (int i = 0; i < numRunways; i++) {
        runways.emplace_back(i);
    }
}

bool FlightControlTower::requestLanding(Plane &plane) {
    // Check if a runway is available

    for (auto &runway : runways) {
        if (runway.isRunwayAvailable()) {
            runway.blockRunway(plane.getFlightNumber());
            std::cout << fctTag;
            std::cout << "Plane " << plane.getFlightNumber() << " is landing on runway " << runway.getIndex() << std::endl;
            return true;
        }
    }
    // If no runway is available, inform the plane
    std::cout << fctTag;
    std::cout << "No available runways for plane " << plane.getFlightNumber() << std::endl;
    return false;


}

bool FlightControlTower::requestDisembarking(Plane &plane) {
    Gate* gate = terminal.assignGate(plane.getFlightNumber());
    //Check if gate is null
    if (gate == nullptr) {
        std::cout << fctTag;
        std::cout << "No available gates for plane " << plane.getFlightNumber() << std::endl;
        return false;
    }
    else {
        std::cout << fctTag;
        std::cout << "Plane " << plane.getFlightNumber() << " is disembarking passengers at gate " << gate->getIndex() << std::endl;
        return true;
    }
//(gate ? std::to_string(gate->getIndex()) : "none")


}
bool FlightControlTower::requestTurnaroundCheck(Plane &plane) {
    //Check if engineers are available
    return true;
}


bool FlightControlTower::requestRefueling(Plane &plane) {
    //Check if tanker is available
    return true;
}
bool FlightControlTower::requestBoarding(Plane &plane) {
    //Check if cargo is available
    return true;
}
bool FlightControlTower::requestRunwayAvailability(Plane &plane) {
    return true;

}
bool FlightControlTower::requestTakeOff(Plane &plane) {
    return true;

}

