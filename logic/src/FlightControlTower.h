//
// Created by Skipper on 01.05.2025.
//

#ifndef FLIGHTCONTROLTOWER_H
#define FLIGHTCONTROLTOWER_H
#include "Plane.h"


class FlightControlTower {
public:
    void requestLanding(Plane& plane);
    void requestTakeOff(Plane& plane);

    void requestHangarAvailability(Plane &plane);

    void requestTerminalAvailability(Plane &plane);

    void requestRefueling(Plane& plane);
    void requestBoarding(Plane& plane);
    void requestDisembarking(Plane& plane);
    void requestRunwayAvailability(Plane& plane);

};



#endif //FLIGHTCONTROLTOWER_H
