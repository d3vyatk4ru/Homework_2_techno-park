# минимальная версия для запуска
cmake_minimum_required(VERSION 3.16)

# имя проекта
project(Homework_2_techno-park)

# стандарт языка
set(CMAKE_CXX_STANDARD 14)

add_compile_options(-g -O0 -Wextra -Wall -Wextra -Wpedantic -lgcov --coverage)
add_link_options( -O0 -lgcov --coverage)

# добавляем пакет с потокам
find_package (Threads REQUIRED)
add_compile_options(-pthread)

# добавляем поиск файло в директории include
include_directories("../include")

# библиотека с общими функциями
set(COMMON_LIB_SOURCE file_interaction.c)

# библиотека с реализацией последовательной обработки поданных символов
set(STAT_LIB_SOURCE_SEQ ${COMMON_LIB_SOURCE} count_symbols_sequence.c)

# библиотека с реализацией многопоточной обработки поданных символов
set(SHAR_LIB_SOURCE_THR ${COMMON_LIB_SOURCE} count_symbols_thread.c)

# создание статической библиотеки
add_library(cosym_static STATIC ${STAT_LIB_SOURCE_SEQ})

# создание динамической библиотеки
add_library(cosym_shared SHARED ${SHAR_LIB_SOURCE_THR})

# создание бинарных файлов
add_executable(main_static main.c ${LIB_SOURCES_HEADER})
add_executable(main_shared main.c ${LIB_SOURCES_HEADER})

# соединение библиотеки и основного бинарного файла
target_link_libraries(main_static cosym_static)
target_link_libraries(main_shared cosym_shared pthread)

# бинарный файл для тестирования времени работы
add_executable(main_time_test time_test.c)
