#ifndef DUPLICATES_H_
#define DUPLICATES_H_

/*
 * A data structure to keep track of the lines of input text that have already
 * been seen/processed, in order to know whether subsequent lines are duplicates
 * of previous ones. It does so using a dynamically-allocated buffer of strings,
 * each representing a line previously seen.
 *
 * TODO: Due to time constraints, this implementation is far from optimal. For
 * an input file with N lines of M characters each:
 *
 *  1) Using an array to search for previous lines is suboptimal both in time
 *     and space, taking O(N*M) time per lookup in the worst case and using
 *     O(N*M) space overall. A better solution would be to use a hash set, which
 *     would reduce the amortized insertion/retrieval cost to O(M) and the overall
 *     space usage to O(N).
 *
 *     Alternatively, one could first sort the input file lines lexicographically
 *     before processing, which would take O(N*M log N*M) time and O(N*M) extra
 *     space but would make finding duplicates trivial, as one would only need
 *     to check whether the current line is the same as the previous one. This
 *     solution would also require that the output line ordering does not matter.
 *
 *  2) Furthermore, in order to save time and keep the implementation simple, this
 *     structure is fixed in size, using the number of lines in the input file as
 *     the max size. This avoids needing to write code for handling reallocating
 *     the buffer, but also means that we need to scan the entire input file first
 *     in order to determine the number of lines and therefore the size of the
 *     buffer.
 */
typedef struct {
    char** buf;
    int count;
    int max_size;
} seen_set;

/* Initializes a set with room for `num_newlines` elements and returns it. */
seen_set seen_set_init(int num_newlines);

/*
 * Check whether the given `line` of size `bufsize` already exists in set `s`.
 *
 * If so, returns 1.
 * If not, returns 0.
 * If `s` is NULL, returns -1.
 */
int seen_set_line_seen_before(seen_set* s, const char* line, int bufsize);

/*
 * Adds the given `line` of size `bufsize` to set `s`.
 *
 * If the line was successfully added, returns 0.
 * If the line could not be added due to no more room, or if `s` is NULL,
 * returns -1.
 */
int seen_set_add_seen_line(seen_set* s, const char* line, int bufsize);

/* Frees all memory associated with set `s`. */
void seen_set_free(seen_set* s);

#endif
