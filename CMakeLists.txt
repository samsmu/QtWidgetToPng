cmake_minimum_required(VERSION 2.6)
project(QtWidgetToPng)

include(cmake/PVS-Studio.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_WIN32_EXECUTABLE ON)


SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

set(QtWidgetToPng_SRCS QtWidgetToPng.cpp main.cpp QArrowTabBar.cpp)

add_executable(QtWidgetToPng ${QtWidgetToPng_SRCS})

target_link_libraries(QtWidgetToPng ${Qt5Core_LIBRARIES} ${Qt5Core_QTMAIN_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES})

pvs_studio_add_target(TARGET analyze ALL
                      OUTPUT FORMAT errorfile
                      ANALYZE QtWidgetToPng
                      LOG target.plog)

install(TARGETS QtWidgetToPng RUNTIME DESTINATION bin)
