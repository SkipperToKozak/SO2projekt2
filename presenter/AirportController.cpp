//
// Created by Skipper on 20.05.2025.
//

#include "AirportController.h"

vector<PlaneViewModel> AirportController::getPlanesInfo() {
    std::lock_guard<std::mutex> lock(mutex);
    vector<PlaneViewModel> planeViewVec;
    for (const auto &plane: airport.getPlanes()) {
        PlaneViewModel planeViewModel;
        planeViewModel.flightNumber = plane.getFlightNumber();
        planeViewModel.passengerLimit = plane.getPassengerLimit();
        planeViewModel.passengersOnBoard = plane.getPassengersOnBoard();
        planeViewModel.currentFuel = plane.getCurrentFuel();
        planeViewModel.fuelCapacity = plane.getFuelCapacity();
        planeViewModel.currentRunway = plane.getCurrentRunway();
        planeViewModel.gateIndex = plane.getGateIndex();
        planeViewModel.statusText = plane.getStatusString();
        planeViewVec.push_back(planeViewModel);
    }
    return planeViewVec;
}

vector<PassengerViewModel> AirportController::getPassengersInfo() {
    std::lock_guard<std::mutex> lock(mutex);
    vector<PassengerViewModel> passengerViewVec;
    for (const auto &passenger: airport.getPassengers()) {
        PassengerViewModel passengerViewModel;
        passengerViewModel.passengerID = passenger.getPassengerID();
        passengerViewModel.gateIndex = passenger.getGateIndex();
        passengerViewModel.happiness = passenger.getHappiness();
        passengerViewModel.numberOf = passenger.getNumberOf();
        passengerViewModel.flightNumber = passenger.getFlightNumber();
        passengerViewModel.statusText = passenger.getPassengerStatusString();
        passengerViewVec.push_back(passengerViewModel);
    }
    return passengerViewVec;
}

vector<GateViewModel> AirportController::getGatesInfo() {
    std::lock_guard<std::mutex> lock(mutex);
    vector<GateViewModel> gateViewVec;
    for (const auto &gate: airport.getTerminal().getGates()) {
        GateViewModel gateViewModel;
        gateViewModel.gateID = gate.getIndex();
        if (gate.isGateAvailableForPlanes())
            gateViewModel.statusText = "Planes";
        else if (gate.isGateAvailableForEnteringPassengers())
            gateViewModel.statusText = "Entering Passengers";
        else if (gate.isGateAvailableForExitingPassengers())
            gateViewModel.statusText = "Exiting Passengers";
        else
            gateViewModel.statusText = "None";
        gateViewModel.currentPlaneId = gate.getCurrentPlaneId();
        gateViewModel.limit = gate.getLimit();
        gateViewVec.push_back(gateViewModel);
    }
    return gateViewVec;
}

