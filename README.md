# InformationConsole

A console-based Recreation Information System written in standard C++.

The application allows users to manage vacation information, countries, resorts, and hotels through a menu-driven interface.

## Features

- View and edit vacation information
- Add, list, edit, and delete countries
- Manage resorts within countries
- Manage hotels within resorts
- Search for hotels with swimming pools
- Find ski resorts
- Search for hotels by maximum price
- Save and load data using binary files
- Load saved data at startup and save data on exit

## Technologies

- C++
- Visual Studio
- Standard C++ library
- Dynamic arrays and linked lists
- Binary file handling

## Project Structure

- `main.cpp` — main menu and application navigation
- `type.h` — data structure definitions
- `prototype.h` — function declarations
- `vacation.cpp` — vacation management
- `country.cpp` — country management
- `resort.cpp` — resort management
- `hotel.cpp` — hotel management
- `query.cpp` — search functions and binary file operations

## How to Run

1. Clone or download this repository.
2. Open `InformationConsole.slnx` in a compatible version of Visual Studio.
3. Build the project.
4. Run the application.

## Data Storage

The application stores vacation information in a binary file named `vacation.dat`. When available, the file is loaded at startup. The application also supports manual saving and loading through the menu.

## Testing

The application has been tested for:
- Adding, editing, listing, and deleting countries, resorts, and hotels
- Searching for hotels and resorts
- Saving and loading vacation data
- Empty lists and deleting the last country
- Missing and invalid binary files
- Data persistence after restarting the program
