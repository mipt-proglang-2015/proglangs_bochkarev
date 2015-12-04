cmake_minimum_required(VERSION 2.8.11)

project(Excel)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

file(GLOB SOURCES
	"*.h"
	"*.cpp"
)

set(SOURCE_FILES main.cpp)

# Tell CMake to create the helloworld executable
add_executable(excel ${SOURCES})

# Use the Widgets module from Qt 5.
target_link_libraries(excel Qt5::Widgets)
