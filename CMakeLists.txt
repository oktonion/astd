
cmake_minimum_required (VERSION 3.15)


# Set the project name
project ("astd_tests" VERSION 1.0.0 LANGUAGES C CXX)

# Set project variables

set(TESTS_DIRECTORY ${PROJECT_SOURCE_DIR}/tests)
set(ANGELSCRIPT_LIB_DIRECTORY ${PROJECT_SOURCE_DIR}/angelscript)

# Set CMake variables
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${TESTS_DIRECTORY}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${TESTS_DIRECTORY}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${TESTS_DIRECTORY}/bin")
foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} "${TESTS_DIRECTORY}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} "${TESTS_DIRECTORY}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} "${TESTS_DIRECTORY}/bin")
endforeach()


# Platform specific: add compile definitions, libraries

add_compile_definitions(DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)

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

# Create library with all code

set(ANGELSCRIPT_LIBRARY_NAME ascript)
add_subdirectory("${PROJECT_SOURCE_DIR}/sdk/angelscript/projects/cmake")
set(TESTS_LINK_LIBRARIES ${TESTS_LINK_LIBRARIES} ascript)

# Create executable Tests

aux_source_directory("${TESTS_DIRECTORY}" TESTS_SOURCES)

set(FAIL_TESTS "")

foreach(test_source_file ${TESTS_SOURCES})
    get_filename_component(test_name ${test_source_file} NAME_WE)
    add_executable(${test_name} 
        ${test_source_file}
    )
    set_property(TARGET ${test_name} PROPERTY WORKING_DIRECTORY "${TESTS_DIRECTORY}/bin")
    set_property(TARGET ${test_name} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${TESTS_DIRECTORY}/bin")
    target_link_libraries(${test_name} ${TESTS_LINK_LIBRARIES} )
endforeach(test_source_file ${TEST_SOURCES})

string(REPLACE ";" "," SUCCESS_TESTS "${TESTS_SOURCES}")