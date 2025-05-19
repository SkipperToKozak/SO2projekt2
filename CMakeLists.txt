cmake_minimum_required(VERSION 3.30.5)
project(SO2projekt2)

set(CMAKE_CXX_STANDARD 20)

add_executable(SO2projekt2 main.cpp
        logic/src/Airport.cpp
        logic/src/Airport.h
        logic/src/Plane.cpp
        logic/src/Plane.h
        logic/src/Passenger.cpp
        logic/src/Passenger.h
        logic/src/ATControlTower.cpp
        logic/src/ATControlTower.h
        logic/src/resources/Hangar.cpp
        logic/src/resources/Hangar.h
        logic/src/resources/Gate.cpp
        logic/src/resources/Gate.h
        logic/src/Terminal.cpp
        logic/src/Terminal.h
        logic/src/resources/Runway.cpp
        logic/src/resources/Runway.h
        logic/src/utilities/randomise.h
        logic/src/GroundServices.cpp
        logic/src/GroundServices.h
        logic/src/resources/Vehicle.cpp
        logic/src/resources/Vehicle.h
        logic/src/resources/RefuellingTruck.cpp
        logic/src/resources/RefuellingTruck.h
        logic/src/resources/TechnicalSupport.cpp
        logic/src/resources/TechnicalSupport.h)
