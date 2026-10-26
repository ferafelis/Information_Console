
#include "prototype.h"

#include <iostream>
#include <string>
#include <limits>

// Create a vacation with default values
Vacation* createDefaultVacation()
{
    Vacation* vacation = new Vacation();

    vacation->name = "My Vacation";
    vacation->duration = 7;
    vacation->season = "Summer";
    vacation->countryCount = 0;
    vacation->countryArray = nullptr;

    return vacation;
}

// Display vacation information
void ShowVacationInfo(Vacation* vacation)
{
    if (vacation == nullptr) {
        std::cout << "Vacation is not initialized.\n";
        return;
    }

    std::cout << "\n=== Vacation Information ===\n";
    std::cout << "Name: " << vacation->name << '\n';
    std::cout << "Duration: " << vacation->duration << " days\n";
    std::cout << "Season: " << vacation->season << '\n';
    std::cout << "Number of countries: "
        << vacation->countryCount << '\n';
}

// Edit vacation information
void EditVacationInfo(Vacation* vacation)
{
    if (vacation == nullptr) {
        std::cout << "Vacation is not initialized.\n";
        return;
    }

    std::string input;

    std::cout << "Enter a new vacation name (leave empty to keep current): ";
    std::getline(std::cin, input);

    if (!input.empty()) {
        vacation->name = input;
    }

    std::cout << "Enter duration in days (leave empty to keep current): ";
    std::getline(std::cin, input);

    if (!input.empty()) {
        try {
            std::size_t position = 0;
            unsigned long value = std::stoul(input, &position);

            if (position != input.size() ||
                value == 0 ||
                value > std::numeric_limits<uint>::max()) {
                throw std::invalid_argument("Invalid duration");
            }

            vacation->duration = static_cast<uint>(value);
        }
        catch (const std::exception&) {
            std::cout << "Invalid duration. Previous value retained.\n";
        }
    }

    std::cout << "Enter a new season (leave empty to keep current): ";
    std::getline(std::cin, input);

    if (!input.empty()) {
        vacation->season = input;
    }

    std::cout << "Vacation information updated.\n";
}

// List all countries belonging to a vacation
void listCountries(Vacation* vacation)
{
    if (vacation == nullptr) {
        std::cout << "Vacation is not initialized.\n";
        return;
    }

    if (vacation->countryCount == 0) {
        std::cout << "No countries have been added yet.\n";
        return;
    }

    std::cout << "\n=== Countries ===\n";

    for (uint i = 0; i < vacation->countryCount; ++i) {
        Country* country = vacation->countryArray[i];

        if (country == nullptr) {
            continue;
        }

        std::cout << i + 1 << ". " << country->name
            << " | Mainland: " << country->mainland
            << " | Visa required: "
            << (country->visaRequired ? "Yes" : "No")
            << " | Tourist attractiveness: "
            << country->touristAttractiveness
            << '\n';
    }
}

// Add a country to the vacation's dynamic array
void addCountry(Vacation* vacation, Country* country)
{
    if (vacation == nullptr || country == nullptr) {
        return;
    }

    Country** newArray =
        new Country * [vacation->countryCount + 1];

    for (uint i = 0; i < vacation->countryCount; ++i) {
        newArray[i] = vacation->countryArray[i];
    }

    newArray[vacation->countryCount] = country;

    delete[] vacation->countryArray;

    vacation->countryArray = newArray;
    ++vacation->countryCount;
}

// Delete a vacation and all data it owns
Vacation* DeleteVacation(Vacation* vacation)
{
    delete vacation;
    return nullptr;
}
