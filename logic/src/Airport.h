//
// Created by Skipper on 01.05.2025.
//

#ifndef AIRPORT_H
#define AIRPORT_H

#include <vector>
#include <mutex>
#include <thread>

#include "FlightControlTower.h"
#include "Passenger.h"
#include "Plane.h"

//AIRPORT CONFIG
#define NUM_RUNWAYS 3
#define NUM_HANGARS 5
#define NUM_TERMINALS 2
#define NUM_GATES 2
#define NUM_PASSENGERS 10
#define NUM_PLANES 3

//PLANES INIT CONFIG
#define PLANE_PASSENGER_LIMIT 100
#define MAX_PLANE_FUEL_CAPACITY 1000
#define MIN_PLANE_FUEL_CAPACITY 400
// #define MIN_PLANE_FUEL_NEEDED 100


using namespace std;

class FlightControlTower;
class Passenger;
class Plane;
class Runway;

class Airport {
    vector<Plane> planes;
    vector<thread> planes_threads;

    vector<Passenger> passengers;
    vector<thread> passengers_threads;

    FlightControlTower flightControlTower;




public:

    Airport()
        : flightControlTower(NUM_RUNWAYS, NUM_GATES) { // Inicjalizacja flightControlTower
    }

    vector<Passenger> getPassengers() {
        return passengers;
    }

    FlightControlTower *getFlightControlTower() {
        return &flightControlTower;
    };
    void initialize();
    void run();

};



#endif //AIRPORT_H
