# CMake file mostly written from this example:
# https://cliutils.gitlab.io/modern-cmake/chapters/packages/ROOT.html
# https://cliutils.gitlab.io/modern-cmake/examples/root-dict/

# Assert CMake version
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# This is your project statement. You should always list languages
project(RooPositronGui LANGUAGES CXX)

# Find ROOT
find_package(ROOT CONFIG REQUIRED)

# Debug output - print all variables set by ROOT: https://gist.github.com/drautb/5922368
# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   if ("${_variableName}" MATCHES "ROOT")
#     message(STATUS "${_variableName}=${${_variableName}}")
#   endif()
# endforeach()

# Obtain ROOT C++ standard from ROOT_CXX_STANDARD variable
string(REGEX MATCH "-std=c\\+\\+([0-9]+)" ROOT_CXX_STANDARD "${ROOT_CXX_FLAGS}")
set(ROOT_CXX_STANDARD "${CMAKE_MATCH_1}")
message(STATUS "Found ROOT CXX standard: ${ROOT_CXX_STANDARD}")

# For setting project in IDE via CMake generators
include_directories(${ROOT_INCLUDE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/src)

# First find all headers in project
# file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
                  ${PROJECT_SOURCE_DIR}/src/*.hpp
                  ${PROJECT_SOURCE_DIR}/src/*.hxx
                  ${PROJECT_SOURCE_DIR}/src/*.hh
                  ${PROJECT_SOURCE_DIR}/src/*.h)
message(STATUS "Found list of all header files: ${HEADERS}")

# Find LinkDef.h file
file(GLOB_RECURSE LINKDEFH ${CMAKE_CURRENT_SOURCE_DIR}/*.hxx ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hh ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
list(FILTER LINKDEFH INCLUDE REGEX "[lL]ink[dD]ef")
message(STATUS "Found LinkDef file: ${LINKDEFH}")

# Exclude Linkdef from other headers
list(REMOVE_ITEM HEADERS ${LINKDEFH})

# TARGET: generate the dictionary (extra C++ file containing custom ROOT methods)
set(DICTIONARY_TARGET ${PROJECT_NAME})
root_generate_dictionary(${DICTIONARY_TARGET} ${HEADERS} LINKDEF ${LINKDEFH})

# Tip: name of the generated dictionary is same as target name with .cxx extension: ${DICTIONARY_TARGET}.cxx
#      cmake automatically searches for .cpp, cxx etc files so neo need to add extension below
set(DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/${DICTIONARY_TARGET})
message(STATUS "Created dictionary file: ${DICTIONARY}")

# Find sources in project
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
                  ${PROJECT_SOURCE_DIR}/src/*.cpp
                  ${PROJECT_SOURCE_DIR}/src/*.cxx
                  ${PROJECT_SOURCE_DIR}/src/*.cc
                  ${PROJECT_SOURCE_DIR}/src/*.c)
message(STATUS "Found list of source files: ${SOURCES}")

# Compose list of ROOT libraries with "ROOT::" prefix - need to link them to the shared library
# Append required ROOT libs to the list
  set(LIB_NAMES "")
  FOREACH(X IN LISTS ROOT_LIBRARIES)
    get_filename_component(FILENAME ${X} NAME)
    string(REGEX REPLACE "lib([a-zA-Z0-9]+).so" "ROOT::\\1" FILENAME2 ${FILENAME})
    list(APPEND LIB_NAMES "${FILENAME2}")
  ENDFOREACH()

# Manually append extra ROOT libraries
  list(APPEND LIB_NAMES "ROOT::Gui")
  list(APPEND LIB_NAMES "ROOT::RooFit")
  list(APPEND LIB_NAMES "ROOT::RooFitCore")
  list(APPEND LIB_NAMES "ROOT::Html")
  list(APPEND LIB_NAMES "ROOT::Minuit")
  list(APPEND LIB_NAMES "ROOT::Fumili")

# TARGET: create shared library
set(SHARED_LIB_TARGET ${PROJECT_NAME}-so)

# Option 1: use ROOT_LINKER_LIBRARY function (works)
# ROOT_LINKER_LIBRARY(${SHARED_LIB_TARGET} ${SOURCES} ${DICTIONARY} DEPENDENCIES ${LIB_NAMES})

# Option 2: create library manually
add_library(${SHARED_LIB_TARGET} SHARED)

# Tip: ROOT-based programs should be built with the same standard as ROOT itself
set_property(TARGET ${SHARED_LIB_TARGET} PROPERTY CXX_STANDARD ${ROOT_CXX_STANDARD})
# Tip: specify PUBLIC_HEADER library files (used on the install step)
set_property(TARGET ${SHARED_LIB_TARGET} PROPERTY PUBLIC_HEADER ${HEADERS})
# Tip: cmake target name and target output file name can be different. Here we tell target "<project-name>-so" produces library named "<project-name>" 
set_property(TARGET ${SHARED_LIB_TARGET} PROPERTY OUTPUT_NAME ${PROJECT_NAME})

# Tip: multiple properties can be set with: set_target_properties(${SHARED_LIB_TARGET} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}) 

# Specify sources that shared library target should be built from. Dictionary file goes last
target_sources(${SHARED_LIB_TARGET} PUBLIC ${SOURCES} ${DICTIONARY})

# Link found libraries to the project shared library
target_link_libraries(${SHARED_LIB_TARGET} PUBLIC ${LIB_NAMES})
message(STATUS "Created shared library target.")

# TARGET: executable name is same as target name here
# Entry point - file containing the main() cpp function
set(MAIN_CPP "${PROJECT_SOURCE_DIR}/src/main.cpp")

set(EXECUTABLE_TARGET ${PROJECT_NAME}-bin)
add_executable(${EXECUTABLE_TARGET} ${MAIN_CPP})

# Specify CMake standard: 
set_property(TARGET ${SHARED_LIB_TARGET} PROPERTY CXX_STANDARD ${ROOT_CXX_STANDARD})
# Compose executable name - striup path and extension from the "main()" file
get_filename_component(EXECUTABLE_NAME "${PROJECT_NAME}" NAME_WE)
set_property(TARGET ${EXECUTABLE_TARGET} PROPERTY OUTPUT_NAME ${EXECUTABLE_NAME})

# Set output name for the executable - trick to have library and binary with the same name 
target_link_libraries(${EXECUTABLE_TARGET} ${SHARED_LIB_TARGET})
