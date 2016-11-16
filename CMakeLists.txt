cmake_minimum_required(VERSION 2.6)
project(themes_generator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

set(themes_generator_SRCS themes_generator.cpp main.cpp QArrowTabBar.cpp)

add_executable(themes_generator ${themes_generator_SRCS})

target_link_libraries(themes_generator ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES})

install(TARGETS themes_generator RUNTIME DESTINATION bin)
