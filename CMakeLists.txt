cmake_minimum_required(VERSION 3.10)
project(CalculatorProject)

# Створюємо статичну бібліотеку
add_library(calculator_lib STATIC calculator.cpp)

# Створюємо виконуваний файл
add_executable(calculator_app main.cpp)

# Лінкуємо бібліотеку до програми
target_link_libraries(calculator_app calculator_lib)
