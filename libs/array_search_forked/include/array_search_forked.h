#ifndef IW_2_LIBS_STATIC_INCLUDE_ARRAY_SEARCH_FORKED_H_
#define IW_2_LIBS_STATIC_INCLUDE_ARRAY_SEARCH_FORKED_H_

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
char *input_array_from_file(const char *path, size_t *asize);
char *find_longest_sequence(char *array, size_t size, size_t mlen);
#ifdef __cplusplus
}
#endif

#endif // IW_2_LIBS_STATIC_INCLUDE_ARRAY_SEARCH_FORKED_H_
