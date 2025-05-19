//
// Created by Skipper on 19.05.2025.
//

#ifndef SO2PROJEKT2_VEHICLE_H
#define SO2PROJEKT2_VEHICLE_H


#include <string>

class Vehicle {
public:
    virtual ~Vehicle() = default;

    // Metoda czysto wirtualna (abstrakcyjna)
    virtual void performTask(const std::string &planeId) = 0;

    // Opcjonalnie inne wspólne metody lub pola
    virtual std::string getType() const = 0;

protected:
    int vehicleID = 0;
    int currentGate = -1;
    int nextGate = -1;
};


#endif //SO2PROJEKT2_VEHICLE_H
