#include <gtest/gtest.h>
#include <cmath>
#include <ctime>

#include "array_search_forked.h"

TEST(print_matrix, print_matrix) {
    double timer = 0;
    size_t size;
    char *mat_exp = input_array_from_file("./tests/test.txt", &size);
    printf("%d\n",size);
    clock_t begin = clock();
    char * result  = find_longest_sequence(mat_exp, size, 4);
    clock_t end = clock();
    timer += (double) (end - begin) / CLOCKS_PER_SEC;
    std::cout << "average time: " << timer << std::endl;
    int flag = 0;
    printf("\n{%s}\n", result);
    //char *result_c = "111";
    if (strcmp(result, "111"))
    {
        flag = 1;
    }
    free(result);
    EXPECT_EQ(flag, 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
