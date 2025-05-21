#include <iostream>
#include <random>

// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>

#include <curses.h>

#include "AirportView.h"
// #include "logic/src/Airport.h"

int main(int argc, char *argv[]) {
    // srand(time(NULL));
    // AirportView view;
    // view.display();
    initscr(); // Start curses mode
    cbreak(); // Line buffering disabled
    noecho(); // Don't echo while we do getch
    curs_set(0); // Hide the cursor

    int height = 10, width = 30;
    int starty1 = 2, startx1 = 5;
    int starty2 = 2, startx2 = 40;

    // Tworzenie dwóch okien
    WINDOW *win1 = newwin(height, width, starty1, startx1);
    WINDOW *win2 = newwin(height, width, starty2, startx2);

    // Ramki wokół okien
    box(win1, 0, 0);
    box(win2, 0, 0);

    // Wypisywanie tekstu do okien
    mvwprintw(win1, 1, 1, "To jest okno 1");
    mvwprintw(win2, 1, 1, "To jest okno 2");

    // Odświeżanie okien
    wrefresh(win1);
    wrefresh(win2);

    getch(); // Czekaj na klawisz

    // Zwolnienie zasobów
    delwin(win1);
    delwin(win2);
    endwin(); // Koniec curses
    //
    // Airport airport;
    // airport.initialize();
    // airport.run();
    // Utworzenie okna
    // sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Przykład SFML z obsługą zdarzeń");
    //
    // // Utworzenie prostokąta
    // sf::RectangleShape rectangle(sf::Vector2f(100, 50)); // Rozmiar prostokąta
    // rectangle.setFillColor(sf::Color::Blue); // Kolor wypełnienia
    // rectangle.setPosition(sf::Vector2f(350, 275)); // Pozycja na środku okna
    //
    // // Główna pętla aplikacji
    // while (window.isOpen()) {
    //     // Obsługa zdarzeń
    //     while (true) {
    //         while (const std::optional<sf::Event> event = window.pollEvent()) {
    //             if (event->is<sf::Event::Closed>()) {
    //                 window.close();
    //             } else if (event->is<sf::Event::KeyPressed>()) {
    //                 const auto *keyEvent = event->getIf<sf::Event::KeyPressed>();
    //                 if (keyEvent && keyEvent->code == sf::Keyboard::Key::Escape) {
    //                     window.close();
    //                 }
    //             }
    //         }
    //
    //
    //         // Czyszczenie okna
    //         window.clear(sf::Color::Black);
    //
    //         // Rysowanie prostokąta
    //         window.draw(rectangle);
    //
    //         // Wyświetlenie zawartości okna
    //         window.display();
    //     }
    // }


    return 0;
}
