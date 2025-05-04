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

void FlightControlTower::requestDisembarking(Plane &plane) {
    //Check if gate is available


}
void FlightControlTower::requestTurnaroundCheck(Plane &plane) {
    //Check if engineers are available
}


void FlightControlTower::requestRefueling(Plane &plane) {
    //Check if tanker is available

}
void FlightControlTower::requestBoarding(Plane &plane) {
    //Check if cargo is available

}
void FlightControlTower::requestRunwayAvailability(Plane &plane) {


}
void FlightControlTower::requestTakeOff(Plane &plane) {


}

