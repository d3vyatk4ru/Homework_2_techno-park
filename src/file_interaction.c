//
// Created by d3vyatk4 on 20.10.2021.
//

#include "stucture_t.h"
#include <fcntl.h>// импортируем int open(char* path, char mode)
#include <pthread.h>
#include <stdio.h>   // поток ввода/вывода
#include <stdlib.h>  // EXIT_SUCCESS
#include <sys/mman.h>// импортируем void* mmap(...)
#include <unistd.h>  // импортируем int close(inf fd)

int print_count(args_routine_t *arg, int size) {
    if (!arg) {
        return -1;
    }

    FILE *fd = fopen("../../results.txt", "w");

    if (!fd) {
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        fprintf(fd, "%u\n", arg[i].count);
    }

    if (fclose(fd) == -1) {
        printf("FILE WAS CLOSE WITH ERROR!!!\n");
        return -1;
    }

    return 0;
}

size_t size(char const *symbols) {

    if (!symbols) {
        return -1;
    }

    size_t len = 0;
    for (size_t i = 0; symbols[i] != '\0'; ++i) {
        len++;
    }
    return len;
}

// подсчет вхождения одного символа
void *count_once_symbol(void *args) {

    if (!args) {
        return NULL;
    }

    args_routine_t *arg = (args_routine_t *) args;
    unsigned int count = 0;

    for (int i = 0; i < arg->file_len; ++i) {
        if (arg->symbol == arg->region[i]) {
            count++;
        }
    }

    arg->count = count;

    return NULL;
}

// размер файла
long get_file_size(char const *path) {

    // открываем файл для записи
    FILE *fp = fopen(path, "r");

    if (!fp) {
        printf("ERROR! FILE WAS NOT OPEN!!!\n");
        return -1;
    }

    // премещаем внутренний указатель в конец файла.
    if (fseek(fp, 0, SEEK_END)) {
        printf("POSITION SETTING ERROR!!!\n");

        // разрываем связь с файлом
        if (fclose(fp) == EOF) {
            printf("FILE WAS CLOSE WITH ERROR!!!\n");
            return -1;
        }

        return -1;
    }

    // количество байт, занимаемое файлом
    long len = ftell(fp);

    if (len == -1L) {
        printf("ERROR PROCESSING FILE!!!\n");

        // разрываем связь с файлом
        if (fclose(fp) == EOF) {
            printf("FILE WAS CLOSE WITH ERROR!!!\n");
            return -1;
        }

        return -1;
    }

    // разрываем связь с файлом
    if (fclose(fp) == EOF) {
        printf("FILE WAS CLOSE WITH ERROR!!!\n");
        return -1;
    }

    return len;
}

// загрузка файла в виртуальную память
char *load_file_into_mem(char const *path, long file_len) {

    int fd = open(path, O_RDONLY);

    if (fd < 0) {
        printf("ERROR! FILE WAS NOT OPEN!!!\n");
        return NULL;
    }

    char *region = mmap(NULL,
                        file_len,
                        PROT_READ,
                        MAP_PRIVATE | MAP_POPULATE,
                        fd,
                        0);

    if (region == MAP_FAILED) {
        printf("ERROR! LOADING FILE INTO MEMORY IS NOT SUCSSESFULLY!!!\n");
        return NULL;
    }

    if (close(fd) == -1) {
        printf("FILE WAS CLOSE WITH ERROR!!!\n");
        return NULL;
    }

    return region;
}
