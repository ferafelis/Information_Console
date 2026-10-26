#pragma once

#include "type.h"

// Vacation
Vacation* createDefaultVacation();
void ShowVacationInfo(Vacation* vacation);
void EditVacationInfo(Vacation* vacation);
Vacation* DeleteVacation(Vacation* vacation);
void listCountries(Vacation* vacation);
void addCountry(Vacation* vacation, Country* country);

// Country
void showCountryInfo(Country* country);
void editCountryInfo(Country* country);
void deleteCountry(Vacation* vacation, Country* countryToDelete);
void listResorts(Country* country);
void addResort(Country* country, Resort* resort);

// Resort
void showResortInfo(Resort* resort);
void EditResortInfo(Resort* resort);
void deleteResort(Country* country, Resort* resortToDelete);
void listHotels(Resort* resort);
void addHotel(Resort* resort, Hotel* hotel);

// Hotel
void showHotelInfo(Hotel* hotel);
void EditHotelInfo(Hotel* hotel);
void deleteHotel(Resort* resort, Hotel* hotelToDelete);

// Queries
void ShowHotelsWithPool(Vacation* vacation);
void ShowSkiResorts(Vacation* vacation);
void ShowBudgetHotels(Vacation* vacation, uint maxPrice);

// Binary file operations
void SaveVacationToBinary(
    const char* filename,
    const Vacation* vacation
);

Vacation* LoadVacationFromBinary(const char* filename);
