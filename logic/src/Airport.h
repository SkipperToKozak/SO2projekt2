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
#include "resources/Runway.h"
//AIRPORT CONFIG
#define NUM_RUNWAYS 2
#define NUM_HANGARS 5
#define NUM_TERMINALS 2
#define NUM_GATES 5
#define NUM_PASSENGERS 10
#define NUM_PLANES 10

//PLANES CONFIG
#define PLANE_PASSENGER_LIMIT 100
#define MAX_PLANE_FUEL_CAPACITY 1000
#define MIN_PLANE_FUEL_CAPACITY 400
// #define MIN_PLANE_FUEL_NEEDED 100


using namespace std;

class Airport {
    vector<Plane> planes;
    vector<thread> planes_threads;

    vector<Passenger> passengers;
    vector<thread> passengers_threads;

    FlightControlTower flightControlTower;

    vector<Runway> runways;


public:
    void initialize();
    void run();
};



#endif //AIRPORT_H
