#include <gtest/gtest.h>
#include <cmath>
#include <ctime>
#include "array_search.h"

TEST(print_matrix, print_matrix) {
    double timer = 0;
    size_t size;
    char *mat_exp = input_array_from_file("./tests/test.txt", &size);
    char *longest;
    clock_t begin = clock();
    longest = find_longest_sequence(mat_exp, size, 4);
    clock_t end = clock();
    free(longest);
    timer += (double) (end - begin) / CLOCKS_PER_SEC;
    std::cout << "average time: " << timer << std::endl;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
