#include <gtest/gtest.h>
#include <cmath>
#include <ctime>
#include "array_search.h"

TEST(find_longest_sequence, find_longest_sequence) {
    int size;
    char *mat_exp = input_array_from_file("./test_data/test.txt", &size);
    char * result  = find_longest_sequence(mat_exp, size, 4);
    int flag = 1;
    for(int i = 0; i < 3; i++)
    {
        if (result[i] != '1')
        {
            flag = 0;
        }
    }
    free(result);
    EXPECT_EQ(flag, 1);
}

TEST(find_longest_sequence, no_array) {
    int size = 100;
    char *mat_exp = NULL;
    char * result  = find_longest_sequence(mat_exp, size, 4);
    int flag = 0;
    if (result == NULL)
    {
        flag = 1;
    }
    free(result);
    EXPECT_EQ(flag, 1);
}

TEST(find_longest_sequence, invalid_size) {
    int size;
    char *mat_exp = input_array_from_file("./test_data/test.txt", &size);
    char * result  = find_longest_sequence(mat_exp, -100, 4);
    int flag = 0;
    if (result == NULL)
    {
        flag = 1;
    }
    EXPECT_EQ(flag, 1);
}

TEST(find_longest_sequence, invalid_mlen) {
    int size;
    char *mat_exp = input_array_from_file("./test_data/test.txt", &size);
    char * result  = find_longest_sequence(mat_exp, size, -4);
    int flag = 0;
    if (result == NULL)
    {
        flag = 1;
    }
    free(result);
    EXPECT_EQ(flag, 1);
}

TEST(input_array_from_file, empty_file) {
    int size;
    int flag;
    flag = 0;
    char *mat_exp = input_array_from_file("./test_data/invalid_input_2.txt", &size);
    if (mat_exp == NULL)
    {
        flag = 1;
    }
    EXPECT_EQ(flag, 1);
}

TEST(input_array_from_file, file_with_no_chars) {
    int size;
    int flag;
    flag = 0;
    char *mat_exp = input_array_from_file("./test_data/invalid_input_1.txt", &size);
    if (mat_exp == NULL)
    {
        flag = 1;
    }
    EXPECT_EQ(flag, 1);
}

TEST(input_array_from_file, invalid_path) {
    int size;
    int flag;
    flag = 0;
    char *mat_exp = input_array_from_file("./test_data/invalid_input_1_23123.txt", &size);
    if (mat_exp == NULL)
    {
        flag = 1;
    }
    EXPECT_EQ(flag, 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
