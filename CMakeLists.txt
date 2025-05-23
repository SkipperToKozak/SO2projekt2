cmake_minimum_required(VERSION 3.10) #3.30.5
project(SO2projekt2)

# Ustawienie standardu C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Ścieżka do SFML
#set(SFML_DIR "C:/SFML-3.0.0/lib/cmake/SFML")

# Znalezienie pakietu SFML
#find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Dodanie katalogów z nagłówkami
include_directories(
        "C:/biblioteki-cpp/PDCurses-3.8"
        ${CMAKE_SOURCE_DIR}/logic
        ${CMAKE_SOURCE_DIR}/view
        ${CMAKE_SOURCE_DIR}/presenter
        #        "C:/SFML-3.0.0/include/*"


)
link_directories("C:/biblioteki-cpp/PDCurses-3.8/wincon")


# Dodanie plików źródłowych
add_executable(SO2projekt2
        main.cpp
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
        logic/src/resources/TechnicalSupport.h
        presenter/AirportController.cpp
        presenter/AirportController.h
        view/AirportView.cpp
        view/AirportView.h
)
target_link_libraries(SO2projekt2 pdcurses)
# Linkowanie bibliotek SFML

#target_link_libraries(SO2projekt2
#        SFML::Graphics
#        SFML::Window
#        SFML::System
#)