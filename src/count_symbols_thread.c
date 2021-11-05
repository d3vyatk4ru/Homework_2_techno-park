//
// Created by d3vyatk4 on 24.10.2021.
//

#include "file_interaction.h"
#include "stucture_t.h"
#include <pthread.h>
#include <stdio.h> // поток ввода/вывода
#include <stdlib.h>// EXIT_SUCCESS

// подсчет количества символов в многопоточном режиме
int count_symbols(char const *symbols, char *region, long file_len) {

    if (!region) {
        return 1;
    }

    // кол-во потоков = кол-во символов, которые необходимо найти
    size_t n_threads = size(symbols);
    // массив идентификаторов потока
    pthread_t thread[n_threads];

    // флаг ошибки
    int errflag;
    args_routine_t arg[n_threads];

    for (size_t i = 0; i < n_threads; ++i) {
        arg[i].symbol = symbols[i];
        arg[i].region = region;
        arg[i].file_len = file_len;
    }

    for (size_t i = 0; i < n_threads; ++i) {
        errflag = pthread_create(&thread[i], NULL, count_once_symbol, (void *) &arg[i]);

        // если не удлось создать и выполнить поток - выход
        if (errflag != EXIT_SUCCESS) {
            printf("Can't create thread, status = %d\n", errflag);
            return -1;
        }
    }

    // ожидание завершения всех потоков
    for (size_t i = 0; i < n_threads; ++i) {
        errflag = pthread_join(thread[i], NULL);
        if (errflag != EXIT_SUCCESS) {
            printf("Сan't join thread, status = %d\n", errflag);
            return -1;
        }
    }

    // печать результата
    errflag = print_count((args_routine_t *) &arg, n_threads);

    if (errflag == 1) {
        return errflag;
    }

    return 0;
}
