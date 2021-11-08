
#include <cmath>
#include <ctime>
#include <iostream>
#include <ostream>
#include <cstring>
#include "array_search_forked.h"

int main(int argc, char **argv) {
    double timer = 0;
    size_t size;
    clock_t begin = clock();
    char *mat_exp = input_array_from_file("./matrix_data/matrix_3_2.txt", &size);
    printf("%d\n",size);
    
    char * result  = find_longest_sequence(mat_exp, "./matrix_data/test_mat.txt", size, 4);
    clock_t end = clock();
    timer += (double) (end - begin) / CLOCKS_PER_SEC;
    std::cout << "average time: " << timer << std::endl;
    int flag = 0;
    printf("%s\n", result);
    if (strcmp(result, "111"))
    {
        flag = 1;
    }
    printf("%d\n", flag);
    free(result);
    return 0;
}