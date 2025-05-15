//
// Created by Skipper on 01.05.2025.
//
#include "Utilities/randomise.h"
#include "Passenger.h"
#include <iostream>
#include <thread>

void Passenger::runGettingOnAPlane() {
    arriveAtAirport();
    checkIn();
    passSecurityCheck();
    waitAtGate();
    boardPlane();
}

void Passenger::runLeavingThePlane() {
    exitPlane();
    proceedToTerminal();
    collectLuggage();
    leaveAirport();
}


//Entering a plane
void Passenger::arriveAtAirport() {
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is arriving at the airport." << std::endl;
    status = PassengerStatus::ArrivingAtAirport;
    // Implementacja logiki przybycia pasażera na lotnisko
    std::this_thread::sleep_for(std::chrono::seconds(randInt(2, 6)));
}

void Passenger::checkIn() {
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is checking in." << std::endl;
    status = PassengerStatus::CheckingIn;
    // Implementacja logiki odprawy pasażera
    std::this_thread::sleep_for(std::chrono::seconds(randInt(2, 6)));
}

void Passenger::passSecurityCheck() {
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is passing security check." << std::endl;
    status = PassengerStatus::SecurityCheck;
    // Implementacja logiki przejścia kontroli bezpieczeństwa
    std::this_thread::sleep_for(std::chrono::seconds(randInt(2, 6)));
}

void Passenger::waitAtGate() {
    status = PassengerStatus::WaitingAtGate;
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is waiting at the gate." << std::endl;
    // Implementacja logiki oczekiwania pasażera przy bramce
    std::this_thread::sleep_for(std::chrono::seconds(randInt(15, 20)));
    if (!terminal.isGateOpenedForPassengers(gateIndex, passengerID)) {
        if (happiness > 0) {
            happiness -= 10;
        }
        waitAtGate();
    }
}

void Passenger::boardPlane() {
    status = PassengerStatus::Boarding;
    if (terminal.goThroughGate(numberOf)) {
        //przechodzenie przez bramke, jesli brak miejsc to sie odbija
        // Implementacja logiki wchodzenia pasażera do samolotu
        std::cout << "[Passenger " << passengerID << "] ";
        std::cout << "is boarding the plane." << std::endl;
    } else {
        std::cout << "[Passenger " << passengerID << "] ";
        std::cout << "did not go through the gate " << gateIndex << std::endl;
    }
}

//Leaving a plane

void Passenger::exitPlane() {
    // Implementacja logiki opuszczania samolotu przez pasażera
}

void Passenger::proceedToTerminal() {
    // Implementacja logiki przejścia pasażera do terminalu
}

void Passenger::collectLuggage() {
    // Implementacja logiki odbierania bagażu przez pasażera
}

void Passenger::leaveAirport() {
    // Implementacja logiki opuszczania lotniska przez pasażera
}

