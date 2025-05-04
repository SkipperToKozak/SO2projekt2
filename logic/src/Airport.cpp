//
// Created by Skipper on 01.05.2025.
//

#include "Airport.h"

#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

#include "FlightControlTower.h"
#include "Passenger.h"
#include "Plane.h"

using namespace std;

void Airport::initialize() {
    //przypisanie lotniska do wieży
    flightControlTower = FlightControlTower();
    flightControlTower.initialize();


    //Tworzenie pasażerów
    for (int i = 0; i < NUM_PASSENGERS; ++i) {
        passengers.emplace_back();
    }

    //Tworzenie samolotów
    for (int i = 0; i < NUM_PLANES; ++i) {
        string flightNumber = Plane::randomFlightID();

        // Sprawdzenie, czy numer lotu jest unikalny
        for (Plane plane : planes) {
            while (plane.getFlightNumber()==flightNumber) {
                flightNumber = Plane::randomFlightID();
            }
        }

        // Generowanie losowych danych dla samolotu
        int passengerLimit = rand() % PLANE_PASSENGER_LIMIT + 1;
        int passengersOnBoard = rand() % passengerLimit + 1;
        int fuelCapacity = rand() % (MAX_PLANE_FUEL_CAPACITY-MIN_PLANE_FUEL_CAPACITY)+ MIN_PLANE_FUEL_CAPACITY;
        int currentFuel = rand() % (fuelCapacity)+1;

        Plane plane(*this, flightNumber, passengersOnBoard, passengerLimit, currentFuel, fuelCapacity);
        //Przypisanie do samolotu lotniska
        planes.emplace_back(plane);
        std::cout << "Plane " << flightNumber << " is running." << std::endl;
    }

    //Laubching planes' threads
    for (auto& plane : planes) {
        planes_threads.emplace_back(&Plane::run, &plane);
        this_thread::sleep_for(10ms); // Sleep for 100 milliseconds to simulate staggered start
    }
    //Waiting for planes' threads to finish
    for (int i = 0; i < NUM_PLANES; i++) {
        planes_threads[i].join();
    }




    std::cout << "Airport initialized." << std::endl;

}


void Airport::run() {
    std::cout << "Airport simulation started." << std::endl;



    // Simulate boarding and disembarking passengers


    // for (auto& passenger : passengers) {
    //     passenger.board();
    //     std::cout << "Passenger is boarding." << std::endl;
    // }


    std::cout << "Airport simulation ended." << std::endl;
}
