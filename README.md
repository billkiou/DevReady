# Call Management Backend

A C++ backend project developed for DevReady Week 2.

The application manages call records and their associated notes using JSON files and an in-memory repository.

## Features

- Load calls and notes from JSON files.
- Retrieve all non-archived calls.
- Find a call by its ID.
- Retrieve notes associated with a call.
- Archive a call by updating its in-memory status.
- Handle requests for calls that do not exist.

## Technologies

- C++17
- CMake
- nlohmann/json
- vcpkg

## How to Run

### Prerequisites

- C++17-compatible compiler
- CMake
- vcpkg

### Build

From the project root directory:

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

### Run

On Windows, using the Visual Studio Debug build:

```powershell
.\build\Debug\call-management-backend.exe
```

## Project Structure

- `call-management-backend/data/` — JSON files containing calls and notes.
- `call-management-backend/src/models/` — Call and Note data models.
- `call-management-backend/src/repositories/` — CallRepository implementation.
- `call-management-backend/src/main.cpp` — Tests for repository functionality.

## Known Limitations

- Data is stored in memory after loading.
- Archiving a call does not update the original JSON file.
- There is no database, HTTP server, or graphical interface.
- Repository functionality is tested directly from `main.cpp`.

## Assignment

DevReady — Week 2: Call Management Backend.