#include <iostream>
#include <random>

// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>

#include <curses.h>
#include <string.h>

#include "AirportView.h"

// #include "logic/src/Airport.h"
typedef struct {
    int x, y, width, height;
    char title[32];
    char content[256];
} Box;


int main(int argc, char *argv[]) {
    srand(time(NULL));
#include "presenter/AirportController.h"
#include "view/AirportView.h"
#include <thread>

    AirportController controller;
    AirportView view(controller);

    // Uruchom Airport::run w osobnym wątku
    std::thread airportThread(&Airport::run, &controller.airport);

    // Wywołaj display w głównym wątku
    view.display();

    // Po zakończeniu display dołącz wątek
    if (airportThread.joinable())
        airportThread.join();

    return 0;
}
