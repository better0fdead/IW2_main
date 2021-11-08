#include <gtest/gtest.h>

TEST(comparator, comparator) {
    FILE *ptr = fopen("../matrix_data/test_cols_sum.txt", "r");
    FILE *ptr_f = fopen("../matrix_data/test_cols_sum_forked.txt", "r");

    double elem = 0;
    double elem_f = 0;

    for (size_t i = 0; i < 5000; ++i) {
        fscanf(ptr, "%lf", &elem);
        fscanf(ptr_f, "%lf", &elem_f);
        EXPECT_EQ(elem, elem_f);
    }
}

TEST(time, time) {
    FILE *ptr = fopen("../matrix_data/test_time.txt", "r");
    FILE *ptr_f = fopen("../matrix_data/test_time_forked.txt", "r");

    double time = 0;
    double time_f = 0;

    fscanf(ptr, "%lf", &time);
    fscanf(ptr_f, "%lf", &time_f);

    printf("Not forked: %lf\n", time);
    printf("Forked: %lf\n", time_f);
    printf("not forked / forked: %lf\n", time / time_f);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
