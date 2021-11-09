//
// Created by d3vyatk4 on 25.10.2021.
//
#include "gtest/gtest.h"

extern "C" {
#include "file_interaction.h"
}

#include <stdio.h>// поток ввода/вывода

#define TEST_FILE "/home/runner/work/Homework_2_techno-park/Homework_2_techno-park/test_file.txt"
#define NON_EXIST_FILE "filename.txt"
#define TRUE_LEN 1000
#define SYMBOLS "abcdefghij"

// файл найден, размер корректный
TEST(FILE_LEN, successful_len) {

    long len = get_file_size(TEST_FILE);
    EXPECT_EQ(len, TRUE_LEN);
}

// проверка работы, если файла нет
TEST(FILE_LEN, non_exist_file) {

    long len = get_file_size(NON_EXIST_FILE);
    EXPECT_EQ(len, -1);
}

// проверка работы, если нулевой указатель
TEST(FILE_LEN, nullptr_file) {

    long len = get_file_size(nullptr);
    EXPECT_EQ(len, -1);
}

TEST(FILE_LEN, din_file_size) {
    FILE *file;

    size_t sizes[] = {0, (int) 1e+1, (int) 1e+2, (int) 1e+4, (int) 1e+8};
    for (size_t i = 0; i < 5; ++i) {
        file = fopen("testfile.txt", "w");
        rewind(file);
        for (size_t j = 0; j < sizes[i]; ++j) {
            fprintf(file, "%c", 'a');
        }

        fclose(file);
        ASSERT_EQ(sizes[i], get_file_size("testfile.txt"));
    }
}

// нулевой указатель данных
TEST(DISPLAY_COUNT, print_count_null_args) {

    int status = print_count(nullptr, 0);
    EXPECT_EQ(status, -1);
}

TEST(DISPLAY_COUNT, successful_print) {

    args_routine_t arg[2];

    for (size_t i = 0; i < 2; ++i) {
        arg[i].count = i + 1;
    }

    int status = print_count(arg, 0);
    EXPECT_EQ(status, 0);
}

TEST(COUNT_ONCE_SYMBOL, nullptr_input) {

    int *status = (int *) count_once_symbol(nullptr);
    EXPECT_TRUE(status != nullptr);
}

TEST(SIZE, nullptr_input) {

    int status = print_count(nullptr, 0);
    EXPECT_EQ(status, -1);
}

// корректная загрузка файла в виртуальную память
TEST(MMAP_TEST, successful_read_into_mem) {

    char *region = load_file_into_mem(TEST_FILE, TRUE_LEN);
    EXPECT_TRUE(region != nullptr);
}

// некорректная загрузка файла в виртуальную память из-за ошибочной длины
TEST(MMAP_TEST, non_successful_read_into_mem) {

    char *region = load_file_into_mem(NON_EXIST_FILE, TRUE_LEN);
    EXPECT_TRUE(region == nullptr);
}

// нулевой указательь най файл
TEST(MMAP_TEST, nullptr_file) {

    char *region = load_file_into_mem(nullptr, TRUE_LEN);
    EXPECT_TRUE(region == nullptr);
}

// отрицательный размер файла
TEST(MMAP_TEST, non_successful_len) {

    char *region = load_file_into_mem(TEST_FILE, -1);
    EXPECT_TRUE(region == nullptr);
}

// нулевой указатель на файл в виртуальной памяти
TEST(CALC_COUNT_SYM, nullptr_problem_region) {

    int status = count_symbols(SYMBOLS, nullptr, TRUE_LEN);
    EXPECT_EQ(status, 1);
}

TEST(CALC_COUNT_SYM, nullptr_problem_symbols) {

    char *region = load_file_into_mem(TEST_FILE, TRUE_LEN);

    int status = count_symbols(nullptr, region, TRUE_LEN);
    EXPECT_EQ(status, 1);
}

TEST(CALC_COUNT_SYM, null_len_problem) {

    char *region = load_file_into_mem(TEST_FILE, TRUE_LEN);

    int status = count_symbols(SYMBOLS, region, -1);
    EXPECT_EQ(status, 1);
}

TEST(FULL_TEST, correct_working) {

    const char filename[] = TEST_FILE;
    long len = get_file_size(filename);

    char *region = load_file_into_mem(filename, len);

    int status = count_symbols(SYMBOLS, region, len);

    status = clear_mem(region, len);

    EXPECT_EQ(status, 0);
}

// тесты на корректность работы программы
TEST(COUNT_SYMBOL, correct_count_symbol) {
    char symbols[1024] = {0};
    for (int i = 0; i < 1024; i += 2) {
        symbols[i] = 'b';
    }
    ASSERT_EQ(512, count_symbols('b', symbols, 1024));
}

int main(int argc, char *argv[]) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
