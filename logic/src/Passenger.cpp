//
// Created by Skipper on 01.05.2025.
//

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
    status = PassengerStatus::ArrivingAtAirport;
    // Implementacja logiki przybycia pasażera na lotnisko
    std::this_thread::sleep_for(std::chrono::seconds(5));

}
void Passenger::checkIn() {
    status = PassengerStatus::CheckingIn;
    // Implementacja logiki odprawy pasażera
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
void Passenger::passSecurityCheck() {
    status = PassengerStatus::SecurityCheck;
    // Implementacja logiki przejścia kontroli bezpieczeństwa
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
void Passenger::waitAtGate() {
    status = PassengerStatus::WaitingAtGate;
    // Implementacja logiki oczekiwania pasażera przy bramce
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (!terminal.isGateOpenedForPassengers(gateIndex, passengerID)) {
        waitAtGate();
    }

}
void Passenger::boardPlane() {
    status = PassengerStatus::Boarding;
    // Implementacja logiki wchodzenia pasażera do samolotu
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

