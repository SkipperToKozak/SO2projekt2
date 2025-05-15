//
// Created by Skipper on 01.05.2025.
//

#ifndef FLIGHTCONTROLTOWER_H
#define FLIGHTCONTROLTOWER_H
#include <mutex>
#include <vector>

#include "Plane.h"
#include "Terminal.h"
#include "resources/Runway.h"





class FlightControlTower {
    Terminal terminal;
    int numRunways;
    std::vector<Runway> runways;
public:
    FlightControlTower(int numRunways, int numGates)
    : terminal(numGates), numRunways(numRunways) {
        for (int i = 0; i < numRunways; ++i) {
            runways.emplace_back(i);
        }
    }
    void initialize();

    bool requestLanding(Plane& plane);
    bool requestTakeOff(Plane& plane);

    void releaseRunway(Plane &plane);

    bool requestTurnaroundCheck(Plane& plane);
    bool requestRefueling(Plane& plane);
    bool requestBoarding(Plane& plane);
    bool requestDisembarking(Plane& plane, int& gateIndex);
    bool requestRunwayAvailability(Plane& plane, int& runwayIndex);
    bool requestTaxiing(Plane &plane);


    Terminal &getTerminal() {
        return terminal;
    }
};



#endif //FLIGHTCONTROLTOWER_H
