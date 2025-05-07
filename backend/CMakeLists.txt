cmake_minimum_required(VERSION 3.10)
project(SmartResponseBackend)

set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(backend main.cpp)

# Include directories for headers
target_include_directories(backend PRIVATE ../headers nlohmann)

# Link with the import library (.lib), not the DLL directly
# Replace SMARTResponseSDK.lib with the actual path if needed
target_link_libraries(backend PRIVATE SMARTResponseSDK.lib)
