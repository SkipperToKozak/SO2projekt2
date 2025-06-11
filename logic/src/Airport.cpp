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

    // //Tworzenie pasażerów
    // for (int i = 0; i < NUM_PASSENGERS; i++) {
    //     passengers.emplace_back(terminal, Plane::randomFlightID(), ++passengersNumber);
    // }

    //Tworzenie samolotów
    for (int i = 0; i < NUM_PLANES; i++) {
        string flightNumber = Plane::randomFlightID();

        // Sprawdzenie, czy numer lotu jest unikalny
        for (Plane &plane: planes) {
            while (plane.getFlightNumber() == flightNumber) {
                flightNumber = Plane::randomFlightID();
            }
        }

        // Generowanie losowych danych dla samolotu
        int passengerLimit = rand() % PLANE_PASSENGER_LIMIT + 10;
        int passengersOnBoard = rand() % passengerLimit + 1;
        int fuelCapacity = rand() % (MAX_PLANE_FUEL_CAPACITY - MIN_PLANE_FUEL_CAPACITY) + MIN_PLANE_FUEL_CAPACITY;
        int currentFuel = rand() % (fuelCapacity - int(0.6 * fuelCapacity) - 1) + int(0.6 * fuelCapacity);

        //Przypisanie do samolotu lotniska
        planes.emplace_back(*this, flightNumber, passengersOnBoard, passengerLimit, currentFuel, fuelCapacity,
                            i * STARTING_DELAY + 1);
    }


    std::cout << "Airport initialized." << std::endl;
}


void Airport::run() {
    std::cout << "Airport simulation started." << std::endl;


    // Simulate boarding and disembarking passengers

    thread passengerGenEnteringThread = thread(&Airport::addPassengersGettingOnAPlane, this);
    thread cleanerThread = thread(&Airport::cleanupFinishedPassengers, this);
    thread fuelCheckThread = thread(&Airport::checkFuelLevel, this);
    // for (auto& passenger : passengers) {
    //     passenger.board();
    //     std::cout << "Passenger is boarding." << std::endl;
    // }
    //Launching planes' threads
    for (auto &plane: planes) {
        planes_threads.emplace_back(&Plane::run, &plane);
        this_thread::sleep_for(10ms); // Sleep for 100 milliseconds to simulate staggered start
        std::cout << "Plane " << plane.getFlightNumber() << " is running." << std::endl;
    }
    // Launching passengers' threads
    // for (auto &passenger: passengers) {
    //     passengers_threads.emplace_back(&Passenger::run, &passenger);
    //     this_thread::sleep_for(10ms); // Sleep for 100 milliseconds to simulate staggered start
    //     std::cout << "Passenger " << passenger.getPassengerID() << " is running." << std::endl;
    // }
    // addPassengersGettingOnAPlane();

    // addPassengersLeavingThePlane(5);


    // cleanupFinishedPassengers();
    //Waiting for passengers' threads to finish
    for (auto &passengers_thread: passengers_threads) {
        if (passengers_thread.joinable()) passengers_thread.join();

        cout << "[AIRPORT-CLEANER] ";
        cout << "Passenger thread is over." << endl;
    }
    //Waiting for planes' threads to finish
    for (auto &planes_thread: planes_threads) {
        cout << "[AIRPORT-CLEANER] ";
        cout << "Plane thread is over." << endl;
        planes_thread.join();
    }
    cleanerThread.join();
    passengerGenEnteringThread.join();
    fuelCheckThread.join();

    std::cout << "Airport simulation ended." << std::endl;
}

void Airport::cleanupFinishedPassengers() {
    while (true) {
        this_thread::sleep_for(1s); {
            std::lock_guard<std::mutex> lock(passengersMutex);
            std::cout << "Calling cleanup" << std::endl;
            auto pit = passengers.begin();
            auto tit = passengers_threads.begin();
            while (pit != passengers.end() && tit != passengers_threads.end()) {
                if (pit->getPassengerFinished() && tit->joinable()) {
                    tit->join();
                    tit = passengers_threads.erase(tit);
                    pit = passengers.erase(pit);
                    std::cout << "[CLEANUP] Passenger zakończył i został usunięty.\n";
                } else {
                    ++pit;
                    ++tit;
                }
            }
        }
    }
}

void Airport::addPassengersGettingOnAPlane() {
    while (true) {
        this_thread::sleep_for(1s); {
            std::lock_guard<std::mutex> lock(passengersMutex);
            if (passengers.size() < NUM_PASSENGERS) {
                // 1) wstawiamy nowego pasażera na koniec deque
                passengers.emplace_back(terminal, Plane::randomFlightID(), ++passengersNumber);

                // 2) bierzemy referencję do tego obiektu
                Passenger &p = passengers.back();

                // 3) tworzymy wątek, który wywoła metodę run() na tym obiekcie
                passengers_threads.emplace_back(&Passenger::run, &p);

                // (opcjonalnie) mała przerwa, żeby starty były „rozsiane”
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                std::cout << "[AIRPORT] Passenger " << p.getPassengerID() << " started." << std::endl;
            }
        }
    }
}
void Airport::checkFuelLevel() {
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Check fuel level every 5 seconds
        {
            if (airportFuel < 0.95 * MIN_AIRPORT_FUEL) {
                std::cout << "[AIRPORT] Fuel level is low. Refueling..." << std::endl;
                groundServices.getRefuellingTruck().goForFuel(airportFuel, MIN_AIRPORT_FUEL);
            }
        }
    }

}

void Airport::addPassengersLeavingThePlane(int &size) {
    std::lock_guard<std::mutex> lock(passengersMutex);
    while (size > 0) {
        int psize;
        if (size > 10) {
            //TODO zahrdcodowany max na grupa pasazerow = 10
            psize = randInt(1, 10);
        } else {
            psize = randInt(1, size);
        }
        size -= psize;

        // 1) wstawiamy nowego pasażera na koniec deque
        passengers.emplace_back(terminal, ++passengersNumber, psize);

        // 2) bierzemy referencję do tego obiektu
        Passenger &p = passengers.back();

        // 3) tworzymy wątek, który wywoła metodę run() na tym obiekcie
        passengers_threads.emplace_back(&Passenger::runLeavingThePlane, &p);

        // (opcjonalnie) mała przerwa, żeby starty były „rozsiane”
        std::this_thread::sleep_for(1s);
        std::cout << "[AIRPORT] Passenger " << p.getPassengerID() << " started." << std::endl;
    }
}

void Airport::addPlanes() {
    // for (int i = 0; i < NUM_PLANES; ++i) {
    //     planes.emplace_back();
    // }
}

bool Airport::isFlightNumberAvailable(string flightNumber) {
    for (auto &plane: planes) {
        if (plane.getFlightNumber() == flightNumber) {
            cout << plane.getFlightNumber() << endl;
            cout << flightNumber << endl;
            return false; // Flight number is not available
        }
    }
    return true; // Flight number is available
}

