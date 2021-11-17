//
// Created by d3vyatk4 on 20.10.2021.
//

#include "file_interaction.h"

#define SYMBOLS "abcdefghijklmnopqrstuw"

int main() {

    const char filename[] = "../../test_file.txt";
    long len = get_file_size(filename);
    if (len == -1) {
        return 1;
    }

    char *region = load_file_into_mem(filename, len);
    if (!region) {
        return 1;
    }

    int status = count_symbols(SYMBOLS, region, len);
    if (status != 0) {
        return 1;
    }


    return 0;
}
