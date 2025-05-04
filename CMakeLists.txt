cmake_minimum_required(VERSION 3.31)
project(SO2projekt2)

set(CMAKE_CXX_STANDARD 20)

add_executable(SO2projekt2 main.cpp
        logic/src/Airport.cpp
        logic/src/Airport.h
        logic/src/Plane.cpp
        logic/src/Plane.h
        logic/src/Vehicle.cpp
        logic/src/Vehicle.h
        logic/src/Passenger.cpp
        logic/src/Passenger.h
        logic/src/FlightControlTower.cpp
        logic/src/FlightControlTower.h
        logic/src/resources/Hangar.cpp
        logic/src/resources/Hangar.h
        logic/src/resources/Gate.cpp
        logic/src/resources/Gate.h
        logic/src/resources/Terminal.cpp
        logic/src/resources/Terminal.h
        logic/src/resources/Runway.cpp
        logic/src/resources/Runway.h)
