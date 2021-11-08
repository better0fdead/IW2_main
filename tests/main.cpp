
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
    char *mat_exp = input_array_from_file("./test_data/test.txt", &size);
    printf("%ld\n",size);
    
    char * result  = find_longest_sequence(mat_exp, size, 4);
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