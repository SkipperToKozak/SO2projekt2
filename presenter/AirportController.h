//
// Created by Skipper on 20.05.2025.
//

#ifndef AIRPORTCONTROLLER_H
#define AIRPORTCONTROLLER_H


#pragma once
#include "src/Airport.h"
// #include "src/Airport.h"
// #include "AirportView.h"

class AirportController {
public:
    AirportController() {
        airport.initialize();
        airport.run();
    };
    Airport airport;
    // AirportView &view;

public:
    // AirportController(Airport &airport, AirportView &view);

    // void run(); // główna pętla odświeżania widoku
};


#endif //AIRPORTCONTROLLER_H
