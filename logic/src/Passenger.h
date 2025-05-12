//
// Created by Skipper on 01.05.2025.
//

#ifndef PASSENGER_H
#define PASSENGER_H

#include "Utilities/randomise.h"

enum class PassengerStatus {
    Waiting,
    Boarding,
    InFlight,
    Disembarked,
    Leaving
};

class Passenger {
    int number = 0;
    std::string planeID = "";
    PassengerStatus status = PassengerStatus::Waiting;
public:
    Passenger(std::string planeID) : planeID(planeID)
    {
        number = randInt(1, 10);
    }



};



#endif //PASSENGER_H
