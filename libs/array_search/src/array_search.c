#include "array_search.h"
#include <string.h>

void free_array(char *array) {
    free(array);
}

char *create_array(size_t size) {
    char *array = (char *)malloc(sizeof(char) * size);
    return array;
}

char *input_array_from_file(const char *file_path, int *asize) {
    if (file_path == NULL) {
        return NULL;
    }
    FILE *ptr = fopen(file_path, "r");
    if (ptr == NULL) {
        return NULL;
    }
    size_t size;
    if (fscanf(ptr, "%zu", &size) != 1) {
        fclose(ptr);
        return NULL;
    }
    char *array = create_array(size);
    for (size_t i = 0; i < size; i++) {
        if (fscanf(ptr, "%c", &array[i]) != 1) {
            fclose(ptr);
            free(array);
            return NULL;
        }
    }
    *asize = size;

    fclose(ptr);
    return array;
}

char *find_sequence(char *array, int size, int n) {
    int seq_start = 0;
    int pos_start = 0;
    int pos_end = 0;
    int max_pos_s = 0;
    int max_pos_e = 0;
    int len = 0;
    int max_len = 0;
    int sum = 0;

    for (int i = 0; i < size; i++) {
        if (((array[i] - '0') > -1) && ((array[i] - '0') < 10)) {
            if (seq_start == 0) {
                seq_start = 1;
                pos_start = i;
            }
            sum += array[i] - '0';
        } else {
            if (seq_start == 1) {
                seq_start = 0;
                pos_end = i - 1;
                len = pos_end - pos_start;
                if (len > max_len && sum <= n) {
                    max_len = len;
                    max_pos_s = pos_start;
                    max_pos_e = pos_end;
                }
                len = 0;
                sum = 0;
            }
        }
    }
    char *current_word = (char *)
    calloc(max_pos_e - max_pos_s + 2, sizeof(char));
    for (int j = max_pos_s; j <= max_pos_e; j++) {
        current_word[j - max_pos_s] = array[j];
    }
    current_word[max_pos_e-max_pos_s + 1] ='\0';
    return current_word;
}

char *find_longest_sequence(char *array, int size, int mlen) {
    if (array == NULL) {
        return NULL;
    }
    if (mlen < 0 || size < 0) {
        free_array(array);
        return NULL;
    }
    char * longest_string = find_sequence(array, size, mlen);
    free_array(array);
    return longest_string;
}
