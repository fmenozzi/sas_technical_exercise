#include "parser.h"

#include <ctype.h>
#include <stdlib.h>

int is_invalid_parser_state(parser* p) {
    return !p || !p->line || p->idx >= p->len;
}

int current(parser* p) {
    if (is_invalid_parser_state(p)) {
        return -1;
    }

    return p->line[p->idx];
}

int accept_char(char c, parser* p) {
    if (is_invalid_parser_state(p)) {
        return 0;
    }

    if (current(p) == c) {
        p->idx++;
        return 1;
    }

    return 0;
}

int accept_current(parser* p) {
    return accept_char(current(p), p);
}

int accept_digit(parser* p) {
    char digitstr[2] = {'\0'};

    if (is_invalid_parser_state(p) || !isdigit(current(p))) {
        return -1;
    }

    digitstr[0] = current(p);
    accept_current(p);
    return atoi(digitstr);
}

int accept_two_digit_num_in_range(int lo, int hi, parser* p) {
    int tens, ones, value;

    if (is_invalid_parser_state(p)) {
        return 0;
    }

    if ((tens = accept_digit(p)) == -1) return 0;
    if ((ones = accept_digit(p)) == -1) return 0;

    value = 10*tens + ones;
    if (value < lo || value > hi) {
        return 0;
    }

    return 1;
}

int accept_year(parser* p) {
    if (accept_digit(p) == -1) return 0;
    if (accept_digit(p) == -1) return 0;
    if (accept_digit(p) == -1) return 0;
    if (accept_digit(p) == -1) return 0;

    return 1;
}

int accept_month(parser* p) {
    return accept_two_digit_num_in_range(1, 12, p);
}

int accept_day(parser* p) {
    return accept_two_digit_num_in_range(1, 31, p);
}

int accept_hour(parser* p) {
    return accept_two_digit_num_in_range(0, 23, p);
}

int accept_minute(parser* p) {
    return accept_two_digit_num_in_range(0, 59, p);
}

int accept_second(parser* p) {
    return accept_two_digit_num_in_range(0, 59, p);
}

int accept_tzd(parser* p) {
    if (is_invalid_parser_state(p)) {
        return 0;
    }

    if (current(p) == 'Z') {
        accept_current(p);
        return 1;
    } else if (current(p) == '+' || current(p) == '-') {
        if (accept_current(p) == 0)     return 0;
        if (accept_hour(p) == 0)        return 0;
        if (accept_char(':', p) == 0)   return 0;
        if (accept_minute(p) == 0)      return 0;

        return 1;
    }

    return 0;
}

int is_valid_iso8601_date(const char* line, int len) {
    parser p;

    p.line = line;
    p.len = len;
    p.idx = 0;

    if (!accept_year(&p))         return 0;
    if (!accept_char('-', &p))    return 0;
    if (!accept_month(&p))        return 0;
    if (!accept_char('-', &p))    return 0;
    if (!accept_day(&p))          return 0;
    if (!accept_char('T', &p))    return 0;
    if (!accept_hour(&p))         return 0;
    if (!accept_char(':', &p))    return 0;
    if (!accept_minute(&p))       return 0;
    if (!accept_char(':', &p))    return 0;
    if (!accept_second(&p))       return 0;
    if (!accept_tzd(&p))          return 0;

    /* fgets() might add a newline. */
    if (current(&p) == '\n') {
        accept_current(&p);
    }

    /* Additional text past this point considered invalid. */
    if (p.idx < p.len) {
        return 0;
    }

    return 1;
}
