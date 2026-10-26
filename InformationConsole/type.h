#pragma once

#include <cstdint>
#include <string>

typedef uint32_t uint;

// Hotel
struct Hotel {
    std::string name;
    uint rating = 0;
    uint price = 0;
    bool hasPool = false;

    Hotel* nextHotel = nullptr;

    Hotel() = default;

    Hotel(const std::string& n, uint r, uint p, bool pool)
        : name(n), rating(r), price(p), hasPool(pool) {
    }
};

// Resort
struct Resort {
    std::string name;
    std::string type;
    std::string location;

    Hotel* firstHotel = nullptr;
    Resort* nextResort = nullptr;

    Resort() = default;

    Resort(const std::string& n,
        const std::string& t,
        const std::string& loc)
        : name(n), type(t), location(loc) {
    }

    ~Resort() {
        Hotel* currHotel = firstHotel;

        while (currHotel != nullptr) {
            Hotel* nextHotel = currHotel->nextHotel;
            delete currHotel;
            currHotel = nextHotel;
        }
    }
};

// Country
struct Country {
    std::string name;
    std::string mainland;
    bool visaRequired = false;
    uint touristAttractiveness = 0;

    Resort* firstResort = nullptr;
    Country* nextCountry = nullptr;

    Country() = default;

    ~Country() {
        Resort* currResort = firstResort;

        while (currResort != nullptr) {
            Resort* nextResort = currResort->nextResort;
            delete currResort;
            currResort = nextResort;
        }
    }
};

// Vacation
struct Vacation {
    std::string name;
    uint duration = 0;
    std::string season;

    uint countryCount = 0;
    Country** countryArray = nullptr;

    Vacation() = default;

    ~Vacation() {
        if (countryArray != nullptr) {
            for (uint i = 0; i < countryCount; ++i) {
                delete countryArray[i];
            }

            delete[] countryArray;
        }
    }
};