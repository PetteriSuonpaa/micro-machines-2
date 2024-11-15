cmake_minimum_required(VERSION 3.0)
project(Niban)

set(CMAKE_CXX_STANDARD 17)

# Define SFML root directory
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/libs/SFML")
set(BOX2D_ROOT "${CMAKE_SOURCE_DIR}/libs/box2d")

# Include SFML headers
include_directories("${SFML_ROOT}/include")
include_directories("${BOX2D_ROOT}/include")

# Link SFML libraries
link_directories("${SFML_ROOT}/lib")
link_directories("${BOX2D_ROOT}/build/src")

# Specify the executable and link SFML and X11 libraries
add_executable(Niban src/main.cpp)

target_link_libraries(Niban
    sfml-graphics sfml-window sfml-system sfml-audio
    "${BOX2D_ROOT}/build/src/libbox2d.a"  # Ensure this path is correct for your build
    X11 Xrandr Xinerama Xcursor Xi
)