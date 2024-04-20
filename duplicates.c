#include "duplicates.h"

#include <stdlib.h>
#include <string.h>

seen_set seen_set_init(int num_newlines) {
    seen_set s;
    s.count = 0;
    s.max_size = num_newlines;
    s.buf = malloc(num_newlines * sizeof(char*));
    return s;
}

int seen_set_line_seen_before(seen_set* s, const char* line, int bufsize) {
    int i;
    if (!s) {
        return -1;
    }
    for (i = 0; i < s->count; i++) {
        if (strncmp(s->buf[i], line, bufsize) == 0) {
            return 1;
        }
    }
    return 0;
}

int seen_set_add_seen_line(seen_set* s, const char* line, int bufsize) {
    if (!s || s->count >= s->max_size) {
        return -1;
    }
    s->buf[s->count] = malloc(bufsize * sizeof(char));
    strncpy(s->buf[s->count], line, bufsize);
    s->count++;
    return 0;
}

void seen_set_free(seen_set* s) {
    int i;
    if (!s) {
        return;
    }
    for (i = 0; i < s->count; i++) {
        free(s->buf[i]);
    }
    free(s->buf);
}
