cmake_minimum_required(VERSION 3.16)
project(AimTrainerDemo) 

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(aim_trainer_demo src/main.cpp)

target_link_libraries(aim_trainer_demo sfml-graphics sfml-window sfml-system)