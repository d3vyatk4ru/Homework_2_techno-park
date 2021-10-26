//
// Created by d3vyatk4 on 24.10.2021.
//

#include "file_interaction.h"
#include "stucture_t.h"
#include <stdlib.h>

// подсчет вхождения всех данных символов в последовательном режиме
int count_symbols(char const *symbols, char *region, long file_len) {

    int n_symbols = size(symbols);
    args_routine_t arg[n_symbols];

    for (size_t i = 0; i < n_symbols; ++i) {
        arg[i].symbol = symbols[i];
        arg[i].region = region;
        arg[i].file_len = file_len;
    }

    for (size_t i = 0; symbols[i] != '\0'; ++i) {
        int errflag = *(int *) count_once_symbol((void *) &arg[i]);

        if (errflag != 0) {
            return 1;
        }
    }

    print_count((args_routine_t *) &arg, n_symbols);

    return 0;
}
