project( supermario )

# CMake 3.* necessario per Qt
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)

# ottengo tutti i sorgenti
file(GLOB my_sources *.h *.cpp *.qrc)

# attiva il Resource Compiler (RCC)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

# aggiungo eseguibile
add_executable(supermario ${my_sources})

# verifico l'esistenza delle librerie Qt necessarie
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

# collego le librerie Qt con l'eseguibile
target_link_libraries(supermario Qt5::Widgets Qt5::Multimedia)