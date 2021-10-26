//
// Created by d3vyatk4 on 25.10.2021.
//

#include "gtest/gtest.h"
extern "C" {
#include "file_interaction.h"
}

#define TEST_FILE "./tests/test_file.txt"

TEST(EQ_LEN, len_100) {

    long len = get_file_size(TEST_FILE);

    EXPECT_EQ(len, 1000);
}

int main(int argc, char* argv[]) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}