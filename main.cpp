#include <iostream>
#include <random>

#include "logic/src/Airport.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Airport airport;
    airport.initialize();
    airport.run();
    return 0;
}
