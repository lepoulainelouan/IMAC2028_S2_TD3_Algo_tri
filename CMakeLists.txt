cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(TD03_S2)

# On indique que l'on veut créer un exécutable "ex01" compilé à partir du fichier td1.cpp
add_executable(td_1_exo1 src/td_1_exo1.cpp)
add_executable(td_1_exo2 src/td_1_exo2.cpp)
add_executable(td_1_exo3 src/td_1_exo3.cpp)
add_executable(td_1_exo4 src/td_1_exo4.cpp)
add_executable(td_5_exo1 src/td_5_exo1.cpp)
add_executable(td_5_exo2 src/td_5_exo2.cpp)
add_executable(td_5_exo3 src/td_5_exo3.cpp)
add_executable(td_5_bonus src/td_5_bonus.cpp)