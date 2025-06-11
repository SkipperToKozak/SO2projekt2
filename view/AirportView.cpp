//
// Created by Skipper on 20.05.2025.
//

#include "AirportView.h"

#include <curses.h>
#include <cstring>

#include "src/utilities/Timer.h"
// #include <windows.h>

#define WIDTH 60
#define HEIGHT 15

// #include <curses.h>
typedef struct {
    int x, y, width, height;
    char title[32];
    vector<PlaneViewModel> content;
} PlaneBox;

typedef struct {
    int x, y, width, height;
    char title[32];
    vector<PassengerViewModel> content;
} PassengerBox;

typedef struct {
    int x, y, width, height;
    char title[32];
    vector<GateViewModel> content;
} GateBox;

typedef struct {
    int x, y, width, height;
    char title[32];
    vector<RunwayViewModel> content;
} RunwayBox;

typedef struct {
    int x, y, width, height;
    char title[32];
    vector<TechSupportViewModel> content;
} TechSupportBox;


void drawPlaneBox(PlaneBox b) {
    WINDOW *win = newwin(b.height, b.width, b.y, b.x);


    box(win, 0, 0);

    mvwprintw(win, 0, 2, "%s", b.title);
    for (int i = 0; i < b.content.size(); i++) {
        if (i < b.height - 2) {
            mvwprintw(win, i + 1, 1, "%s Passengers %2d/%2d  Fuel %d/%d %s %d", (b.content[i].flightNumber).c_str(),
                      b.content[i].passengersOnBoard, b.content[i].passengerLimit,
                      b.content[i].currentFuel, b.content[i].fuelCapacity, (b.content[i].statusText).c_str(),
                      b.content[i].startingDelay);
        }
    }

    wrefresh(win);
    delwin(win); // ważne, by nie zostawiać "śmieci" w pamięci
}

void drawPassengerBox(PassengerBox b) {
    WINDOW *win = newwin(b.height, b.width, b.y, b.x);

    box(win, 0, 0);
    mvwprintw(win, 0, 2, "%s", b.title);
    for (int i = 0; i < b.content.size(); i++) {
        if (i < b.height - 2) {
            b.content[i].statusText == "OnBoard" ? wattron(win, A_BLINK) : wattroff(win, A_BLINK);
            b.content[i].statusText == "Leaving" ? wattron(win, A_STANDOUT) : wattroff(win, A_STANDOUT);
            mvwprintw(win, i + 1, 1, "ID: %2d H: %3d Num: %2d %s %s", b.content[i].passengerID, b.content[i].happiness,
                      b.content[i].numberOf, (b.content[i].flightNumber).c_str(),
                      (b.content[i].statusText).c_str());
        }
    }

    wrefresh(win);
    delwin(win); // ważne, by nie zostawiać "śmieci" w pamięci
}

void drawGateBox(GateBox b) {
    WINDOW *win = newwin(b.height, b.width, b.y, b.x);

    box(win, 0, 0);
    mvwprintw(win, 0, 2, "%s", b.title);
    for (int i = 0; i < b.content.size(); i++) {
        if (i < b.height - 2) {
            if (b.content[i].statusText == "None") {
                wattron(win, COLOR_PAIR(2));
            } else if (b.content[i].statusText == "Planes") {
                wattron(win, COLOR_PAIR(1));
            } else {
                wattron(win, COLOR_PAIR(3));
            }
            mvwprintw(win, i + 1, 1, "ID: %2d %s Lim: %3d %s", b.content[i].gateID, (b.content[i].statusText).c_str(),
                      b.content[i].limit, b.content[i].currentPlaneId.c_str());
        }
    }

    wrefresh(win);
    delwin(win); // ważne, by nie zostawiać "śmieci" w pamięci
}

void drawRunwayBox(RunwayBox b) {
    WINDOW *win = newwin(b.height, b.width, b.y, b.x);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, "%s %d", b.title, b.content.size());
    for (int i = 0; i < b.content.size(); i++) {
        if (i < b.height - 2) {
            if (b.content[i].statusText == "Available") {
                wattron(win, COLOR_PAIR(1));
            } else {
                wattron(win, COLOR_PAIR(2));
            }
            mvwprintw(win, i + 1, 1, "ID: %2d %s %s", b.content[i].runwayID, b.content[i].statusText.c_str(),
                      b.content[i].currentPlaneId.c_str());
        }
    }
    wrefresh(win);
    delwin(win); // ważne, by nie zostawiać "śmieci" w pamięci
}

