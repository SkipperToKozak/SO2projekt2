//
// Created by Skipper on 01.05.2025.
//

#ifndef PLANE_H
#define PLANE_H
#include <condition_variable>
#include <random>
#include <string>


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

class Airport;



class Plane {

    std::mutex mutex;
    Airport& airport;
    std::string flightNumber = "";
    int passengerLimit = 0;
    int passengersOnBoard = 0;
    int currentFuel = 0;
    int currentRunway = 0;
    int fuelCapacity = 0;
    PlaneStatus status = PlaneStatus::Arriving;

    bool ready;
    std::condition_variable cv;


    void land();
    void disembarkPassengers();
    void refuel();
    void turnaroundCheck();
    void boardPassengers();
    void taxiing();
    void takeOff();


public:
    Plane(Airport& airport, std::string flightNumber, int passengersOnBoard, int passengerLimit, int currentFuel, int fuelCapacity)
    : airport(airport), flightNumber(flightNumber), passengerLimit(passengerLimit), passengersOnBoard(passengersOnBoard),
      currentFuel(currentFuel), fuelCapacity(fuelCapacity) {
    }
    //blokowanie kopiowania aby mutex mogł byc w klasie
    Plane(const Plane&) = delete;
    Plane& operator=(const Plane&) = delete;

    Plane(Plane&& other) noexcept
    : airport(other.airport), // Referencja — można tylko skopiować
    flightNumber(std::move(other.flightNumber)),
    passengerLimit(other.passengerLimit),
    passengersOnBoard(other.passengersOnBoard),
    currentFuel(other.currentFuel),
    currentRunway(other.currentRunway),
    fuelCapacity(other.fuelCapacity),
    status(other.status),
    ready(other.ready){
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





};



#endif //PLANE_H
