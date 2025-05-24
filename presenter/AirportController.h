//
// Created by Skipper on 20.05.2025.
//

#ifndef AIRPORTCONTROLLER_H
#define AIRPORTCONTROLLER_H


#pragma once
#include "src/Airport.h"
// #include "src/Airport.h"
// #include "AirportView.h"

struct PlaneViewModel {
    std::string flightNumber;
    std::string statusText;
    int passengerLimit;
    int passengersOnBoard;
    int currentFuel;
    int fuelCapacity;
    int currentRunway;
    int gateIndex;
    int startingDelay;
};

struct PassengerViewModel {
    int passengerID;
    int gateIndex;
    int happiness;
    int numberOf;
    std::string flightNumber;
    std::string statusText;
};

struct RunwayViewModel {
    int runwayID;
    std::string currentPlaneId;
    std::string statusText;
};

struct GateViewModel {
    int gateID;
    int limit;
    std::string currentPlaneId;
    std::string statusText;
};

class AirportController {
public:
    AirportController() {
        airport.initialize();
    };
    Airport airport;

    vector<PlaneViewModel> getPlanesInfo();

    vector<PassengerViewModel> getPassengersInfo();

    vector<GateViewModel> getGatesInfo();

    vector<RunwayViewModel> getRunwaysInfo();

    // AirportView &view;

public:
    // AirportController(Airport &airport, AirportView &view);

    // void run(); // główna pętla odświeżania widoku
};


#endif //AIRPORTCONTROLLER_H
