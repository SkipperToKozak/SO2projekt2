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
        planeViewModel.startingDelay = plane.getStartingDelay();
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
            gateViewModel.statusText = "Entering";
        else if (gate.isGateAvailableForExitingPassengers())
            gateViewModel.statusText = "Exiting";
        else
            gateViewModel.statusText = "None";
        gateViewModel.currentPlaneId = gate.getCurrentPlaneId();
        gateViewModel.limit = gate.getLimit();
        gateViewVec.push_back(gateViewModel);
    }
    return gateViewVec;
}

vector<RunwayViewModel> AirportController::getRunwaysInfo() {
    std::lock_guard<std::mutex> lock(mutex);
    vector<RunwayViewModel> runwayViewVec;
    cout << "[AIRPORT CONTROLLER] ";
    cout << "Getting runways info ";
    cout << airport.getFlightControlTower().getRunways().size() << endl;
    for (const auto &runway: airport.getFlightControlTower().getRunways()) {
        RunwayViewModel runwayViewModel;
        runwayViewModel.runwayID = runway.getIndex();
        // runwayViewModel.sizeT = airport.getFlightControlTower().getRunways().size();
        if (runway.isRunwayAvailable())
            runwayViewModel.statusText = "Available";
        else
            runwayViewModel.statusText = "Occupied";
        runwayViewModel.currentPlaneId = runway.getCurrentPlaneID();
        runwayViewVec.push_back(runwayViewModel);
    }
    return runwayViewVec;
}

vector<TechSupportViewModel> AirportController::getTechSupportInfo() {
    std::lock_guard<std::mutex> lock(mutex);
    vector<TechSupportViewModel> techSupportViewVec;
    for (const auto &techSupport: airport.getGroundServices().getTechSupportCars()) {
        TechSupportViewModel techSupportViewModel;
        techSupportViewModel.maintenanceID = techSupport.getMaintenanceID();
        techSupportViewModel.gateIndex = techSupport.getGateIndex();
        techSupportViewModel.maintenanceType = toString(techSupport.getMaintenanceType());
        techSupportViewModel.planeId = techSupport.getPlaneId();

        techSupportViewVec.push_back(techSupportViewModel);
    }
    return techSupportViewVec;
}

