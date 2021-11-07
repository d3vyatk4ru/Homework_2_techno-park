//
// Created by d3vyatk4 on 24.10.2021.
//

#include "file_interaction.h"
#include "stucture_t.h"
#include <stdlib.h>

// подсчет вхождения всех данных символов в последовательном режиме
int count_symbols(char const *symbols, char *region, long file_len) {

    if (file_len < 0) {
        return -1;
    }

    if (!symbols) {
        return 0;
    }

    if (!region) {
        return 1;
    }

    int n_symbols = size(symbols);
    if (n_symbols < 0) {
        return 1;
    }

    args_routine_t arg[n_symbols];

    for (int i = 0; i < n_symbols; ++i) {
        arg[i].symbol = symbols[i];
        arg[i].region = region;
        arg[i].file_len = file_len;
    }

    for (int i = 0; symbols[i] != '\0'; ++i) {
        int errflag = *(int *) count_once_symbol((void *) &arg[i]);

        if (errflag != 0) {
            return errflag;
        }
    }

    int errflag = print_count((args_routine_t *) &arg, n_symbols);

    if (errflag == 1) {
        return errflag;
    }

    return 0;
}
