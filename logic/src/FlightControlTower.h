//
// Created by Skipper on 01.05.2025.
//

#ifndef FLIGHTCONTROLTOWER_H
#define FLIGHTCONTROLTOWER_H
#include <mutex>
#include <vector>

#include "Plane.h"
#include "resources/Runway.h"

#define NUM_RUNWAYS 3



class FlightControlTower {

    std::vector<Runway> runways;
public:
    FlightControlTower() = default;
    void initialize();

    bool requestLanding(Plane& plane);
    void requestTakeOff(Plane& plane);

    void requestHangarAvailability(Plane &plane);

    void requestTerminalAvailability(Plane &plane);

    void requestRefueling(Plane& plane);
    void requestBoarding(Plane& plane);
    void requestDisembarking(Plane& plane);
    void requestRunwayAvailability(Plane& plane);

};



#endif //FLIGHTCONTROLTOWER_H
