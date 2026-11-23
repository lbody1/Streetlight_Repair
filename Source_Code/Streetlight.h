#ifndef STREETLIGHT_H
#define STREETLIGHT_H

#include <string>
#include <iostream>

// Represents a single streetlight pole in the city
struct Streetlight {
    int poleID;             // Unique ID (Key for BST and Search)
    std::string streetName; // Location / Street
    std::string lampType;   // e.g. LED, Sodium, Solar
    std::string status;     // "Operational" or "Faulty"
    int brightness;         // Brightness percentage (0 - 100%)

    Streetlight() : poleID(0), streetName(""), lampType("LED"), status("Operational"), brightness(100) {}

    Streetlight(int id, std::string street, std::string type, std::string stat, int bright)
        : poleID(id), streetName(street), lampType(type), status(stat), brightness(bright) {}

    void display() const {
        std::cout << " [Pole ID: " << poleID 
                  << " | Location: " << streetName 
                  << " | Type: " << lampType 
                  << " | Status: " << status 
                  << " | Brightness: " << brightness << "%]\n";
    }
};

#endif // STREETLIGHT_H
