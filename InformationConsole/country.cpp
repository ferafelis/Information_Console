#include "prototype.h"

#include <iostream>
#include <string>
#include <limits>

// Display country information
void showCountryInfo(Country* country)
{
    if (country == nullptr) {
        std::cout << "Country is not initialized.\n";
        return;
    }

    std::cout << "\n=== Country Information ===\n";
    std::cout << "Name: " << country->name << '\n';
    std::cout << "Mainland: " << country->mainland << '\n';
    std::cout << "Visa required: "
        << (country->visaRequired ? "Yes" : "No") << '\n';
    std::cout << "Tourist attractiveness: "
        << country->touristAttractiveness << '\n';
}

// Edit country information
void editCountryInfo(Country* country)
{
    if (country == nullptr) {
        std::cout << "Country is not initialized.\n";
        return;
    }

    std::string input;

    std::cout << "Enter new country name (empty to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        country->name = input;
    }

    std::cout << "Enter mainland (empty to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        country->mainland = input;
    }

    std::cout << "Is a visa required? (yes/no, empty to keep current): ";
    std::getline(std::cin, input);

    if (!input.empty()) {
        if (input == "yes" || input == "Yes" ||
            input == "YES" || input == "y") {
            country->visaRequired = true;
        }
        else if (input == "no" || input == "No" ||
            input == "NO" || input == "n") {
            country->visaRequired = false;
        }
        else {
            std::cout << "Invalid answer. Previous value retained.\n";
        }
    }

    std::cout << "Enter tourist attractiveness (empty to keep current): ";
    std::getline(std::cin, input);

    if (!input.empty()) {
        try {
            std::size_t position = 0;
            unsigned long value = std::stoul(input, &position);

            if (position != input.size() ||
                value > std::numeric_limits<uint>::max()) {
                throw std::invalid_argument("Invalid value");
            }

            country->touristAttractiveness =
                static_cast<uint>(value);
        }
        catch (const std::exception&) {
            std::cout << "Invalid number. Previous value retained.\n";
        }
    }

    std::cout << "Country information updated.\n";
}

// Delete a country from a vacation
void deleteCountry(Vacation* vacation, Country* countryToDelete)
{
    if (vacation == nullptr ||
        countryToDelete == nullptr ||
        vacation->countryArray == nullptr) {
        return;
    }

    for (uint i = 0; i < vacation->countryCount; ++i) {
        if (vacation->countryArray[i] == countryToDelete) {
            delete vacation->countryArray[i];

            for (uint j = i; j + 1 < vacation->countryCount; ++j) {
                vacation->countryArray[j] =
                    vacation->countryArray[j + 1];
            }

            --vacation->countryCount;

            if (vacation->countryCount == 0) {
                delete[] vacation->countryArray;
                vacation->countryArray = nullptr;
            }
            else {
                Country** newArray =
                    new Country * [vacation->countryCount];

                for (uint k = 0; k < vacation->countryCount; ++k) {
                    newArray[k] = vacation->countryArray[k];
                }

                delete[] vacation->countryArray;
                vacation->countryArray = newArray;
            }

            std::cout << "Country deleted successfully.\n";
            return;
        }
    }

    std::cout << "Country was not found.\n";
}

// List all resorts in a country
void listResorts(Country* country)
{
    if (country == nullptr) {
        std::cout << "Country is not initialized.\n";
        return;
    }

    Resort* current = country->firstResort;

    if (current == nullptr) {
        std::cout << "No resorts have been added to "
            << country->name << ".\n";
        return;
    }

    std::cout << "\n=== Resorts in " << country->name << " ===\n";

    int index = 1;

    while (current != nullptr) {
        std::cout << index++ << ". " << current->name
            << " | Type: " << current->type
            << " | Location: " << current->location << '\n';

        current = current->nextResort;
    }
}

// Add a resort to a country's linked list
void addResort(Country* country, Resort* resort)
{
    if (country == nullptr || resort == nullptr) {
        return;
    }

    if (country->firstResort == nullptr) {
        country->firstResort = resort;
        return;
    }

    Resort* current = country->firstResort;

    while (current->nextResort != nullptr) {
        current = current->nextResort;
    }

    current->nextResort = resort;
}