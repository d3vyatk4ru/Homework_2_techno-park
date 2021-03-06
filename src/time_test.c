//
// Created by d3vyatk4 on 24.10.2021.
//

#include "file_interaction.h"
#include <stdio.h>
#include <stdlib.h>// EXIT_SUCCESS
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define N_LAUNCH 5

double testing(const char *path, size_t n_launch) {

    struct timespec start, finish;
    double elapsed;

    int errflag = clock_gettime(CLOCK_MONOTONIC, &start);

    if (errflag != 0) {
        printf("ERROR IN CALCULATING TIME!");
        return -1;
    }

    for (size_t i = 0; i < n_launch; ++i) {

        // сооздаем процесс
        pid_t pid = fork();

        // если процесс дочерний - заходим
        if (pid == 0) {
            execl(path, " ", NULL);
            exit(0);
        } else {
            // ожидаем пока все дочерние процессы закончат работу
            while (wait(NULL) > 0)
                ;
        }
    }

    errflag = clock_gettime(CLOCK_MONOTONIC, &finish);

    if (errflag != 0) {
        return -1;
    }

    elapsed = (double) (finish.tv_sec - start.tv_sec) / n_launch;
    return elapsed;
}

int main() {

    double time_1 = testing("main_static", N_LAUNCH);
    if (time_1 == -1) {
        return 1;
    }

    double time_2 = testing("main_shared", N_LAUNCH);
    if (time_2 == -1) {
        return 1;
    }

    printf("Result for %s: %f sec\n", "main_static", time_1);
    printf("Result for %s: %f sec\n", "main_shared", time_2);

    return 0;
}
