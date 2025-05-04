#include <iostream>
#include <random>

#include "logic/src/Airport.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Airport airport;
    airport.initialize();
    return 0;
}
