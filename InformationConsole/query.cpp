#include "prototype.h"
#include <vector>
#include <fstream>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <iostream>

// Display all hotels that have a swimming pool
void ShowHotelsWithPool(Vacation* vacation)
{
    if (vacation == nullptr) {
        std::cout << "Vacation is not initialized.\n";
        return;
    }

    bool found = false;

    std::cout << "\n=== Hotels with a Pool ===\n";

    for (uint i = 0; i < vacation->countryCount; ++i) {
        Country* country = vacation->countryArray[i];

        if (country == nullptr) {
            continue;
        }

        Resort* resort = country->firstResort;

        while (resort != nullptr) {
            Hotel* hotel = resort->firstHotel;

            while (hotel != nullptr) {
                if (hotel->hasPool) {
                    std::cout << "Country: " << country->name
                        << " | Resort: " << resort->name
                        << " | Hotel: " << hotel->name
                        << " | Rating: " << hotel->rating
                        << " | Price: " << hotel->price
                        << '\n';

                    found = true;
                }

                hotel = hotel->nextHotel;
            }

            resort = resort->nextResort;
        }
    }

    if (!found) {
        std::cout << "No hotels with a pool were found.\n";
    }
}

// Display all ski resorts
void ShowSkiResorts(Vacation* vacation)
{
    if (vacation == nullptr) {
        std::cout << "Vacation is not initialized.\n";
        return;
    }

    bool found = false;

    std::cout << "\n=== Ski Resorts ===\n";

    for (uint i = 0; i < vacation->countryCount; ++i) {
        Country* country = vacation->countryArray[i];

        if (country == nullptr) {
            continue;
        }

        Resort* resort = country->firstResort;

        while (resort != nullptr) {
            if (resort->type == "Ski" ||
                resort->type == "ski" ||
                resort->type == "SKI") {

                std::cout << "Country: " << country->name
                    << " | Resort: " << resort->name
                    << " | Location: " << resort->location
                    << '\n';

                found = true;
            }

            resort = resort->nextResort;
        }
    }

    if (!found) {
        std::cout << "No ski resorts were found.\n";
    }
}

// Display hotels whose price does not exceed maxPrice
void ShowBudgetHotels(Vacation* vacation, uint maxPrice)
{
    if (vacation == nullptr) {
        std::cout << "Vacation is not initialized.\n";
        return;
    }

    bool found = false;

    std::cout << "\n=== Budget Hotels (Maximum Price: "
        << maxPrice << ") ===\n";

    for (uint i = 0; i < vacation->countryCount; ++i) {
        Country* country = vacation->countryArray[i];

        if (country == nullptr) {
            continue;
        }

        Resort* resort = country->firstResort;

        while (resort != nullptr) {
            Hotel* hotel = resort->firstHotel;

            while (hotel != nullptr) {
                if (hotel->price <= maxPrice) {
                    std::cout << "Country: " << country->name
                        << " | Resort: " << resort->name
                        << " | Hotel: " << hotel->name
                        << " | Price: " << hotel->price
                        << " | Rating: " << hotel->rating
                        << '\n';

                    found = true;
                }

                hotel = hotel->nextHotel;
            }

            resort = resort->nextResort;
        }
    }

    if (!found) {
        std::cout << "No hotels within this price limit were found.\n";
    }
}
namespace
{
    // Write a 32-bit unsigned integer
    bool writeUInt(std::ofstream& file, uint32_t value)
    {
        file.write(
            reinterpret_cast<const char*>(&value),
            sizeof(value)
        );

        return file.good();
    }

    // Read a 32-bit unsigned integer
    bool readUInt(std::ifstream& file, uint32_t& value)
    {
        file.read(
            reinterpret_cast<char*>(&value),
            sizeof(value)
        );

        return file.good();
    }

    // Write a string as: length followed by characters
    bool writeString(std::ofstream& file, const std::string& value)
    {
        if (value.size() > 1024 * 1024) {
            return false;
        }

        if (!writeUInt(file, static_cast<uint32_t>(value.size()))) {
            return false;
        }

        file.write(value.data(),
            static_cast<std::streamsize>(value.size()));

        return file.good();
    }

