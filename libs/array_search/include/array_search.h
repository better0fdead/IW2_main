#ifndef LIBS_ARRAY_SEARCH_INCLUDE_ARRAY_SEARCH_H_
#define LIBS_ARRAY_SEARCH_INCLUDE_ARRAY_SEARCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/msg.h>

char *create_array(size_t size);
char *input_array_from_file(const char *file_path, int *asize);
char *find_longest_sequence(char *array, int size, int mlen);
#ifdef __cplusplus
}
#endif

#endif  // LIBS_ARRAY_SEARCH_INCLUDE_ARRAY_SEARCH_H_
