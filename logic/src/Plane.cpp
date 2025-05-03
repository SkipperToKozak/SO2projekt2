//
// Created by Skipper on 01.05.2025.
//

#include "Plane.h"

#include <chrono>
#include <iostream>
#include <thread>
#include <random>





void land() {
    // Implement the logic for landing
    std::cout << "Plane is landing." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 4 + 2));
}
void disembarkPassengers() {
    // Implement the logic for disembarking passengers
    std::cout << "Disembarking passengers." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 4 + 2));
}
void boardPassengers() {
    // Implement the logic for boarding passengers
    std::cout << "Boarding passengers." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 4 + 2));
}
void refuel() {
    // Implement the logic for refueling
    std::cout << "Refueling plane." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 4 + 2));
}
void takeOff() {
    // Implement the logic for taking off
    std::cout << "Plane is taking off." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 4 + 2));
}
void run() {
    // Implement the logic for the plane's operations
    land();
    disembarkPassengers();
    refuel();
    boardPassengers();
    takeOff();
}