void drawTechSupportBox(TechSupportBox b) {
    WINDOW *win = newwin(b.height, b.width, b.y, b.x);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, "%s", b.title);
    for (int i = 0; i < b.content.size(); i++) {
        if (i < b.height - 2) {
            if (b.content[i].maintenanceType == "Turnaround Check") {
                wattron(win, COLOR_PAIR(2));
            } else if (b.content[i].maintenanceType == "Refueling") {
                wattron(win, COLOR_PAIR(2));
            } else {
                wattron(win, COLOR_PAIR(1));
            }
            mvwprintw(win, i + 1, 1, "ID: %2d %s %s %s", b.content[i].maintenanceID,
                      b.content[i].maintenanceType.c_str(),
                      b.content[i].planeId.c_str(),
                      b.content[i].gateIndex > -1 ? std::to_string(b.content[i].gateIndex).c_str() : "");
        }
    }
    wrefresh(win);
    delwin(win); // ważne, by nie zostawiać "śmieci" w pamięci
}


void AirportView::display() {
    initscr();
    noecho();
    curs_set(FALSE);
    auto time = startCounter();


    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    int rows, cols, pasHeight = 1;
    // HWND console = GetConsoleWindow();
    // MoveWindow(console, 100, 100, 800, 600, TRUE);
    resize_term(2000, 2000);

    /* Get the largest physical screen dimensions */
    getmaxyx(stdscr, rows, cols);

    /* Resize so it fits */
    resize_term(rows - 2, cols - 2);

    /* Get the screen dimensions that fit */
    getmaxyx(stdscr, rows, cols);

    while (true) {
        if (pasHeight > airportController.getPassengersInfo().size()) {
            clear();
        }
        pasHeight = int(airportController.getPassengersInfo().size());

        mvprintw(
            0, 0, ("Resolution: " + to_string(rows) + "x" + to_string(cols) + " Time: " + to_string(getCounter(time))
                   + " Airport fuel: " + to_string(airportController.getAirportFuel()) + (
                       airportController.getRefuellingTruckInfo()
                           ? " REFUELLING TRUCK IN USE"
                           : " REFUELLING TRUCK - IDLE")).
            c_str());


        /* Resize the terminal to something larger than the physical screen */


        int box_width = (cols - 6) / 2; // 2 boxy + margines
        int box_height = rows - 6;
        // Rysowanie boxów

        PassengerBox passengers = {
            2, 1, WIDTH,
            airportController.getPassengersInfo().empty() ? 1 : int(airportController.getPassengersInfo().size()),
            "Passengers",
            airportController.getPassengersInfo()
        };
        //TODO STAŁE WARTOŚCI SZER I WYS
        PlaneBox planes = {WIDTH + 4, 1, WIDTH, HEIGHT, "Planes", airportController.getPlanesInfo()};

        GateBox gates = {2 * WIDTH + 6, 1, WIDTH - 10, HEIGHT, "Gates", airportController.getGatesInfo()};

        RunwayBox runway = {
            WIDTH + 4, HEIGHT + 4, WIDTH, HEIGHT, "Runways", airportController.getRunwaysInfo()
        };
        TechSupportBox tec = {
            2 * WIDTH + 6, HEIGHT + 4, WIDTH - 10, HEIGHT, "TechSupport", airportController.getTechSupportInfo()
        };

        drawPassengerBox(passengers);
        drawPlaneBox(planes);
        drawGateBox(gates);
        drawRunwayBox(runway);
        drawTechSupportBox(tec);


        // Górny rząd: statusy samolotów
        // for (int i = 0; i < 6; i++) {
        //     char title[16], content[32];
        //     snprintf(title, sizeof(title), "Sam #%d", i + 1);
        //     snprintf(content, sizeof(content), "In Flight");
        //     // Box b = {2 + i * 14, HEIGHT + 5, 12, 3, "", ""};
        //     // draw_box(b);
        // }
        //
        // // Dolny rząd: statusy pasażerów
        // for (int i = 0; i < 6; i++) {
        //     char title[16], content[32];
        //     snprintf(title, sizeof(title), "Pas %d", i + 1);
        //     snprintf(content, sizeof(content), "Checking In");
        //     Box b = {2 + i * 14, 18, 12, 3, "", ""};
        //     draw_box(b);
        // }
        this_thread::sleep_for(500ms);
        refresh();
        // initscr(); // Inicjalizacja curses
        // noecho();
        // curs_set(0);
        // start_color();
        //
        // init_pair(1, COLOR_GREEN, COLOR_BLACK); // Jedzący
        // init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Głodny
        // init_pair(3, COLOR_RED, COLOR_BLACK); // Myślący
        // init_pair(4, COLOR_WHITE, COLOR_BLACK); // Pałeczki
        //
        // int center_x = COLS / 2;
        // int center_y = LINES / 2;
        // int radius = min(COLS, LINES) / 4;
    }
}
