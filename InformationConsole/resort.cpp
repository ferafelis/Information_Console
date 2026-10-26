#include "prototype.h"

#include <iostream>
#include <string>
#include <limits>

// Display resort information
void showResortInfo(Resort* resort)
{
    if (resort == nullptr) {
        std::cout << "Resort is not initialized.\n";
        return;
    }

    std::cout << "\n=== Resort Information ===\n";
    std::cout << "Name: " << resort->name << '\n';
    std::cout << "Type: " << resort->type << '\n';
    std::cout << "Location: " << resort->location << '\n';
}

// Edit resort information
void EditResortInfo(Resort* resort)
{
    if (resort == nullptr) {
        std::cout << "Resort is not initialized.\n";
        return;
    }

    std::string input;

    std::cout << "Enter new resort name (empty to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        resort->name = input;
    }

    std::cout << "Enter new resort type (empty to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        resort->type = input;
    }

    std::cout << "Enter new resort location (empty to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        resort->location = input;
    }

    std::cout << "Resort information updated.\n";
}

// Delete a resort from a country's linked list
void deleteResort(Country* country, Resort* resortToDelete)
{
    if (country == nullptr || resortToDelete == nullptr) {
        return;
    }

    Resort* current = country->firstResort;
    Resort* previous = nullptr;

    while (current != nullptr && current != resortToDelete) {
        previous = current;
        current = current->nextResort;
    }

    if (current == nullptr) {
        std::cout << "Resort was not found.\n";
        return;
    }

    if (previous == nullptr) {
        country->firstResort = current->nextResort;
    }
    else {
        previous->nextResort = current->nextResort;
    }

    // Detach the resort before deleting it.
    current->nextResort = nullptr;
    delete current;

    std::cout << "Resort deleted successfully.\n";
}

// List all hotels in a resort
void listHotels(Resort* resort)
{
    if (resort == nullptr) {
        std::cout << "Resort is not initialized.\n";
        return;
    }

    Hotel* current = resort->firstHotel;

    if (current == nullptr) {
        std::cout << "No hotels have been added to "
            << resort->name << ".\n";
        return;
    }

    std::cout << "\n=== Hotels in " << resort->name << " ===\n";

    int index = 1;

    while (current != nullptr) {
        std::cout << index++ << ". " << current->name
            << " | Rating: " << current->rating
            << " | Price: " << current->price
            << " | Pool: "
            << (current->hasPool ? "Yes" : "No")
            << '\n';

        current = current->nextHotel;
    }
}

