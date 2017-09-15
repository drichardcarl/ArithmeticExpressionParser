#ifndef __TOKENS_H__
#define __TOKENS_H__

#define NK 2 // # of defined acceptable keywords
#define NS 17 // # of defined acceptable symbols

// acceptable keywords
char KEYWORD[][30] = {
    "exit",
    "aparse"
};

// acceptable symbols
char SYMBOL[] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '+',
    '-',
    '*',
    '/',
    '(',
    ')',
    '\"'
};

#endif // __TOKENS_H__

