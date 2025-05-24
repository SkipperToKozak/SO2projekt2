//
// Created by Skipper on 24.05.2025.
//

#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>

class Config {
private:
    std::string filePath;
    std::map<std::string, std::string> configData;

    void createDefaultConfig() {
        std::ofstream configFile(filePath);
        if (configFile.is_open()) {
            configFile << "setting1=default_value1\n";
            configFile << "setting2=default_value2\n";
            configFile.close();
        } else {
            throw std::runtime_error("Nie można utworzyć pliku konfiguracyjnego.");
        }
    }

    void loadConfig() {
        std::ifstream configFile(filePath);
        if (configFile.is_open()) {
            std::string line;
            while (std::getline(configFile, line)) {
                size_t delimiterPos = line.find('=');
                if (delimiterPos != std::string::npos) {
                    std::string key = line.substr(0, delimiterPos);
                    std::string value = line.substr(delimiterPos + 1);
                    configData[key] = value;
                }
            }
            configFile.close();
        } else {
            throw std::runtime_error("Nie można otworzyć pliku konfiguracyjnego.");
        }
    }

public:
    explicit Config(const std::string &path) : filePath(path) {
        std::ifstream configFile(filePath);
        if (!configFile.good()) {
            createDefaultConfig();
        }
        loadConfig();
    }

    std::string getValue(const std::string &key) const {
        auto it = configData.find(key);
        if (it != configData.end()) {
            return it->second;
        }
        throw std::runtime_error("Klucz nie istnieje w konfiguracji: " + key);
    }

    void setValue(const std::string &key, const std::string &value) {
        configData[key] = value;
        saveConfig();
    }

    void saveConfig() {
        std::ofstream configFile(filePath);
        if (configFile.is_open()) {
            for (const auto &entry: configData) {
                configFile << entry.first << "=" << entry.second << "\n";
            }
            configFile.close();
        } else {
            throw std::runtime_error("Nie można zapisać pliku konfiguracyjnego.");
        }
    }
};
#endif //CONFIG_H
