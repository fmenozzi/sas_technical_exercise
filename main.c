#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "duplicates.h"

#define BUFSIZE 64

/*
 * TODO: Due to time constraints, I was unable to finish addressing the
 *       following aspects:
 *
 *  1) Error-handling: while I attempted to handle the more obvious errors
 *     that can arise, the current error-handling is by no means complete, as
 *     errno-based errors are not handled, as well as malloc failures.
 *
 *  2) Unit testing: I was originally hoping to get proper unit tests written,
 *     but instead I had time only for a rudimentary sanity-check test that works
 *     as follows:
 *
 *     a) Start with two files `testdata/valid.txt` and `testdata/invalid.txt`
 *        that are comprised of several lines each of valid and invalid ISO 8601
 *        date-time values, respectively
 *     b) Create the test input file `in.txt` that is the result of concatenating
 *        `valid.txt`, `invalid.txt`, and `valid.txt` again, allowing us to test
 *        both rejecting invalid lines and discarding duplicate ones
 *     c) Run the program with `in.txt` as input and record the results to a new
 *        file `out.txt`
 *     d) Ensure that `out.txt` is identical to `valid.txt` via the `diff` utility
 */

int main(int argc, char** argv) {
    char *infile, *outfile;
    FILE *fi, *fo;
    char linebuf[BUFSIZE];
    int rc, newlines;
    seen_set lines_seen;

    if (argc != 3) {
        fprintf(stderr, "usage: ./dates <input file> <output file>\n");
        return EXIT_FAILURE;
    }

    infile = argv[1];
    fi = fopen(infile, "r");
    if (!fi) {
        fprintf(stderr, "error opening input file %s\n", infile);
        return EXIT_FAILURE;
    }

    /*
     * Count the number of lines in input file in order to know how much space
     * to allocate to buffer for lines already seen.
     */
    newlines = 0;
    while (fgets(linebuf, BUFSIZE, fi) != NULL) {
        newlines++;
    }
    fseek(fi, 0, SEEK_SET);
    lines_seen = seen_set_init(newlines);

    outfile = argv[2];
    fo = fopen(outfile, "w");
    if (!fo) {
        fprintf(stderr, "error opening output file %s\n", outfile);
        fclose(fi);
        seen_set_free(&lines_seen);
        return EXIT_FAILURE;
    }

    while (fgets(linebuf, BUFSIZE, fi) != NULL) {
        if (!is_valid_iso8601_date(linebuf, strlen(linebuf))) {
            continue;
        }

        /* Check for duplicates. */
        if (seen_set_line_seen_before(&lines_seen, linebuf, BUFSIZE)) {
            continue;
        } else {
            seen_set_add_seen_line(&lines_seen, linebuf, BUFSIZE);
        }

        /* Write line to output file. */
        rc = fputs(linebuf, fo);
        if (rc < 0) {
            fprintf(stderr, "error writing to output file %s\n", outfile);
            fclose(fi);
            fclose(fo);
            seen_set_free(&lines_seen);
            return EXIT_FAILURE;
        }
    }

    if (!feof(fi)) {
        fprintf(stderr, "did not reach EOF for input file %s\n", infile);
        fclose(fi);
        fclose(fo);
        seen_set_free(&lines_seen);
        return EXIT_FAILURE;
    }

    fclose(fi);
    fclose(fo);
    seen_set_free(&lines_seen);
    return EXIT_SUCCESS;
}
