#include <iostream>
#include <limits>
#include "prototype.h"

Country* selectCountry(Vacation* vacation)
{
    if (vacation == nullptr || vacation->countryCount == 0) {
        std::cout << "No countries available.\n";
        return nullptr;
    }

    listCountries(vacation);

    std::cout << "Enter country number (0 to cancel): ";

    int choice;

    if (!(std::cin >> choice)) {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
        return nullptr;
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n'
    );

    if (choice == 0) {
        return nullptr;
    }

    if (choice < 1 ||
        static_cast<uint>(choice) > vacation->countryCount) {
        std::cout << "Invalid country number.\n";
        return nullptr;
    }

    return vacation->countryArray[choice - 1];
}
Resort* selectResort(Country* country)
{
    if (country == nullptr || country->firstResort == nullptr) {
        std::cout << "No resorts available.\n";
        return nullptr;
    }

    listResorts(country);

    std::cout << "Enter resort number (0 to cancel): ";
    int choice;

    if (!(std::cin >> choice)) {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
        return nullptr;
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 0) {
        return nullptr;
    }

    int index = 1;
    Resort* current = country->firstResort;

    while (current != nullptr && index < choice) {
        current = current->nextResort;
        ++index;
    }

    if (current == nullptr || choice < 1) {
        std::cout << "Invalid resort number.\n";
        return nullptr;
    }

    return current;
}
Hotel* selectHotel(Resort* resort)
{
    if (resort == nullptr || resort->firstHotel == nullptr) {
        std::cout << "No hotels available.\n";
        return nullptr;
    }

    listHotels(resort);

    std::cout << "Enter hotel number (0 to cancel): ";
    int choice;

    if (!(std::cin >> choice)) {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
        return nullptr;
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 0) {
        return nullptr;
    }

    int index = 1;
    Hotel* current = resort->firstHotel;

    while (current != nullptr && index < choice) {
        current = current->nextHotel;
        ++index;
    }

    if (current == nullptr || choice < 1) {
        std::cout << "Invalid hotel number.\n";
        return nullptr;
    }

    return current;
}

void hotelsMenu(Resort* resort)
{
    if (resort == nullptr) {
        return;
    }

    bool running = true;

    while (running) {
        std::cout << "\n=== Hotels Menu ===\n";
        std::cout << "Resort: " << resort->name << "\n";
        std::cout << "1. List hotels\n";
        std::cout << "2. Add a hotel\n";
        std::cout << "3. Edit a hotel\n";
        std::cout << "4. Delete a hotel\n";
        std::cout << "0. Return to Resorts Menu\n";
        std::cout << "Choose an option: ";

        int choice;

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            listHotels(resort);
            break;

        case 2: {
            Hotel* hotel = new Hotel();

            std::cout << "Enter hotel name: ";
            std::getline(std::cin, hotel->name);

            std::cout << "Enter hotel rating (0-5): ";
            int rating;

            if (!(std::cin >> rating) || rating < 0 || rating > 5) {
                std::cout << "Invalid rating. Hotel not added.\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                delete hotel;
                break;
            }

            hotel->rating = static_cast<uint>(rating);

            std::cout << "Enter hotel price: ";
            int price;

            if (!(std::cin >> price) || price < 0) {
                std::cout << "Invalid price. Hotel not added.\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                delete hotel;
                break;
            }

            hotel->price = static_cast<uint>(price);

            std::cout << "Does the hotel have a pool? (1 = Yes, 0 = No): ";
            int pool;

            if (!(std::cin >> pool) || (pool != 0 && pool != 1)) {
                std::cout << "Invalid value. Hotel not added.\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                delete hotel;
                break;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');

            hotel->hasPool = (pool == 1);

            addHotel(resort, hotel);
            std::cout << "Hotel added successfully.\n";
            break;
        }

        case 3: {
            Hotel* hotel = selectHotel(resort);

            if (hotel != nullptr) {
                EditHotelInfo(hotel);
            }
            break;
        }

        case 4: {
            Hotel* hotel = selectHotel(resort);

            if (hotel != nullptr) {
                deleteHotel(resort, hotel);
                std::cout << "Hotel deleted.\n";
            }
            break;
        }

        case 0:
            running = false;
            break;

        default:
            std::cout << "Unknown option. Please try again.\n";
            break;
        }
    }
}

void searchMenu(Vacation* vacation)
{
    bool running = true;

    while (running) {
        std::cout << "\n=== Search Menu ===\n";
        std::cout << "1. Find hotels with a pool\n";
        std::cout << "2. Find ski resorts\n";
        std::cout << "3. Find hotels by maximum price\n";
        std::cout << "0. Return to Main Menu\n";
        std::cout << "Choose an option: ";

        int choice;

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            ShowHotelsWithPool(vacation);
            break;

        case 2:
            ShowSkiResorts(vacation);
            break;

        case 3: {
            std::cout << "Enter maximum hotel price: ";

            int maxPrice;

            if (!(std::cin >> maxPrice) || maxPrice < 0) {
                std::cout << "Invalid price. Please enter a non-negative number.\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');

            ShowBudgetHotels(
                vacation, static_cast<uint>(maxPrice));
            break;
        }

        case 0:
            running = false;
            break;

        default:
            std::cout << "Unknown option. Please try again.\n";
            break;
        }
    }
}

