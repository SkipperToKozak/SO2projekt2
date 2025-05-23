//
// Created by Skipper on 01.05.2025.
//

#include "Plane.h"

#include <chrono>
#include <iostream>
#include <thread>
#include <random>
#include <mutex>
#include <condition_variable>

#include "Airport.h"
#include "ATControlTower.h"


void Plane::land() {
    // Implement the logic for landing
    while (startingDelay > 0) {
        this_thread::sleep_for(1s); // Starting delay for the plane
        startingDelay--;
        currentFuel -= 1;
    }
    startingDelay = randInt(2, 6);
    if (airport.getFlightControlTower().requestLanding(*this)) {
        startingDelay = 0;
        std::cout << "[Plane " << flightNumber << "] ";
        std::cout << "is landing. " << std::endl;
        status = PlaneStatus::Landing;
        std::this_thread::sleep_for(std::chrono::seconds(randInt(20, 35))); //LANDING SET FOR 10s
    } else {
        std::cout << "[Plane " << flightNumber << "] ";
        std::cout << "is waiting for landing." << std::endl;
        status = PlaneStatus::Arriving;
    }
}

void Plane::disembarkPassengers() {
    if (airport.getFlightControlTower().requestDisembarking(*this, gateIndex)) {
        std::cout << "[Plane " << flightNumber << "] ";
        std::cout << "is taxiing to gate " << gateIndex << std::endl;
        status = PlaneStatus::TaxiingFromRunway;
        std::this_thread::sleep_for(std::chrono::seconds(randInt(5, 10))); //TAXIING SET FOR 10s
        airport.getFlightControlTower().releaseRunway(*this);
        std::cout << "[Plane " << flightNumber << "] ";
        std::cout << "is disembarking passengers." << std::endl;
        status = PlaneStatus::Disembarking;
        std::this_thread::sleep_for(std::chrono::seconds(randInt(3, 8))); //DISAMBARKING SET FOR 10s
    } else {
        //TODO mam wrazenie ze cos jest nie tak z czasem oczekiwania na koniec disembarkingu. Za dlugo to trwa, powinno kilka sekund (tylko gdy samolot nie uzyskal wczesniej gate'a)
        std::cout << "[Plane " << flightNumber << "] ";
        std::cout << "is waiting for disembarkation." << std::endl;
        this_thread::sleep_for(std::chrono::seconds(15));
        disembarkPassengers();
    }
    // Implement the logic for disembarking passengers
    status = PlaneStatus::Disembarking;
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 10)); //DISEMBARKING SET FOR 10s
}

void Plane::turnaroundCheck() {
    std::cout << "[Plane " << flightNumber << "] ";
    // Implement the logic for disembarking passengers
    std::cout << "Turnaround check." << std::endl;
    status = PlaneStatus::TurnaroundCheck;
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 10)); //DISEMBARKING SET FOR 10s
}

void Plane::refuel() {
    status = PlaneStatus::Refueling;
    std::cout << "[Plane " << flightNumber << "] ";
    // Implement the logic for refueling
    std::cout << "Refueling plane." << std::endl;
    while (currentFuel < fuelCapacity) {
        if (currentFuel + 20 > fuelCapacity) {
            currentFuel = fuelCapacity;
        } else {
            currentFuel += 20;
        }
        this_thread::sleep_for(1s);
        std::cout << "[Plane " << flightNumber << "] ";
        std::cout << "Refueling plane. Current fuel: " << currentFuel << std::endl;
    }

    // std::this_thread::sleep_for(std::chrono::seconds(20)); //REFUELING SET FOR 20s
}


void Plane::boardPassengers() {
    std::cout << "[Plane " << flightNumber << "] ";
    // Implement the logic for boarding passengers
    std::cout << "Boarding passengers." << std::endl;
    status = PlaneStatus::Boarding;
    airport.getFlightControlTower().requestBoarding(*this);

    std::this_thread::sleep_for(std::chrono::seconds(30)); //BOARDING SET FOR 30s
    status = PlaneStatus::WaitingForRunway;
}

void Plane::taxiing() {
    std::cout << "[Plane " << flightNumber << "] ";
    std::cout << "Requesting runway." << std::endl;

    if (airport.getFlightControlTower().requestTaxiing(*this)) {
        std::cout << "[Plane " << flightNumber << "] ";
        std::cout << "Heading to runway." << std::endl;
        status = PlaneStatus::TaxiingToRunway;
    } else {
        std::cout << "Runway is not available. Waiting..." << std::endl;
        // std::unique_lock<std::mutex> lock(mutex);
        // cv.wait(lock, [this] { return ready; });
        // ready = false;  // Resetuj flagę
        this_thread::sleep_for(std::chrono::seconds(5));
        taxiing(); // Ponów próbę
        return;
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));
}


void Plane::takeOff() {
    std::cout << "[Plane " << flightNumber << "] ";
    // Implement the logic for taking off
    std::cout << "Plane is taking off." << std::endl;
    status = PlaneStatus::TakingOff;
    std::this_thread::sleep_for(std::chrono::seconds(12)); //TAKEOFF SET FOR 12s
    std::cout << "[Plane " << flightNumber << "] ";
    std::cout << "Took off" << std::endl;
    airport.getFlightControlTower().releaseRunway(*this);
}

void Plane::inFlight() {
    cout << "[Plane " << flightNumber << "] ";
    cout << "Plane is in flight." << endl;
    status = PlaneStatus::InFlight;
    std::this_thread::sleep_for(std::chrono::seconds(30)); //FLIGHT SET FOR 30s
}


[[noreturn]] void Plane::run() {
    // this_thread::sleep_for(chrono::seconds(startingDelay)); // Starting delay for the plane
    // Implement the logic for the plane's operations
    while (true) {
        while (startingDelay > 0) {
            this_thread::sleep_for(1s); // Starting delay for the plane
            startingDelay--;
            currentFuel -= 1;
        }
        initialize();
        while (status != PlaneStatus::Landing) {
            land();
        }
        disembarkPassengers();
        turnaroundCheck();
        refuel();
        boardPassengers();
        taxiing();
        takeOff();
        startingDelay = 30;
    }
}

void Plane::initialize() {
    string flightNumber_temp = randomFlightID();
    if (flightNumber == "") {
        if (!airport.isFlightNumberAvailable(flightNumber_temp)) {
            initialize();
        } else {
            flightNumber = flightNumber_temp;
        }
    }
}
