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

// // тесты на логику работы программы
// TEST(CALC_COUNT_SYM, correct_count) {

//     long len = get_file_size(TEST_FILE);
//     char *region = load_file_into_mem(TEST_FILE, len);
//     int status = count_symbols(SYMBOLS, region, len);

//     EXPECT_EQ(status, 0);

//     FILE *fd = fopen("../../results.txt", "r");

//     unsigned int clc[10] = {};
//     unsigned int correct_ans[10] = {37, 35, 44, 39, 50, 48, 37, 40, 41, 41};

//     for (size_t i = 0; i < 10; ++i) {
//         fscanf(fd, "%u", &clc[i]);
//     }
//     fclose(fd);

//     for (size_t i = 0; i < 10; ++i) {
//         EXPECT_EQ(clc[i], correct_ans[i]);
//     }
// }

int main(int argc, char *argv[]) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
