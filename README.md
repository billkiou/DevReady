# Call Management Backend

A C++ backend application for managing call records, built as part of the DevReady Accelerator.

## Technologies

- C++17
- Crow HTTP Framework
- nlohmann/json
- CMake
- vcpkg

## Features

- Retrieve all non-archived calls
- Retrieve a specific call with its notes
- Archive a call
- Load initial data from JSON files
- Handle HTTP errors

## API Endpoints

| Method | Endpoint | Description |
|---|---|---|
| GET | `/calls` | Retrieve all active calls |
| GET | `/calls/{id}` | Retrieve a call with its notes |
| PATCH | `/calls/{id}/archive` | Archive a call |

## HTTP Status Codes

| Status | Description |
|---|---|
| 200 OK | Successful request |
| 400 Bad Request | Invalid request body |
| 404 Not Found | Call not found |
| 405 Method Not Allowed | Unsupported HTTP method |
| 500 Internal Server Error | Unexpected server error |

## Build and Run

Configure the project using CMake and vcpkg:

```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

Build:

```powershell
cmake --build build --config Debug
```

Run the server:

```powershell
.\build\Debug\call-management-backend.exe
```

The API runs at `http://localhost:18080`.

## Example Requests

**200 OK — Get all active calls**

```powershell
curl.exe -i http://localhost:18080/calls
```

**200 OK — Get a specific call**

```powershell
curl.exe -i http://localhost:18080/calls/1
```

**200 OK — Archive a call**

```powershell
curl.exe -i -X PATCH http://localhost:18080/calls/1/archive
```

**400 Bad Request — Invalid JSON body**

```powershell
curl.exe -i -X PATCH http://localhost:18080/calls/3/archive -H "Content-Type: application/json" -d "invalid"
```

Expected response:

```json
{"error":"Invalid request body"}
```

**404 Not Found — Call does not exist**

```powershell
curl.exe -i http://localhost:18080/calls/999
```

Expected response:

```json
{"error":"Call not found"}
```

**405 Method Not Allowed — Unsupported method**

```powershell
curl.exe -i -X POST http://localhost:18080/calls
```

**500 Internal Server Error — Exception handling**

A `/test-error` endpoint is included as commented-out code in `main.cpp`.

To test it, uncomment the endpoint, rebuild and restart the server, then run:

```powershell
curl.exe -i http://localhost:18080/test-error
```

Expected response:

```json
{"error":"Internal server error"}
```

Comment out the test endpoint again after testing.

## Testing

Run the repository tests:

```powershell
.\build\Debug\call-management-tests.exe
```

HTTP endpoints and status codes (200, 400, 404, 405, 500) were also manually tested using curl.

## Notes

Call data is loaded from JSON files at startup. Archiving modifies the in-memory repository and is not persisted to the source JSON files.