#include "array_search_forked.h"
#include <string.h>


typedef struct {
    size_t mtype;
    char mtext[1100];
} message_buff;


void free_array(char *array, size_t size) {
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
            free(array);
            fclose(ptr);
            return NULL;
        }
    }
    *asize = size;

    fclose(ptr);
    return array;
}



int find_sequence
(char *array, size_t size, int n, size_t number_of_procs,
int q_id, size_t current_procs_numb) {
    int seq_start = 0;
    int pos_start = 0;
    int pos_end = 0;
    int max_pos_s = 0;
    int max_pos_e = 0;
    int len = 0;
    int max_len = 0;
    int sum = 0;
    size_t part_size = size / number_of_procs;
    size_t r_bor = 0;
    size_t j = current_procs_numb * part_size;
    size_t skip_let = 0;

    if (current_procs_numb != number_of_procs - 1) {
        r_bor = (current_procs_numb + 1) * part_size;
    } else {
        r_bor = size;
    }
    if (j != 0) {
        while (((array[j] - '0') > -1) && ((array[j] - '0') < 10)) {
            j++;
            skip_let++;
        }
        j++;
        skip_let++;
    }
    if (current_procs_numb == number_of_procs - 1) {
        skip_let = 0;
    }

    while (j < r_bor + skip_let) {
        if (((array[j] - '0') > -1) && ((array[j] - '0') < 10)) {
            if (seq_start == 0) {
                seq_start = 1;
                pos_start = j;
            }
            sum += array[j] - '0';
        } else {
            if (seq_start == 1) {
                seq_start = 0;
                pos_end = j - 1;
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
        j++;
    }
    char *current_sequence = (char *)
    calloc(max_pos_e - max_pos_s + 2, sizeof(char));
    for (int j = max_pos_s; j <= max_pos_e; j++) {
        current_sequence[j - max_pos_s] = array[j];
    }
    current_sequence[max_pos_e-max_pos_s + 1] ='\0';
    message_buff q_buff = {1, ""};
    snprintf(q_buff.mtext, strlen(current_sequence) + 1, "%s", current_sequence);

    if (msgsnd(q_id, (struct msgbuf *) &q_buff,
    strlen(q_buff.mtext) + 1, 0) == -1) {
        free(array);
        free(current_sequence);
        exit(1);
    }
    free(array);
    free(current_sequence);
    exit(1);
}

char *find_longest_sequence(char *array, int size, int mlen) {
    size_t number_of_procs = sysconf(_SC_NPROCESSORS_ONLN);
    int status = 0;
    key_t key = IPC_PRIVATE;
    int q_id = msgget(key, 0660 | IPC_CREAT);
    pid_t pids[number_of_procs];

    if (size < 0 || mlen < 0 || array == NULL) {
        free(array);
        return NULL;
    }

    for (size_t k = 0; k < number_of_procs; ++k) {
        pids[k] = fork();
        if (pids[k] == 0) {
            find_sequence(array, size, mlen, number_of_procs, q_id, k);
        }
    }
    for (size_t i = 0; i < number_of_procs; ++i) {
        if (waitpid(pids[i], &status, 0) != pids[i]) {
            return NULL;
        }
    }
    char *longest_sequence = (char *) malloc( size * sizeof(char));
    size_t max_len = 0;
    for (size_t i = 0; i < number_of_procs; ++i) {
        message_buff q_buff;
        if (msgrcv(q_id, (struct msgbuf *) &q_buff, size, 1, 0) == -1) {
            free(array);
            return NULL;
        }

        if (q_buff.mtext[0] == '\0') {
            return NULL;
        }

        if (max_len < strlen(q_buff.mtext)) {
            free(longest_sequence);
            longest_sequence = (char *) malloc(size * sizeof(char));

            if (longest_sequence == NULL) {
                free(array);
                return NULL;
            }
            snprintf(longest_sequence,
            strlen(q_buff.mtext) + 1, "%s", q_buff.mtext);
            max_len = strlen(q_buff.mtext);
        }
    }

    free_array(array, size);
    return longest_sequence;
}
