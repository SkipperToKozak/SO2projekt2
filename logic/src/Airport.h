//
// Created by Skipper on 01.05.2025.
//

#ifndef AIRPORT_H
#define AIRPORT_H

#include <deque>
#include <list>
#include <vector>
#include <mutex>
#include <thread>

#include "ATControlTower.h"
#include "GroundServices.h"
#include "Passenger.h"
#include "Plane.h"
#include "utilities/Config.h"

//AIRPORT CONFIG
#define NUM_RUNWAYS 4
#define NUM_HANGARS 5
#define NUM_TERMINALS 2
#define NUM_GATES (NUM_RUNWAYS*3)
#define NUM_PASSENGERS 15
#define NUM_PLANES 10

//PLANES INIT CONFIG
#define PLANE_PASSENGER_LIMIT 20
#define MAX_PLANE_FUEL_CAPACITY 1000
#define MIN_PLANE_FUEL_CAPACITY 400
// #define MIN_PLANE_FUEL_NEEDED 100
#define STARTING_DELAY 30

using namespace std;

class ATControlTower;
class Passenger;
class Plane;
class Runway;

class Airport {
    vector<Plane> planes;
    int planesNumber = 0;
    vector<thread> planes_threads;


    list<Passenger> passengers;
    int passengersNumber = 0;
    vector<thread> passengers_threads;

    ATControlTower atControlTower;
    Terminal terminal;
    GroundServices groundServices;

    int airportFuel = 3000; // Initial fuel available at the airport

    std::mutex passengersMutex;

public:
    Airport(Config config)
        : atControlTower(*this, stoi(config.getValue("RUNWAYS"))),
          terminal(*this, stoi(config.getValue("RUNWAYS")) * 3),
          groundServices(stoi(config.getValue("RUNWAYS")) * 3) {
    }

    bool isFlightNumberAvailable(string flightNumber);

    list<Passenger> &getPassengers() {
        // std::lock_guard<std::mutex> lock(passengersMutex);
        cout << "POBIERAM PASAZEROW" << endl;
        return passengers;
    }

    vector<Plane> &getPlanes() {
        return planes;
    }

    ATControlTower &getFlightControlTower() {
        return atControlTower;
    };

    Terminal &getTerminal() {
        return terminal;
    }

    GroundServices &getGroundServices() {
        return groundServices;
    }

    int getAirportFuel() {
        return airportFuel;
    }

    void setAirportFuel(int fuel) {
        airportFuel = fuel;
    }


    void initialize();

    void run();

    void cleanupFinishedPassengers();

    void addPassengersGettingOnAPlane();

    void addPassengersLeavingThePlane(int &size);

    void addPlanes();
};


#endif //AIRPORT_H
