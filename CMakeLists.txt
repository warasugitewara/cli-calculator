cmake_minimum_required(VERSION 3.16)
project(calcpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimization flags
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/calculator.cpp
    src/parser.cpp
    src/repl.cpp
    src/fraction.cpp
)

set(HEADERS
    include/calculator.h
    include/parser.h
    include/repl.h
    include/fraction.h
)

# Executable
add_executable(calcpp ${SOURCES} ${HEADERS})
target_include_directories(calcpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Optional: readline library for tab completion
find_package(Readline)
if(Readline_FOUND)
    target_link_libraries(calcpp PRIVATE ${Readline_LIBRARIES})
    target_compile_definitions(calcpp PRIVATE HAVE_READLINE=1)
    message(STATUS "Readline library found - tab completion enabled")
else()
    message(STATUS "Readline library not found - tab completion disabled")
endif()

# Link math library (not needed on Windows)
if(NOT MSVC)
    target_link_libraries(calcpp PRIVATE m)
endif()

# Installation
install(TARGETS calcpp DESTINATION bin)
