#include <iostream>
#include <random>

// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>

#include <curses.h>
#include <string.h>

#include "AirportView.h"
#include "AirportController.h"
#include <thread>

// #include "logic/src/Airport.h"
typedef struct {
    int x, y, width, height;
    char title[32];
    char content[256];
} Box;


int main(int argc, char *argv[]) {
    srand(time(NULL));
    Config config;


    AirportController controller = AirportController(std::move(config));
    AirportView view(controller);

    // Uruchom Airport::run w osobnym wątku
    std::thread airportThread(&Airport::run, &controller.airport);

    // Wywołaj display w głównym wątku
    view.display();
    controller.getRunwaysInfo();
    // while (true) {
    //     this_thread::sleep_for(6500ms);
    //     cout << controller.getPassengersInfo().at(1).statusText << endl;
    //     this_thread::sleep_for(500ms);
    // }
    // Po zakończeniu display dołącz wątek
    if (airportThread.joinable())
        airportThread.join();

    return 0;
}