void resortsMenu(Country* country)
{
    if (country == nullptr) {
        return;
    }

    bool running = true;

    while (running) {
        std::cout << "\n=== Resorts Menu ===\n";
        std::cout << "Country: " << country->name << "\n";
        std::cout << "1. List resorts\n";
        std::cout << "2. Add a resort\n";
        std::cout << "3. Edit a resort\n";
        std::cout << "4. Delete a resort\n";
        std::cout << "5. Manage hotels\n";
        std::cout << "0. Return to Countries Menu\n";
        std::cout << "Choose an option: ";

        int choice;

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            listResorts(country);
            break;

        case 2: {
            Resort* resort = new Resort();

            std::cout << "Enter resort name: ";
            std::getline(std::cin, resort->name);

            std::cout << "Enter resort type (e.g. Beach, Ski): ";
            std::getline(std::cin, resort->type);

            std::cout << "Enter resort location: ";
            std::getline(std::cin, resort->location);

            addResort(country, resort);
            std::cout << "Resort added successfully.\n";
            break;
        }

        case 3: {
            Resort* resort = selectResort(country);

            if (resort != nullptr) {
                EditResortInfo(resort);
            }
            break;
        }

        case 4: {
            Resort* resort = selectResort(country);

            if (resort != nullptr) {
                deleteResort(country, resort);
                std::cout << "Resort deleted.\n";
            }
            break;
        }
        case 5: {
            Resort* resort = selectResort(country);

            if (resort != nullptr) {
                hotelsMenu(resort);
            }
            break;
        }
        case 0:
            running = false;
            break;

        default:
            std::cout << "Unknown option. Please try again.\n";
            break;
        }
    }
}

void countriesMenu(Vacation* vacation)
{
    bool running = true;

    while (running) {
        std::cout << "\n=== Countries Menu ===\n";
        std::cout << "1. List countries\n";
        std::cout << "2. Add a country\n";
        std::cout << "3. Edit a country\n";
        std::cout << "4. Delete a country\n";
        std::cout << "5. Manage resorts\n";
        std::cout << "0. Return to main menu\n";
        std::cout << "Choose an option: ";

        int choice;

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );

        switch (choice) {
        case 1:
            listCountries(vacation);
            break;

        case 2: {
            Country* country = new Country();

            std::cout << "Enter country name: ";
            std::getline(std::cin, country->name);

            std::cout << "Enter mainland/continent: ";
            std::getline(std::cin, country->mainland);

            std::cout << "Is a visa required? (1 = Yes, 0 = No): ";

            int visa;
            if (!(std::cin >> visa) || (visa != 0 && visa != 1)) {
                std::cout << "Invalid visa value. Country not added.\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
                delete country;
                break;
            }

            country->visaRequired = (visa == 1);

            std::cout << "Tourist attractiveness (0-10): ";

            int attractiveness;
            if (!(std::cin >> attractiveness) ||
                attractiveness < 0 || attractiveness > 10) {
                std::cout << "Invalid value. Country not added.\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
                delete country;
                break;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );

            country->touristAttractiveness =
                static_cast<uint>(attractiveness);

            addCountry(vacation, country);

            std::cout << "Country added successfully.\n";
            break;
        }

        case 3: {
            Country* country = selectCountry(vacation);

            if (country != nullptr) {
                editCountryInfo(country);
            }
            break;
        }

        case 4: {
            Country* country = selectCountry(vacation);

            if (country != nullptr) {
                deleteCountry(vacation, country);
                std::cout << "Country deleted.\n";
            }
            break;
        }
        case 5: {
            Country* country = selectCountry(vacation);

            if (country != nullptr) {
                resortsMenu(country);
            }
            break;
        }

        case 0:
            running = false;
            break;

        default:
            std::cout << "Unknown option. Please try again.\n";
            break;
        }
    }
}
int main()
{
    Vacation* vacation = LoadVacationFromBinary("vacation.dat");

    if (vacation == nullptr) {
        std::cout << "No saved vacation found. Creating a new one.\n";
        vacation = createDefaultVacation();
    }

    bool running = true;

    while (running) {
        std::cout << "\n    Vacation Information System   \n";
        std::cout << "1. Show vacation information\n";
        std::cout << "2. Edit vacation information\n";
        std::cout << "3. Manage countries\n";
        std::cout << "4. Search vacation information\n";
        std::cout << "5. Save vacation data\n";
        std::cout << "6. Load vacation data\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";

        int choice;

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        switch (choice) {
        case 1:
            ShowVacationInfo(vacation);
            break;

        case 2:
            EditVacationInfo(vacation);
            break;

        case 3:
            countriesMenu(vacation);
            break;
        case 4:
            searchMenu(vacation);
            break;
        case 5:
            SaveVacationToBinary("vacation.dat", vacation);
            break;

        case 6: {
            Vacation* loadedVacation = LoadVacationFromBinary("vacation.dat");

            if (loadedVacation != nullptr) {
                vacation = DeleteVacation(vacation);
                vacation = loadedVacation;

                std::cout << "Vacation data loaded successfully.\n";
            }
            else {
                std::cout << "Could not load vacation data.\n";
            }

            break;
        }
        case 0:
            running = false;
            break;

        default:
            std::cout << "Unknown option. Please try again.\n";
            break;
        }
    }
    SaveVacationToBinary("vacation.dat", vacation);

    vacation = DeleteVacation(vacation);

    std::cout << "Program closed\n";

    return 0;
}

