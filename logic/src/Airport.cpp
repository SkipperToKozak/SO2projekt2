//
// Created by Skipper on 01.05.2025.
//

#include "Airport.h"

#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

#include "ATControlTower.h"
#include "Passenger.h"
#include "Plane.h"

using namespace std;

void Airport::initialize() {
    //przypisanie lotniska do wieży

    atControlTower.initialize();


    //Tworzenie pasażerów
    for (int i = 0; i < NUM_PASSENGERS; ++i) {
        passengers.emplace_back(terminal, Plane::randomFlightID(), ++passengersNumber);
    }

    //Tworzenie samolotów
    for (int i = 0; i < NUM_PLANES; ++i) {
        string flightNumber = Plane::randomFlightID();

        // Sprawdzenie, czy numer lotu jest unikalny
        for (Plane &plane: planes) {
            while (plane.getFlightNumber() == flightNumber) {
                flightNumber = Plane::randomFlightID();
            }
        }

        // Generowanie losowych danych dla samolotu
        int passengerLimit = rand() % PLANE_PASSENGER_LIMIT + 1;
        int passengersOnBoard = rand() % passengerLimit + 1;
        int fuelCapacity = rand() % (MAX_PLANE_FUEL_CAPACITY - MIN_PLANE_FUEL_CAPACITY) + MIN_PLANE_FUEL_CAPACITY;
        int currentFuel = rand() % (fuelCapacity) + 1;

        //Przypisanie do samolotu lotniska
        planes.emplace_back(*this, passengersOnBoard, passengerLimit, currentFuel, fuelCapacity);
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
    //Laubching planes' threads
    for (auto &plane: planes) {
        planes_threads.emplace_back(&Plane::run, &plane);
        this_thread::sleep_for(10ms); // Sleep for 100 milliseconds to simulate staggered start
        std::cout << "Plane " << plane.getFlightNumber() << " is running." << std::endl;
    }
    //Launching passengers' threads
    for (auto &passenger: passengers) {
        passengers_threads.emplace_back(&Passenger::run, &passenger);
        this_thread::sleep_for(10ms); // Sleep for 100 milliseconds to simulate staggered start
        std::cout << "Passenger " << passenger.getPassengerID() << " is running." << std::endl;
    }
    // addPassengersGettingOnAPlane();

    //Waiting for passengers' threads to finish
    for (auto &passengers_thread: passengers_threads) {
        passengers_thread.join();
        cout << "[AIRPORT] ";
        cout << "Passenger thread is over." << endl;
    }
    //Waiting for planes' threads to finish
    for (auto &planes_thread: planes_threads) {
        planes_thread.join();
    }

    std::cout << "Airport simulation ended." << std::endl;
}

void Airport::addPassengersGettingOnAPlane() {
    passengers.emplace_back(terminal, Plane::randomFlightID(), ++passengersNumber);
    passengers_threads.emplace_back(&Passenger::runGettingOnAPlane, &passengers.back());
}

void Airport::addPassengersLeavingThePlane() {
    int lastPassengerIndex = 0;
    if (!passengers.empty()) {
        lastPassengerIndex = passengers.size() - 1;
    } else {
        cout << "[AIRPORT] ";
        cout << "Airport passenger list is empty." << endl;
    }
    for (int i = 0; i < NUM_PASSENGERS; ++i) {
        passengers.emplace_back(terminal, Plane::randomFlightID(), ++passengersNumber);
        passengers_threads.emplace_back(&Passenger::runLeavingThePlane, &passengers[i + lastPassengerIndex]);
    }
}

void Airport::addPlanes() {
    // for (int i = 0; i < NUM_PLANES; ++i) {
    //     planes.emplace_back();
    // }
}
