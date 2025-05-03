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


    runways = vector<Runway>(NUM_RUNWAYS);


    //Tworzenie pasażerów
    for (int i = 0; i < NUM_PASSENGERS; ++i) {
        passengers.emplace_back();
    }

    //Tworzenie samolotów
    for (int i = 0; i < NUM_PLANES; ++i) {
        string flightNumber = Plane::randomFlightNumber();

        // Sprawdzenie, czy numer lotu jest unikalny
        for (Plane plane : planes) {
            while (plane.get_flight_number()==flightNumber) {
                flightNumber = Plane::randomFlightNumber();
            }
        }

        // Generowanie losowych danych dla samolotu
        int passengerLimit = rand() % PLANE_PASSENGER_LIMIT + 1;
        int passengersOnBoard = rand() % passengerLimit + 1;
        int fuelCapacity = rand() % (MAX_PLANE_FUEL_CAPACITY-MIN_PLANE_FUEL_CAPACITY)+ MIN_PLANE_FUEL_CAPACITY;
        int currentFuel = rand() % (fuelCapacity)+1;


        //Przypisane do samolotu
        planes.emplace_back(flightNumber,passengersOnBoard, passengerLimit, currentFuel, fuelCapacity);
        std::cout << "Plane " << flightNumber << " is running." << std::endl;
    }

    // //Uruchamianie wątków
    // for (auto& passenger : passengers) {
    //     passengers_threads.emplace_back(&Passenger::run, &passenger);
    // }
    for (auto& plane : planes) {
        planes_threads.emplace_back(&Plane::run, &plane);
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


    // Simulate flight operations
    for (auto& plane : planes) {
        plane.run();
        std::cout << "Plane is taking off." << std::endl;
    }

    std::cout << "Airport simulation ended." << std::endl;
}
