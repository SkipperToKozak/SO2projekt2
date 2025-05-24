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
    OnBoard,
    // InFlight,
    ExitingPlane,
    Disembarked,
    CollectingLuggage,
    Leaving
};

inline std::string toString(PassengerStatus status) {
    switch (status) {
        case PassengerStatus::ArrivingAtAirport: return "ArrivingAtAirport";
        case PassengerStatus::CheckingIn: return "CheckingIn";
        case PassengerStatus::SecurityCheck: return "SecurityCheck";
        case PassengerStatus::WaitingAtGate: return "WaitingAtGate";
        case PassengerStatus::Boarding: return "Boarding";
        case PassengerStatus::OnBoard: return "OnBoard";
        case PassengerStatus::ExitingPlane: return "ExitingPlane";
        case PassengerStatus::Disembarked: return "Disembarked";
        case PassengerStatus::CollectingLuggage: return "CollectingLuggage";
        case PassengerStatus::Leaving: return "Leaving";
        default: return "Unknown";
    }
}

class Passenger {
    Terminal &terminal;
    std::atomic<bool> isFinished = false;
    int passengerID = 0;
    int numberOf = 0;
    int happiness = 100;
    int gateIndex = 1;
    std::string flightNumber = " ";
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
    Passenger(Terminal &terminal, std::string flightNumber, int passengerID) : terminal(terminal),
                                                                               flightNumber("TEMP"),
                                                                               passengerID(passengerID) {
        numberOf = randInt(1, 10);
    }

    explicit Passenger(Terminal &terminal, int passengerID, int numberOf): terminal(terminal), numberOf(numberOf),
                                                                           passengerID(passengerID) {
    }


    // Passenger(Passenger &&other) noexcept
    //     : terminal(other.terminal),
    //       passengerID(other.passengerID),
    //       numberOf(other.numberOf),
    //       happiness(other.happiness),
    //       gateIndex(other.gateIndex),
    //       flightNumber(std::move(other.flightNumber)),
    //       status(other.status) {
    // }

    [[nodiscard]] int getPassengerID() const {
        return passengerID;
    }

    void run();

    void runGettingOnAPlane();

    void runLeavingThePlane();

    std::string getFlightNumber() const {
        return flightNumber;
    };

    std::string getPassengerStatusString() const {
        return toString(status);
    }

    PassengerStatus getPassengerStatus() const {
        return status;
    }

    int getGateIndex() const {
        return gateIndex;
    }

    void setGateIndex(int gateeIndex) {
        gateIndex = gateeIndex;
    }

    int getHappiness() const {
        return happiness;
    }

    int getNumberOf() const {
        return numberOf;
    }

    bool getPassengerFinished() const {
        return isFinished;
    }
};


#endif //PASSENGER_H
