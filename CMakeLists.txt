cmake_minimum_required (VERSION 2.6)
project (Niban)
include_directories("src")

# Set the name of the executable to be produced
set(EXECUTABLE_NAME Niban)

# Specify the executable and link SFML and X11 libraries
add_executable(Niban src/main.cpp src/Car.cpp src/MainMenu.cpp 
                src/SoundManager.cpp src/Game.cpp )
set(CMAKE_BUILD_TYPE Debug)

# Find Box2D library
set(BOX2D_ROOT "${CMAKE_SOURCE_DIR}/libs/box2d")
include_directories("${BOX2D_ROOT}/include")
add_library(Box2D STATIC IMPORTED)
set_target_properties(Box2D PROPERTIES
    IMPORTED_LOCATION "${BOX2D_ROOT}/build/src/libbox2d.a"
    INTERFACE_INCLUDE_DIRECTORIES "${BOX2D_ROOT}/include"
)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE Box2D X11 Xrandr Xinerama Xcursor Xi)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
   include_directories(${SFML_INCLUDE_DIR})
   target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} sfml-graphics sfml-window sfml-system sfml-audio)
endif()

# For installing targets (not mandatory)
install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)