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
    while (status != PassengerStatus::OnBoard) {
        waitAtGate();
    }
}

void Passenger::runLeavingThePlane() {
    exitPlane();
    proceedToTerminal();
    collectLuggage();
    leaveAirport();
}


void Passenger::run() {
    // while (true) {
    status = PassengerStatus::ExitingPlane;
    happiness = 100;
    flightNumber = " ";
    runGettingOnAPlane();
    // runLeavingThePlane();
    // }
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
    } else boardPlane(flightNumber);
}

void Passenger::boardPlane(std::string &flightNumber) {
    status = PassengerStatus::Boarding;
    std::this_thread::sleep_for(std::chrono::seconds(randInt(2, 6)));
    if (terminal.goThroughGate(numberOf, flightNumber)) {
        status = PassengerStatus::OnBoard;
        //przechodzenie przez bramke, jesli brak miejsc to sie odbija
        // Implementacja logiki wchodzenia pasażera do samolotu
        std::cout << "[Passenger " << passengerID << "] ";
        std::cout << "is boarding the plane." << std::endl;
    } else {
        if (happiness > 0) {
            happiness -= 10;
        }
        std::cout << "[Passenger " << passengerID << "] ";
        std::cout << "did not go through the gate " << gateIndex << std::endl;
    }
}

//Leaving a plane

void Passenger::exitPlane() {
    // Implementacja logiki opuszczania samolotu przez pasażera
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is exiting the plane." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(randInt(15, 20)));
}

void Passenger::proceedToTerminal() {
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is proceeding to the terminal." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(randInt(15, 20)));
    // Implementacja logiki przejścia pasażera do terminalu
}

void Passenger::collectLuggage() {
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is collecting luggage." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(randInt(15, 20)));
    // Implementacja logiki odbierania bagażu przez pasażera
}

void Passenger::leaveAirport() {
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is leaving the airport." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(randInt(15, 20)));
    // Implementacja logiki opuszczania lotniska przez pasażera
}

