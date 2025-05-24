//
// Created by Skipper on 01.05.2025.
//
#include "Utilities/randomise.h"
#include "Passenger.h"
#include <iostream>
#include <thread>

#include "utilities/FileUtils.h"

void Passenger::runGettingOnAPlane() {
    arriveAtAirport();
    checkIn();
    passSecurityCheck();
    while (status != PassengerStatus::OnBoard) {
        waitAtGate();
    }
    std::cout << "[Passenger " << passengerID << "]  skonczylem";
    FileUtils::saveToFile(
        std::to_string(passengerID) + ";" + std::to_string(numberOf) + ";" + std::to_string(happiness));
    isFinished = true;
}

void Passenger::runLeavingThePlane() {
    exitPlane();
    proceedToTerminal();
    collectLuggage();
    leaveAirport();
    isFinished = true;
}


void Passenger::run() {
    // while (true) {
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
    if (!terminal.isGateOpenedForPassengers(gateIndex, passengerID, numberOf)) {
        if (happiness > 0) {
            happiness -= 10;
        }
        waitAtGate();
    } else boardPlane();
}

void Passenger::boardPlane() {
    status = PassengerStatus::Boarding;
    std::this_thread::sleep_for(std::chrono::seconds(randInt(2, 6)));
    if (terminal.goThroughGate(gateIndex, numberOf, flightNumber)) {
        status = PassengerStatus::OnBoard;
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Czas przejścia przez bramkę
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
    // Implementacja logiki ouszczania samolotu przez pasażera
    status = PassengerStatus::ExitingPlane;
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is exiting the plane." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(randInt(2, 6)));
}

void Passenger::proceedToTerminal() {
    status = PassengerStatus::Disembarked;
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is proceeding to the terminal." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(randInt(2, 6)));
    // Implementacja logiki przejścia pasażera do terminalu
}

void Passenger::collectLuggage() {
    status = PassengerStatus::CollectingLuggage;
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is collecting luggage." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(randInt(2, 6)));
    // Implementacja logiki odbierania bagażu przez pasażera
}

void Passenger::leaveAirport() {
    status = PassengerStatus::Leaving;
    std::cout << "[Passenger " << passengerID << "] ";
    std::cout << "is leaving the airport." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(6));
    // Implementacja logiki opuszczania lotniska przez pasażera
}

