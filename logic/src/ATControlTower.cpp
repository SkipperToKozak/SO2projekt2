//
// Created by Skipper on 01.05.2025.
//

#include "ATControlTower.h"

#include <iostream>

#include "Airport.h"

std::string fctTag = "[AT CONTROL TOWER] "; //air traffic control tower tag

void ATControlTower::initialize() {
    for (int i = 0; i < numRunways; i++) {
        runways.emplace_back(i);
    }
}

bool ATControlTower::requestLanding(Plane &plane) {
    int runwayIndex = -1;
    // Check if a runway is available
    if (requestRunwayAvailability(plane, runwayIndex)) {
        std::cout << fctTag;
        std::cout << "Plane " << plane.getFlightNumber() << " is landing on runway " << runwayIndex << std::endl;
        // for (auto &plane_temp: airport.getPlanes()) {
        //     // if (float(plane_temp.getCurrentFuel()) / float((plane_temp.getFuelCapacity()) < 0.3)) {
        //     //     // //sprawdza czy istnieje samolot z mala iloscia paliwa
        //     //     // if (plane.getFlightNumber() == plane_temp.getFlightNumber()) {
        //     //     //     //jesli to ten co prosi o zgode na ladowanie to sie zgadza
        //     //     //     return true;
        //     //     // }
        //     //     return false;
        //     // }
        // }
        return true;
    }
    // If no runway is available, inform the plane
    std::cout << fctTag;
    std::cout << "No available runways for plane " << plane.getFlightNumber() << std::endl;
    return false;
}


bool ATControlTower::requestDisembarking(Plane &plane, int &gateIndex) {
    Gate *gate = airport.getTerminal().assignGate(plane.getFlightNumber(), plane.getPassengerLimit());
    //Check if gate is null
    if (gate == nullptr) {
        std::cout << fctTag;
        std::cout << "No available gates for plane " << plane.getFlightNumber() << std::endl;
        return false;
    }
    plane.setGateIndex(gateIndex);
    std::cout << fctTag;
    std::cout << "Plane " << plane.getFlightNumber() << " is disembarking passengers at gate " << gate->getIndex() <<
            std::endl;
    gateIndex = gate->getIndex();
    return true;
    //(gate ? std::to_string(gate->getIndex()) : "none")
}

bool ATControlTower::requestTurnaroundCheck(Plane &plane) {
    //Check if engineers are available
    return true;
}


bool ATControlTower::requestRefueling(Plane &plane) {
    //Check if tanker is available
    return true;
}

bool ATControlTower::requestBoarding(Plane &plane) {
    //Check if cargo is available (int the future)
    if (true) {
        airport.getTerminal().setGateOpenedForPassengers(plane.getFlightNumber());
    }

    return true;
}

bool ATControlTower::requestRunwayAvailability(Plane &plane, int &runwayIndex) {
    for (auto &runway: runways) {
        if (runway.isRunwayAvailable()) {
            runway.blockRunway(plane.getFlightNumber());
            runwayIndex = runway.getIndex();
            return true;
        }
    }
    // If no runway is available, inform the plane
    return false;
}

bool ATControlTower::requestTaxiing(Plane &plane) {
    //Check if taxiway is available
    int runwayIndex = -1;
    if (requestRunwayAvailability(plane, runwayIndex)) {
        std::cout << fctTag;
        std::cout << "Plane " << plane.getFlightNumber() << " is taxiing to runway " << runwayIndex << std::endl;
        //release gate
        airport.getTerminal().releaseGate(plane.getFlightNumber());
        std::cout << fctTag;
        std::cout << "Plane " << plane.getFlightNumber() << " has released the gate." << std::endl;

        return true;
    }
    // If no taxiway is available, inform the plane
    std::cout << fctTag;
    std::cout << "No available taxiways for plane " << plane.getFlightNumber() << std::endl;
    return false;
}

bool ATControlTower::requestTakeOff(Plane &plane) {
    return true;
}

void ATControlTower::releaseRunway(Plane &plane) {
    for (auto &runway: runways) {
        if (runway.getCurrentPlaneID() == plane.getFlightNumber()) {
            runway.releaseRunway();
            std::cout << fctTag;
            std::cout << "Plane " << plane.getFlightNumber() << " has released the runway " << runway.getIndex() << "."
                    << std::endl;
            return;
        }
    }
}
