//
// Created by Skipper on 09.06.2025.
//

#ifndef TECHNICALSUPPORT_H
#define TECHNICALSUPPORT_H
#include <iostream>

enum class MaintenanceType {
    TurnaroundCheck, // Przegląd techniczny przed odlotem
    Refueling, // Tankowanie samolotu
    Other // Inne przeglądy techniczne
};

inline std::string toString(MaintenanceType type) {
    switch (type) {
        case MaintenanceType::TurnaroundCheck: return "Turnaround Check";
        case MaintenanceType::Refueling: return "Refueling";
        case MaintenanceType::Other: return "Idle";
        default: return "Unknown";
    }
}


class TechnicalSupport {
    int maintenanceID = 0; // Unikalny identyfikator przeglądu technicznego
    bool inUse = false;
    int gateIndex = -1;
    MaintenanceType maintenanceType = MaintenanceType::Other;
    std::string planeId; // Identyfikator samolotu, który jest poddawany przeglądowi

public:
    explicit TechnicalSupport(int id)
        : maintenanceID(id), inUse(false), gateIndex(-1), maintenanceType(MaintenanceType::Other) {
    }

    // Metoda do przeprowadzania przeglądów technicznych
    void performTurnaroundCheck(std::string &planeID, int gateID) {
        // Logika przeglądu technicznego
        maintenanceType = MaintenanceType::TurnaroundCheck;
        planeId = planeID;
        gateIndex = gateID;
        inUse = true; // Ustawienie przeglądu jako w użyciu
        std::cout << "Performing technical maintenance..." << std::endl;
        // Można dodać więcej szczegółów dotyczących przeglądu
    }

    void refuelPlane() {
        // Logika tankowania samolotu
        maintenanceType = MaintenanceType::Refueling;
        std::cout << "Refueling plane: " << planeId << std::endl;
        // Można dodać więcej szczegółów dotyczących tankowania
    }

    void setFree() {
        // Logika zwalniania przeglądu technicznego
        std::cout << "Technical maintenance completed for plane: " << planeId << std::endl;
        maintenanceType = MaintenanceType::Other; // Resetowanie typu przeglądu
        planeId.clear();
        inUse = false;
        gateIndex = -1; // Resetowanie indeksu bramki
    }

    void setInUse() {
        // Logika ustawiania przeglądu technicznego jako w użyciu
        inUse = true;
        std::cout << "Technical maintenance is now in use for plane: " << planeId << std::endl;
    }

    [[nodiscard]] bool isInUse() const {
        return inUse;
    }

    [[nodiscard]] int getGateIndex() const {
        return gateIndex;
    }

    [[nodiscard]] std::string getPlaneId() const {
        return planeId;
    }

    [[nodiscard]] MaintenanceType getMaintenanceType() const {
        return maintenanceType;
    }

    [[nodiscard]] int getMaintenanceID() const {
        return maintenanceID;
    }
};


#endif //TECHNICALSUPPORT_H
