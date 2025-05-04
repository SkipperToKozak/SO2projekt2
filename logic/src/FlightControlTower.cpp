//
// Created by Skipper on 01.05.2025.
//

#include "FlightControlTower.h"

#include <iostream>


void FlightControlTower::initialize() {
    for (int i = 0; i < NUM_RUNWAYS; i++) {
        runways.emplace_back(i);
    }
}

bool FlightControlTower::requestLanding(Plane &plane) {
    // Check if a runway is available

    for (auto &runway : runways) {
        if (runway.isRunwayAvailable()) {
            runway.blockRunway(plane.getFlightNumber());
            std::cout << "[FLIGHT CONTROL TOWER] ";
            std::cout << "Plane " << plane.getFlightNumber() << " is landing on runway " << runway.getIndex() << std::endl;
            return true;
        }
    }
    // If no runway is available, inform the plane
    std::cout << "[FLIGHT CONTROL TOWER] ";
    std::cout << "No available runways for plane " << plane.getFlightNumber() << std::endl;
    return false;


}
void FlightControlTower::requestBoarding(Plane &plane) {


}
void FlightControlTower::requestDisembarking(Plane &plane) {


}


void FlightControlTower::requestRefueling(Plane &plane) {


}
void FlightControlTower::requestRunwayAvailability(Plane &plane) {


}
void FlightControlTower::requestTakeOff(Plane &plane) {


}
void FlightControlTower::requestHangarAvailability(Plane &plane) {


}
void FlightControlTower::requestTerminalAvailability(Plane &plane) {


}
