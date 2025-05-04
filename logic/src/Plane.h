//
// Created by Skipper on 01.05.2025.
//

#ifndef PLANE_H
#define PLANE_H
#include <random>
#include <string>


enum class PlaneStatus {
    Arriving,
    Landing,
    Disembarking,
    TurnaroundCheck,
    Refueling,
    Boarding,
    TakingOff,
    InFlight
};

class Airport;



class Plane {

public:
    Plane(Airport& airport, std::string flightNumber, int passengersOnBoard, int passengerLimit, int currentFuel, int fuelCapacity)
    : airport(airport), flightNumber(flightNumber), passengerLimit(passengerLimit), passengersOnBoard(passengersOnBoard),
      currentFuel(currentFuel), fuelCapacity(fuelCapacity) {
    }

    void run();

    [[nodiscard]] std::string getFlightNumber() const {
        return flightNumber;
    }

    [[nodiscard]] int getPassengerLimit() const {
        return passengerLimit;
    }

    [[nodiscard]] int getPassengersOnBoard() const {
        return passengersOnBoard;
    }

    [[nodiscard]] int getFuelNeeded() const {
        return currentFuel;
    }

    [[nodiscard]] PlaneStatus getStatus() const {
        return status;
    }
    static std::string randomFlightID() {
        std::string id = "";
        for (int i = 0; i < 3; ++i) {
            id += 'A' + rand() % 26; // Random uppercase letter
        }
        id+=" ";
        id+=std::to_string((rand() % 900+100)); // Random number
        return id;
    }
    int randInt(int min, int max) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(mt);
    }


private:
    Airport& airport;
    std::string flightNumber = "";
    int passengerLimit = 0;
    int passengersOnBoard = 0;
    int currentFuel = 0;
    int currentRunway = 0;
    int fuelCapacity = 0;
    PlaneStatus status = PlaneStatus::Arriving;


    void land();
    void disembarkPassengers();
    void refuel();
    void turnaroundCheck();
    void boardPassengers();
    void takeOff();



};



#endif //PLANE_H
