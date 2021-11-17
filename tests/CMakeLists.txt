cmake_minimum_required(VERSION 3.16)
project(tests)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-g -O0 -Wextra -Wall -Wextra -Wpedantic -lgcov --coverage)
add_link_options( -O0 -lgcov --coverage)

include_directories("../include")
include_directories("../src")

# Включаем тестирование
enable_testing()

# Загружаем библиотеки ОБЯЗАТЕЛЬНО
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

# Создаем исполняемый файл для статической библиотеки и последовательной реализации
add_executable(test_static test.cpp)
# Исполняемый файл для динамической библиотеки и многопоточной реализации
add_executable(test_shared test.cpp)

# Линкуем (соединяем) программу со статической библиотекой
target_link_libraries(test_static ${GTEST_LIBRARIES} cosym_static pthread)
# Линкуем (соединяем) программу с библиотекой
target_link_libraries(test_shared ${GTEST_LIBRARIES} cosym_shared pthread)
