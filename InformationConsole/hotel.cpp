#include "prototype.h"

#include <iostream>
#include <string>

// Display hotel information
void showHotelInfo(Hotel* hotel)
{
    if (hotel == nullptr) {
        std::cout << "Hotel is not initialized.\n";
        return;
    }

    std::cout << "\n=== Hotel Information ===\n";
    std::cout << "Name: " << hotel->name << '\n';
    std::cout << "Rating: " << hotel->rating << '\n';
    std::cout << "Price: " << hotel->price << '\n';
    std::cout << "Has pool: "
        << (hotel->hasPool ? "Yes" : "No") << '\n';
}

// Edit hotel information
void EditHotelInfo(Hotel* hotel)
{
    if (hotel == nullptr) {
        std::cout << "Hotel is not initialized.\n";
        return;
    }

    std::string input;

    std::cout << "Enter new hotel name (empty to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        hotel->name = input;
    }

    std::cout << "Enter new rating (empty to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            std::size_t position = 0;
            unsigned long value = std::stoul(input, &position);

            if (position != input.size() || value > 5) {
                throw std::invalid_argument("Invalid rating");
            }

            hotel->rating = static_cast<uint>(value);
        }
        catch (const std::exception&) {
            std::cout << "Invalid rating. Previous value retained.\n";
        }
    }

    std::cout << "Enter new price (empty to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            std::size_t position = 0;
            unsigned long value = std::stoul(input, &position);

            if (position != input.size() ||
                value > std::numeric_limits<uint>::max()) {
                throw std::invalid_argument("Invalid price");
            }

            hotel->price = static_cast<uint>(value);
        }
        catch (const std::exception&) {
            std::cout << "Invalid price. Previous value retained.\n";
        }
    }

    std::cout << "Does the hotel have a pool? (yes/no, empty to keep current): ";
    std::getline(std::cin, input);

    if (input == "yes" || input == "Yes" || input == "YES") {
        hotel->hasPool = true;
    }
    else if (input == "no" || input == "No" || input == "NO") {
        hotel->hasPool = false;
    }

    std::cout << "Hotel information updated.\n";
}

// Add a hotel to a resort's linked list
void addHotel(Resort* resort, Hotel* hotel)
{
    if (resort == nullptr || hotel == nullptr) {
        return;
    }

    hotel->nextHotel = nullptr;

    if (resort->firstHotel == nullptr) {
        resort->firstHotel = hotel;
        return;
    }

    Hotel* current = resort->firstHotel;

    while (current->nextHotel != nullptr) {
        current = current->nextHotel;
    }

    current->nextHotel = hotel;
}

// Delete a hotel from a resort's linked list
void deleteHotel(Resort* resort, Hotel* hotelToDelete)
{
    if (resort == nullptr || hotelToDelete == nullptr) {
        return;
    }

    Hotel* current = resort->firstHotel;
    Hotel* previous = nullptr;

    while (current != nullptr && current != hotelToDelete) {
        previous = current;
        current = current->nextHotel;
    }

    if (current == nullptr) {
        std::cout << "Hotel was not found.\n";
        return;
    }

    if (previous == nullptr) {
        resort->firstHotel = current->nextHotel;
    }
    else {
        previous->nextHotel = current->nextHotel;
    }

    current->nextHotel = nullptr;
    delete current;

    std::cout << "Hotel deleted successfully.\n";
}