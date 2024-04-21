cmake_minimum_required(VERSION 3.22.1)
project(Matrix_rkpp)

# Установим стандарт C++ на C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Укажем директорию с заголовочными файлами
include_directories(include)

# Получим список всех исходных файлов
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Создадим исполняемый файл из всех найденных исходных файлов
add_executable(Matrix_rkpp main.cpp ${SOURCES})