    // Read a string from the binary file
    bool readString(std::ifstream& file, std::string& value)
    {
        uint32_t length = 0;

        if (!readUInt(file, length)) {
            return false;
        }

        // Reject unreasonably large strings
        if (length > 1024 * 1024) {
            return false;
        }

        value.resize(length);

        if (length > 0) {
            file.read(&value[0],
                static_cast<std::streamsize>(length));
        }

        return file.good();
    }
}
void SaveVacationToBinary(
    const char* filename,
    const Vacation* vacation)
{
    if (filename == nullptr || vacation == nullptr) {
        std::cout << "Cannot save vacation: invalid argument.\n";
        return;
    }

    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Could not open file for saving.\n";
        return;
    }

    // File format identifier and version
    file.write("VACT", 4);

    if (!file.good() ||
        !writeUInt(file, 1) ||
        !writeString(file, vacation->name) ||
        !writeUInt(file, vacation->duration) ||
        !writeString(file, vacation->season) ||
        !writeUInt(file, vacation->countryCount)) {

        std::cout << "Error writing vacation information.\n";
        return;
    }

    for (uint i = 0; i < vacation->countryCount; ++i) {
        const Country* country = vacation->countryArray[i];

        if (country == nullptr) {
            std::cout << "Cannot save a null country.\n";
            return;
        }

        uint32_t resortCount = 0;

        for (const Resort* r = country->firstResort;
            r != nullptr; r = r->nextResort) {
            ++resortCount;
        }

        if (!writeString(file, country->name) ||
            !writeString(file, country->mainland) ||
            !writeUInt(file, country->visaRequired ? 1 : 0) ||
            !writeUInt(file, country->touristAttractiveness) ||
            !writeUInt(file, resortCount)) {

            std::cout << "Error writing country information.\n";
            return;
        }

        const Resort* resort = country->firstResort;

        while (resort != nullptr) {
            uint32_t hotelCount = 0;

            for (const Hotel* h = resort->firstHotel;
                h != nullptr; h = h->nextHotel) {
                ++hotelCount;
            }

            if (!writeString(file, resort->name) ||
                !writeString(file, resort->type) ||
                !writeString(file, resort->location) ||
                !writeUInt(file, hotelCount)) {

                std::cout << "Error writing resort information.\n";
                return;
            }

            const Hotel* hotel = resort->firstHotel;

            while (hotel != nullptr) {
                if (!writeString(file, hotel->name) ||
                    !writeUInt(file, hotel->rating) ||
                    !writeUInt(file, hotel->price) ||
                    !writeUInt(file, hotel->hasPool ? 1 : 0)) {

                    std::cout << "Error writing hotel information.\n";
                    return;
                }

                hotel = hotel->nextHotel;
            }

            resort = resort->nextResort;
        }
    }

    file.close();

    if (!file) {
        std::cout << "Error closing the binary file.\n";
        return;
    }

    std::cout << "Vacation saved successfully to "
        << filename << ".\n";
}
Vacation* LoadVacationFromBinary(const char* filename)
{
    if (filename == nullptr) {
        std::cout << "Cannot load vacation: invalid filename.\n";
        return nullptr;
    }

    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Could not open file for loading.\n";
        return nullptr;
    }

    Vacation* vacation = new Vacation();
    std::vector<Country*> loadedCountries;

    // Countries are temporarily owned by this vector.
    // They are transferred to vacation after successful loading.
    try {
        char signature[4];

        file.read(signature, sizeof(signature));

        if (!file ||
            signature[0] != 'V' ||
            signature[1] != 'A' ||
            signature[2] != 'C' ||
            signature[3] != 'T') {
            throw std::runtime_error("Invalid file format.");
        }

        uint32_t version = 0;

        if (!readUInt(file, version) || version != 1) {
            throw std::runtime_error("Unsupported file version.");
        }

        uint32_t countryCount = 0;

        if (!readString(file, vacation->name) ||
            !readUInt(file, vacation->duration) ||
            !readString(file, vacation->season) ||
            !readUInt(file, countryCount)) {
            throw std::runtime_error("Invalid vacation data.");
        }

        // Prevent unreasonable allocation requests
        if (countryCount > 100000) {
            throw std::runtime_error("Too many countries in file.");
        }

        loadedCountries.reserve(countryCount);

        for (uint32_t i = 0; i < countryCount; ++i) {
            Country* country = new Country();
            loadedCountries.push_back(country);

            uint32_t visa = 0;
            uint32_t resortCount = 0;

            if (!readString(file, country->name) ||
                !readString(file, country->mainland) ||
                !readUInt(file, visa) ||
                visa > 1 ||
                !readUInt(file, country->touristAttractiveness) ||
                !readUInt(file, resortCount)) {
                throw std::runtime_error("Invalid country data.");
            }

            country->visaRequired = (visa == 1);

            if (resortCount > 100000) {
                throw std::runtime_error("Too many resorts in file.");
            }

            for (uint32_t j = 0; j < resortCount; ++j) {
                Resort* resort = new Resort();

                // Attach immediately so the country owns this resort.
                addResort(country, resort);

                uint32_t hotelCount = 0;

                if (!readString(file, resort->name) ||
                    !readString(file, resort->type) ||
                    !readString(file, resort->location) ||
                    !readUInt(file, hotelCount)) {
                    throw std::runtime_error("Invalid resort data.");
                }

                if (hotelCount > 100000) {
                    throw std::runtime_error("Too many hotels in file.");
                }

                for (uint32_t k = 0; k < hotelCount; ++k) {
                    Hotel* hotel = new Hotel();

                    // Attach immediately so the resort owns this hotel.
                    addHotel(resort, hotel);

                    uint32_t rating = 0;
                    uint32_t price = 0;
                    uint32_t pool = 0;

                    if (!readString(file, hotel->name) ||
                        !readUInt(file, rating) ||
                        rating > 5 ||
                        !readUInt(file, price) ||
                        !readUInt(file, pool) ||
                        pool > 1) {
                        throw std::runtime_error("Invalid hotel data.");
                    }

                    hotel->rating = rating;
                    hotel->price = price;
                    hotel->hasPool = (pool == 1);
                }
            }
        }

        // Reject files containing unexpected trailing data.
        char extraByte;

        if (file.get(extraByte)) {
            throw std::runtime_error("Unexpected data at end of file.");
        }

        if (!file.eof()) {
            throw std::runtime_error("Error reading binary file.");
        }

        // Transfer ownership of the countries to Vacation.
        vacation->countryCount =
            static_cast<uint>(loadedCountries.size());

        if (vacation->countryCount > 0) {
            vacation->countryArray =
                new Country * [vacation->countryCount];

            for (uint i = 0; i < vacation->countryCount; ++i) {
                vacation->countryArray[i] = loadedCountries[i];
            }
        }

        loadedCountries.clear();

        std::cout << "Vacation loaded successfully from "
            << filename << ".\n";

        return vacation;
    }
    catch (const std::exception& error) {
        for (Country* country : loadedCountries) {
            delete country;
        }

        delete vacation;

        std::cout << "Error loading vacation: "
            << error.what() << '\n';

        return nullptr;
    }
}