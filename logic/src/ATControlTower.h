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


class ATControlTower {
    Airport &airport;
    int numRunways;
    std::vector<Runway> runways;

public:
    ATControlTower(Airport &airport, int numRunways)
        : airport(airport), numRunways(numRunways) {
        // for (int i = 0; i < numRunways; i++) {
        //     runways.emplace_back(i);
        //     std::cout << "[AT CONTROL TOWER] Runway " << i << " initialized." << std::endl;
        // }
    }


    void initialize();

    bool requestLanding(Plane &plane);

    bool requestTakeOff(Plane &plane);

    void releaseRunway(Plane &plane);

    bool requestTurnaroundCheck(Plane &plane);

    bool requestRefueling(Plane &plane);

    bool requestBoarding(Plane &plane);

    bool requestDisembarking(Plane &plane, int &gateIndex);

    bool requestRunwayAvailability(Plane &plane, int &runwayIndex);

    bool requestTaxiing(Plane &plane);

    const std::vector<Runway> &getRunways() {
        return runways;
    }
};


#endif //FLIGHTCONTROLTOWER_H
