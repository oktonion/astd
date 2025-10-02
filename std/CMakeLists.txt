
cmake_minimum_required (VERSION 3.15)


# Set the project name
project ("angelscript-std" VERSION 1.0.0 LANGUAGES C CXX)

# Set project variables

set(ASTD_LIB_DIRECTORY ${PROJECT_SOURCE_DIR})
set(ANGELSCRIPT_LIB_DIRECTORY ${PROJECT_SOURCE_DIR}/../angelscript)

# Set CMake variables
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ASTD_LIB_DIRECTORY}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ASTD_LIB_DIRECTORY}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ASTD_LIB_DIRECTORY}/lib")
foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} "${ASTD_LIB_DIRECTORY}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} "${ASTD_LIB_DIRECTORY}/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} "${ASTD_LIB_DIRECTORY}/lib")
endforeach()


# Platform specific: add compile definitions, libraries

if (NOT ${CMAKE_CXX_STANDARD})
    set(CMAKE_CXX_STANDARD 98)
endif()
message(STATUS "Target compiler CXX standard is C++" ${CMAKE_CXX_STANDARD})

if (CMAKE_SYSTEM MATCHES Windows*)
    set(TESTS_TARGET_SYSTEM "Windows")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS)
    message(STATUS "Target system '${CMAKE_SYSTEM}' is ${TESTS_TARGET_SYSTEM}")
else()
    set(TESTS_TARGET_SYSTEM "Unix")
    message(STATUS "Target system '${CMAKE_SYSTEM}' is ${TESTS_TARGET_SYSTEM}")
endif()


# Add includes
include_directories(
    ${PROJECT_SOURCE_DIR}  
    ${ANGELSCRIPT_LIB_DIRECTORY}
    ${ANGELSCRIPT_LIB_DIRECTORY}/sdk/angelscript/include
    ${ANGELSCRIPT_LIB_DIRECTORY}/sdk/add_on
)

# Create AngelScript Standard Library

aux_source_directory("${ASTD_LIB_DIRECTORY}/memory"      ASTD_LIB_SOURCES)
aux_source_directory("${ASTD_LIB_DIRECTORY}/algorithm"   ASTD_LIB_SOURCES)
aux_source_directory("${ASTD_LIB_DIRECTORY}/coroutines"  ASTD_LIB_SOURCES)
aux_source_directory("${ASTD_LIB_DIRECTORY}/chrono"      ASTD_LIB_SOURCES)
aux_source_directory("${ASTD_LIB_DIRECTORY}/ratio"       ASTD_LIB_SOURCES)
aux_source_directory("${ASTD_LIB_DIRECTORY}/format"      ASTD_LIB_SOURCES)
aux_source_directory("${ASTD_LIB_DIRECTORY}/format/fmt"  ASTD_LIB_SOURCES)
aux_source_directory("${ASTD_LIB_DIRECTORY}/scan"        ASTD_LIB_SOURCES)
aux_source_directory("${ASTD_LIB_DIRECTORY}/scan/scn"    ASTD_LIB_SOURCES)

add_library(angelscript-std STATIC ${ASTD_LIB_SOURCES})