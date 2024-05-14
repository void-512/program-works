#ifndef __SYMLIB__
#define __SYMLIB__

#define INVALID_SYMBOL -1

#define CAP 50

#define SYMCAP 20

// read_symbol(): read a string and returns the corresponding cmd
const int read_symbol();

// lookup_symbol(s): register s in the list of symbols
const int lookup_symbol(const char *s);

// printsym(): for testing the content in the list of symbols
void printsym();

#endif