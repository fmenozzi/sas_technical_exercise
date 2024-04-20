#ifndef PARSER_H_
#define PARSER_H_

/*
 * Structure that holds the current `line` of size `len` to be parsed, as well
 * as the index `idx` of the current character being parsed.
 */
typedef struct {
    const char* line;
    int len;
    int idx;
} parser;

/*
 * Checks whether the current state of the parser is invalid, such as when any
 * pointers are NULL or if the parser's `idx` has gone out of bounds.
 *
 * Returns 1 if parser state is invalid, 0 otherwise.
 */
int is_invalid_parser_state(parser* p);

/*
 * Returns the current character being parsed, or -1 if parser state is invalid.
 */
int current(parser* p);

/*
 * Consumes the current character being parsed if it matches `c`.
 *
 * If the current character being parsed does not match `c`, or if the parser
 * state is invalid, returns 0.
 * Otherwise, advances to the next character and returns 1.
 */
int accept_char(char c, parser* p);

/*
 * Unconditionally consumes the current character being parsed.
 *
 * Returns 0 if the parser state is invalid, 1 otherwise.
 */
int accept_current(parser* p);

/*
 * Checks whether the parser's current character is a valid digit from [0-9].
 *
 * If so, it accepts the character and returns the parsed integer digit.
 * If not, or if the parser state is invalid, returns -1.
 */
int accept_digit(parser* p);

/*
 * Checks whether the next two characters are digits whose represented value is
 * in the range [lo,hi].
 *
 * If so, accepts both characters and returns 1.
 * If not, or if the parser state is invalid, returns 0.
 */
int accept_two_digit_num_in_range(int lo, int hi, parser* p);

/*
 * Attempts to parse a YYYY (four-digit) year value at the parser's current
 * position.
 *
 * If parse succeeds, returns 1.
 * If parse does not succeed or the parser state is invalid, returns 0.
 */
int accept_year(parser* p);

/*
 * Attempts to parse a MM (two-digit) month value at the parser's current
 * position. Month values must be in the range [01,12].
 *
 * If parse succeeds, returns 1.
 * If parse does not succeed or the parser state is invalid, returns 0.
 */
int accept_month(parser* p);

/*
 * Attempts to parse a DD (two-digit) day value at the parser's current
 * position. Day values must be in the range [01,31]
 *
 * If parse succeeds, returns 1.
 * If parse does not succeed or the parser state is invalid, returns 0.
 */
int accept_day(parser* p);

/*
 * Attempts to parse a hh (two-digit) hour value at the parser's current
 * position. Hour values must be in the range [00,23].
 *
 * If parse succeeds, returns 1.
 * If parse does not succeed or the parser state is invalid, returns 0.
 */
int accept_hour(parser* p);

/*
 * Attempts to parse a mm (two-digit) minute value at the parser's current
 * position. Minute values must be in the range [00,59].
 *
 * If parse succeeds, returns 1.
 * If parse does not succeed or the parser state is invalid, returns 0.
 */
int accept_minute(parser* p);

/*
 * Attempts to parse a ss (two-digit) second value at the parser's current
 * position. Second values must be in the range [00,59].
 *
 * If parse succeeds, returns 1.
 * If parse does not succeed or the parser state is invalid, returns 0.
 */
int accept_second(parser* p);

/*
 * Attempts to parse a time zone designator (TZD) value. TZDs can take one of
 * three forms:
 *
 * 1) Z
 * 2) +hh:mm
 * 3) -hh:mm
 *
 * where hh and mm are hours and minutes. Hours must be in the range [00,23] and
 * minutes must be in the range [00,59].
 *
 * If parse succeeds, returns 1.
 * If parse does not succeed or the parser state is invalid, returns 0.
 */
int accept_tzd(parser* p);

/*
 * Attempts to parse the given `line` of size `len` to determine whether it
 * conforms to the ISO 8601 date-time specification, using a simplified
 * recursive descent-style parser.
 * Returns 1 if `line` is a valid ISO 8601 date-time value, 0 otherwise.
 */
int is_valid_iso8601_date(const char* line, int len);

#endif
