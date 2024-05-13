// morse_encode(morse_text, plain_text) encodes the string *plain_text using
//   Morse code and stores the result in *morse_text.
// requires: *plain_text may only contain letters and spaces (' ')
// effects:  mutates *morse_text
// time:     O(n)
void morse_encode(char *morse_text, const char *plain_text);

// morse_decode(plain_text, morse_text) decodes the string *morse_text using
//   Morse code and stores the result in *plain_text.
// requires: *morse_text may only contain morse sequences for Latin letters
//           and AR (end of transmission), or the letter 'P'
// effects:  mutates *plain_text
// time:     O(n)
void morse_decode(char *plain_text, const char *morse_text);