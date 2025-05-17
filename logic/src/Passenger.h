//
// Created by Skipper on 01.05.2025.
//

#ifndef PASSENGER_H
#define PASSENGER_H

#include <utility>

#include "Terminal.h"
#include "Utilities/randomise.h"

enum class PassengerStatus {
    ArrivingAtAirport,
    CheckingIn,
    SecurityCheck,
    WaitingAtGate,
    Boarding,
    // InFlight,
    ExitingPlane,
    Disembarked,
    Leaving
};

class Passenger {
    Terminal &terminal;
    int passengerID = 0;
    int numberOf = 0;
    int happiness = 100;
    int gateIndex = -1;
    std::string planeID = " ";
    PassengerStatus status = PassengerStatus::ArrivingAtAirport;

    //entering a plane
    void arriveAtAirport();

    void checkIn();

    void passSecurityCheck();

    void waitAtGate();

    void boardPlane();

    //leaving a plane
    void exitPlane();

    void proceedToTerminal();

    void collectLuggage();

    void leaveAirport();

public:
    Passenger(Terminal &terminal, std::string planeID, int passengerID) : terminal(terminal),
                                                                          planeID(std::move(planeID)),
                                                                          passengerID(passengerID) {
        numberOf = randInt(1, 10);
    }

    explicit Passenger(Terminal &terminal): terminal(terminal) {
        numberOf = randInt(1, 10);
    }

    [[nodiscard]] int getPassengerID() const {
        return passengerID;
    }

    void run();

    void runGettingOnAPlane();

    void runLeavingThePlane();
};


#endif //PASSENGER_H
