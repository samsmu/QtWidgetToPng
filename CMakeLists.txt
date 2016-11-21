cmake_minimum_required(VERSION 2.6)
project(QtWidgetToPng)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_WIN32_EXECUTABLE ON)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

set(QtWidgetToPng_SRCS QtWidgetToPng.cpp main.cpp QArrowTabBar.cpp)

add_executable(QtWidgetToPng ${QtWidgetToPng_SRCS})

target_link_libraries(QtWidgetToPng ${Qt5Core_LIBRARIES} ${Qt5Core_QTMAIN_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES})

install(TARGETS QtWidgetToPng RUNTIME DESTINATION bin)
