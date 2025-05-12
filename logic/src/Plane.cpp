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
#include "FlightControlTower.h"

std::condition_variable cv;

void Plane::land() {
    // Implement the logic for landing
    std::this_thread::sleep_for(std::chrono::seconds(randInt(2, 6)));
    if (airport.getFlightControlTower()->requestLanding(*this)) {;
        std::cout << "[Plane " << flightNumber <<"] ";
        std::cout << "is landing. " << randInt(0,5)<<std::endl;
        status = PlaneStatus::Landing;
        std::this_thread::sleep_for(std::chrono::seconds(randInt(3, 8))); //LANDING SET FOR 10s
    } else {
        std::cout << "[Plane " << flightNumber <<"] ";
        std::cout << "is waiting for landing." << std::endl;
        land();
    }

}
void Plane::disembarkPassengers() {
    std::cout << "[Plane " << flightNumber <<"] ";
    if (airport.getFlightControlTower()->requestDisembarking(*this)) {
        std::cout << "is disembarking passengers." << std::endl;
        status = PlaneStatus::Disembarking;
        std::this_thread::sleep_for(std::chrono::seconds(randInt(3, 8))); //DISAMBARKING SET FOR 10s
    } else {
        std::cout << "[Plane " << flightNumber <<"] ";
        std::cout << "is waiting for disembarkation." << std::endl;
        disembarkPassengers();
    }
    // Implement the logic for disembarking passengers
    status = PlaneStatus::Disembarking;
    std::this_thread::sleep_for( std::chrono::seconds(rand() % 3 + 10)); //DISEMBARKING SET FOR 10s
}
void Plane::turnaroundCheck() {
    std::cout << "[Plane " << flightNumber <<"] ";
    // Implement the logic for disembarking passengers
    std::cout << "Disembarking passengers." << std::endl;
    status = PlaneStatus::TurnaroundCheck;
    std::this_thread::sleep_for( std::chrono::seconds(rand() % 3 + 10)); //DISEMBARKING SET FOR 10s

}
void Plane::refuel() {
    std::cout << "[Plane " << flightNumber <<"] ";
    // Implement the logic for refueling
    std::cout << "Refueling plane." << std::endl;
    status = PlaneStatus::Refueling;
    std::this_thread::sleep_for(std::chrono::seconds(40)); //REFUELING SET FOR 40s
}



void Plane::boardPassengers() {
    std::cout << "[Plane " << flightNumber <<"] ";
    // Implement the logic for boarding passengers
    std::cout << "Boarding passengers." << std::endl;
    status = PlaneStatus::Boarding;
    std::this_thread::sleep_for(std::chrono::seconds(30)); //BOARDING SET FOR 30s
    status = PlaneStatus::WaitingForRunway;
}
void Plane::taxiing() {
    std::cout << "[Plane " << flightNumber <<"] ";
    // Implement the logic for requesting a runway
    std::cout << "Requesting runway." << std::endl;
    if (airport.getFlightControlTower()->requestRunwayAvailability(*this)) {
        std::cout << "Runway is available." << std::endl;
        status = PlaneStatus::TaxiingToRunway;
    } else {
        std::cout << "Runway is not available." << std::endl;
        //TODO stworzenie kolejki gdzie wieża będzie przechowywać samoloty i je powiadamiać ale na razie sleepfor
//        cv.wait(lock, [&] { return ready; }); // Czekaj, aż ready == true to trzeba przekminic

        taxiing();
    }
    std::this_thread::sleep_for(std::chrono::seconds(10)); //REQUESTING RUNWAY SET FOR 10s
}

void Plane::takeOff() {
    std::cout << "[Plane " << flightNumber <<"] ";
    // Implement the logic for taking off
    std::cout << "Plane is taking off." << std::endl;
    status = PlaneStatus::TakingOff;
    std::this_thread::sleep_for(std::chrono::seconds(12)); //TAKEOFF SET FOR 12s
}
void Plane::run() {
    // Implement the logic for the plane's operations
    srand(time(NULL));
    land();
    disembarkPassengers();
    turnaroundCheck();
    refuel();
    boardPassengers();
    takeOff();
}