//
// Created by Skipper on 01.05.2025.
//

#ifndef PLANE_H
#define PLANE_H
#include <condition_variable>
#include <random>
#include <string>
#include <utility>

#include "utilities/randomise.h"


enum class PlaneStatus {
    Arriving,
    Landing,
    TaxiingFromRunway,
    Disembarking,
    TurnaroundCheck,
    Refueling,
    Boarding,
    WaitingForRunway,
    TaxiingToRunway,
    TakingOff,
    InFlight
};

inline std::string toString(PlaneStatus status) {
    switch (status) {
        case PlaneStatus::Arriving: return "Arriving";
        case PlaneStatus::Landing: return "Landing";
        case PlaneStatus::TaxiingFromRunway: return "TaxiingFromRunway";
        case PlaneStatus::Disembarking: return "Disembarking";
        case PlaneStatus::TurnaroundCheck: return "TurnaroundCheck";
        case PlaneStatus::Refueling: return "Refueling";
        case PlaneStatus::Boarding: return "Boarding";
        case PlaneStatus::WaitingForRunway: return "WaitingForRunway";
        case PlaneStatus::TaxiingToRunway: return "TaxiingToRunway";
        case PlaneStatus::TakingOff: return "TakingOff";
        case PlaneStatus::InFlight: return "InFlight";
        default: return "Unknown";
    }
}

class Airport;


class Plane {
    std::mutex mutex;
    Airport &airport;
    std::string flightNumber = "";
    int passengerLimit = 0;
    int passengersOnBoard = 0;
    int currentFuel = 0;
    int currentRunway = 0;
    int fuelCapacity = 0;
    int gateIndex = -1;
    PlaneStatus status = PlaneStatus::InFlight;
    int startingDelay;

    bool ready;
    std::condition_variable cv;


    void land();

    void disembarkPassengers();

    void refuel();

    void turnaroundCheck();

    void boardPassengers();

    void taxiing();

    void takeOff();

    void inFlight();

public:
    Plane(Airport &airport, std::string flightNumber, int passengersOnBoard, int passengerLimit, int currentFuel,
          int fuelCapacity, int startingDelay)
        : airport(airport), flightNumber(flightNumber), passengerLimit(passengerLimit),
          passengersOnBoard(passengersOnBoard),
          currentFuel(currentFuel), fuelCapacity(fuelCapacity), startingDelay(startingDelay) {
    }

    //blokowanie kopiowania aby mutex mogł byc w klasie
    Plane(const Plane &) = delete;

    Plane &operator=(const Plane &) = delete;

    Plane(Plane &&other) noexcept
        : airport(other.airport), // Referencja — można tylko skopiować
          flightNumber(std::move(other.flightNumber)),
          passengerLimit(other.passengerLimit),
          passengersOnBoard(other.passengersOnBoard),
          currentFuel(other.currentFuel),
          currentRunway(other.currentRunway),
          fuelCapacity(other.fuelCapacity),
          status(other.status),
          ready(other.ready) {
        // std::mutex i std::condition_variable nie są przenośne — pozostają domyślne
    }

    // //operator przenoszenia (na przyszlosc)
    // Plane& operator=(Plane&& other) noexcept {
    //     if (this != &other) {
    //         // airport = other.airport;
    //         passengerLimit = other.passengerLimit;
    //         passengersOnBoard = other.passengersOnBoard;
    //         currentFuel = other.currentFuel;
    //         fuelCapacity = other.fuelCapacity;
    //         flightNumber = std::move(other.flightNumber);
    //         // Mutex nie jest przenoszony, pozostaje bez zmian
    //     }
    //     return *this;
    // }

    void initialize();

    [[noreturn]] void run();

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

    [[nodiscard]] int getCurrentFuel() const {
        return currentFuel;
    }

    [[nodiscard]] int getFuelCapacity() const {
        return fuelCapacity;
    }

    [[nodiscard]] int getCurrentRunway() const {
        return currentRunway;
    }

    [[nodiscard]] PlaneStatus getStatus() const {
        return status;
    }

    std::string getStatusString() const {
        return toString(status);
    }

    [[nodiscard]] int getGateIndex() const {
        return gateIndex;
    }

    void setGateIndex(int gateIndex) {
        this->gateIndex = gateIndex;
    }


    static std::string randomFlightID() {
        std::string id = "";
        for (int i = 0; i < 3; ++i) {
            id += 'A' + randInt(0, 25); // Random uppercase letter
        }
        id += " ";
        id += std::to_string(randInt(100, 999)); // Random number
        return id;
    }
};


#endif //PLANE_H
