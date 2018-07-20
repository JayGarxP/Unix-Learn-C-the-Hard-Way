/*****************************************************************************
 * @file prettyprint.h
 *
 * @date 05/30/18
 * @author JP Joseph Fallon
 *
 * Unix Spring 2018 OIT
 *
 * @detail Make Your Output Pretty with ANSI escape codes!
 *
 *****************************************************************************/
#define AC_RED   "\x1b[31m"
#define AC_GRN   "\x1b[32m"
#define AC_YLW   "\x1b[33m"
#define AC_BLU   "\x1b[34m"
#define AC_PRP   "\x1b[35m"
#define AC_CYN   "\x1b[36m"
#define AC_RESET "\x1b[0m"

//SED on `diff -u` output to simulate `colordiff` or --color=auto
#define DIFF_SEDa "sed \"s/^-/`echo -e \\\"\x1b\\\"`[41m-/;s/^+/`echo -e \\\"\\x1b\\\"    `[42m+/;s/^@/`echo -e \\\"\\x1b\\\"`[34m@/;s/$/`echo -e \\\"\\x1b\\\"`[0m/\""

/*
https://stackoverflow.com/a/16865578/3663273
*/
#define DIFF_SEDb "sed 's/^-/\x1b[41m-/;s/^+/\x1b[42m+/;s/^@/\x1b[34m@/;s/$/\x1b[0m/'"
