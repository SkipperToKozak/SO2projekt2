//
// Created by Skipper on 01.05.2025.
//

#ifndef PLANE_H
#define PLANE_H
#include <string>

#include "resources/Runway.h"

enum class PlaneStatus {
    Arriving,
    Landing,
    Disembarking,
    Refueling,
    Boarding,
    TakingOff,
    InFlight
};

class Plane {
    Plane(std::string flightNumber, int passengersOnBoard, int passengerLimit, int currentFuel, int fuelCapacity)
            : flightNumber(flightNumber), passengerLimit(passengerLimit), passengersOnBoard(passengersOnBoard),
    currentFuel(currentFuel), fuelCapacity(fuelCapacity) {}

public:
    void run();
    void land();
    void disembarkPassengers();
    void refuel();
    void boardPassengers();
    void takeOff();

    [[nodiscard]] std::string get_flight_number() const {
        return flightNumber;
    }

    [[nodiscard]] int get_passenger_limit() const {
        return passengerLimit;
    }

    [[nodiscard]] int get_passengers_on_board() const {
        return passengersOnBoard;
    }

    [[nodiscard]] int get_fuel_needed() const {
        return currentFuel;
    }

    [[nodiscard]] PlaneStatus get_status() const {
        return status;
    }

    [[nodiscard]] Runway * get_runway() const {
        return runway;
    }

    void set_runway(Runway *runway) {
        this->runway = runway;
    }

    static std::string randomFlightNumber();
private:
    std::string flightNumber = "";
    int passengerLimit = 0;
    int passengersOnBoard = 0;
    int currentFuel = 0;
    int currentRunway = 0;
    int fuelCapacity = 0;
    Runway* runway = nullptr;
    PlaneStatus status = PlaneStatus::Arriving;



};



#endif //PLANE_H
