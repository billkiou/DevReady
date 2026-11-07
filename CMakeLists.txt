cmake_minimum_required(VERSION 3.20)

project (CallManagementBackend
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(nlohmann_json CONFIG REQUIRED
    PATHS "C:/vcpkg/packages/nlohmann-json_x64-windows/share/nlohmann_json"
    NO_DEFAULT_PATH
)

add_executable(call-management-backend
    call-management-backend/src/main.cpp
    call-management-backend/src/repositories/CallRepository.cpp
)

target_link_libraries(call-management-backend
    PRIVATE nlohmann_json::nlohmann_json
)