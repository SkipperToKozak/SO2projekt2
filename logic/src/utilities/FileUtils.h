//
// Created by Skipper on 24.05.2025.
//

#ifndef FILEUTILS_H
#define FILEUTILS_H


#include <iostream>
#include <fstream>
#include <mutex>
#include <string>

class FileUtils {
public:
    static void createFile(const std::string &filename, const std::string &content) {
        std::lock_guard<std::mutex> lock(std::mutex);
        std::ifstream test(filename);
        // Sprawdzenie, czy plik już istnieje
        if (test.is_open()) {
            test.close();
            return;
        }
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Nie można utworzyć pliku: " + filename);
        }
        file << content;
        file.close();
    }

    static void saveToFile(const std::string &data, std::string filename) {
        std::lock_guard<std::mutex> lock(std::mutex);
        std::ofstream file(filename, std::ios::app); // Otwieranie w trybie dopisywania
        if (file.is_open()) {
            file << data << std::endl;
            file.close();
        } else {
            throw std::runtime_error("Nie można otworzyć pliku do zapisu: " + filename);
        }
    }
};


#endif //FILEUTILS_H
