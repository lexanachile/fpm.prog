cmake_minimum_required(VERSION 3.16)
set(CMAKE_PREFIX_PATH "C:/Prog/QT/6.8.3/mingw_64/lib/cmake")
project(QTDijkstra LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(QTDijkstra
  main.cpp
  dijkstra.h dijkstra.cpp
)
target_link_libraries(QTDijkstra Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS QTDijkstra
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
