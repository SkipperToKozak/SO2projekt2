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
    static void saveToFile(const std::string &data) {
        std::lock_guard<std::mutex> lock(std::mutex);
        std::ofstream file("stats.csv", std::ios::app); // Otwieranie w trybie dopisywania
        if (file.is_open()) {
            file << data << std::endl;
            file.close();
        } else {
            throw std::runtime_error("Nie można otworzyć pliku do zapisu: = stats.csv");
        }
    }
};


#endif //FILEUTILS_H
