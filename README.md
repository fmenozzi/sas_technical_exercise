# SAS Technical Exercise: Career Software Developer - C

This repository contains a small C89 project submission for the following technical exercise:

## Technical Exercise

Implement a program that reads a large list of date-time values from a file and writes to a separate file the list of unique, valid date-time values (no duplicates). A valid date-time value matches the following format (ISO 8601):
YYYY-MM-DDThh:mm:ssTZD

Where:
* YYYY = four-digit year
* MM = two-digit month (01 through 12)
* DD = two-digit day of month (01 through 31)
* hh = two digits of hour (00 through 23)
* mm = two digits of minute (00 through 59)
* ss = two digits of second (00 through 59)
* TZD = time zone designator (“Z” for GMT or +hh:mm or -hh:mm)

It is not necessary to perform semantic validation of the date-time value. In other words, the date-time value "9999-02-31T12:34:56+12:34" should be considered valid by your program even though February 31, 9999 is not a legitimate date.
Guidelines and Requirements:
* The program can be implemented in either C, C++, or Rust (preferably in C).
* The validation logic may not use high-level library functions that perform format validation or regular expression parsing. However, low-level library functions may be used. For example, in C, functions defined in the standard library headers stdlib.h, ctype.h, string.h, stdio.h, etc. may be used.
* Use the development environment (IDE, OS platform) of your choice.
* Use your own coding standards and style. We have no expectations beyond code being easy to read, although consistency of style will be noted.
* If you want to make improvements or extend your code but do not have time, leave a comment in your code with the label “TODO: ” along with a description of what you would have done given time, and why.

## Build and Run

Use `make` to build the project, `make test` to run the rudimentary test, and `make clean` to remove artifacts.
