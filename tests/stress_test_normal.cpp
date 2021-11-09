
#include <cmath>
#include <ctime>
#include <iostream>
#include <ostream>
#include <cstring>
#include "array_search.h"

int main(int argc, char **argv) {
    double timer = 0;
    int size;
    char *mat_exp = input_array_from_file("./test_data/stress_test.txt", &size);
    clock_t begin = clock();
    char * result  = find_longest_sequence(mat_exp, size, 4);
    clock_t end = clock();
    timer += (double) (end - begin) / CLOCKS_PER_SEC;
    std::cout << "time: " << timer << std::endl;
    free(result);
    return 0;
}