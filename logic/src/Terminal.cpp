//
// Created by Skipper on 03.05.2025.
//

#include "Terminal.h"

#include "Airport.h"


void Terminal::startDisembarkation(int &numOfPassengers) {
    std::cout << terminalTag;
    std::cout << "Disembarking " << numOfPassengers << " passengers." << std::endl;
    airport.addPassengersLeavingThePlane(numOfPassengers);

    std::cout << terminalTag;
    std::cout << "Disembarkation completed." << std::endl;
}

void Terminal::setGateOpenedForExitingPassengers(int gateIndex) {
    for (auto &gate: gates) {
        if (gate.getIndex() == gateIndex) {
            gate.setGateOpenedForExitingPassengers();
            break;
        }
    }
}
