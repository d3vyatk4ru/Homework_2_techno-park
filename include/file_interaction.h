//
// Created by d3vyatk4 on 24.10.2021.
//

#ifndef HOMEWORK_2_TECHNO_PARK_FILE_INTERACTION_H
#define HOMEWORK_2_TECHNO_PARK_FILE_INTERACTION_H

#include "stucture_t.h"

long get_file_size(char const *path);

char *load_file_into_mem(char const *path, long file_len);

int count_symbols(char const *symbols, char *region, long file_len);

int print_count(args_routine_t *arg, int size);

int size(char const *symbols);

void *count_once_symbol(void *args);

#endif//HOMEWORK_2_TECHNO_PARK_FILE_INTERACTION_H
