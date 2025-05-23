//
// Created by Skipper on 20.05.2025.
//

#ifndef AIRPORTVIEW_H
#define AIRPORTVIEW_H


#pragma once
#include "AirportController.h"
// #include <vector>


class AirportView {
public:
    AirportView(AirportController &controller) : airportController(controller) {
    };

    void display();

    AirportController &airportController;

private:

public:
    // void show();
    //
    // void update(); // odświeżenie widoku
};


#endif //AIRPORTVIEW_H
