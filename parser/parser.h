// remove_comments(source) removes all comments from the string source.
//   Comments may be single-line, i.e., between // and the end of the line, or
//   multi-line, i.e., between /* and the next */.
// requires: *source must be syntactically correct C code [not asserted]
// effects:  mutates *source
// time:     O(n)
void remove_comments(char *source);