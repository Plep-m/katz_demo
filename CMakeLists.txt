cmake_minimum_required(VERSION 3.10)

project(katz_demo VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Find the katz library
find_library(KATZ_LIBRARY NAMES katz PATHS /usr/local/lib)
find_path(KATZ_INCLUDE_DIR NAMES katz/katz.h PATHS /usr/local/include)

if (NOT KATZ_LIBRARY OR NOT KATZ_INCLUDE_DIR)
    message(FATAL_ERROR "katz library or headers not found. Please install katz first.")
endif()

# Include katz headers
include_directories(${KATZ_INCLUDE_DIR})

# Define the executable
add_executable(katz_demo src/main.c)

# Link katz library
target_link_libraries(katz_demo PRIVATE ${KATZ_LIBRARY})

# Collect all route source files from the routes/ directory
file(GLOB ROUTES_SOURCES "${CMAKE_SOURCE_DIR}/routes/*.c")

# Compile route .c files into shared libraries
foreach(route_source ${ROUTES_SOURCES})
    # Extract the route name from the source file name (e.g., route_hello.c -> hello)
    get_filename_component(route_name ${route_source} NAME_WE)
    string(REPLACE "route_" "" route_name ${route_name}) # Remove "route_" prefix

    # Create the shared library for each route
    add_library(${route_name} SHARED ${route_source})

    # Include directories and link the required libraries
    target_include_directories(${route_name} PRIVATE ${KATZ_INCLUDE_DIR})
    target_link_libraries(${route_name} PRIVATE ${KATZ_LIBRARY})

    # Set the output directory and name for the shared library
    set_target_properties(${route_name} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/routes
        OUTPUT_NAME "route_${route_name}" # Ensure the library is named libroute_<name>.so
    )
endforeach()