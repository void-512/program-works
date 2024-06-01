#include "morse.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

// === THE MORSE ALPHABET =====================================================

// An association of (Latin) letter and Morse sequence
struct morse_code {
    char latin;    // the Latin character
    char morse[6]; // the Morse sequence
};

const int MORSE_ALPHABET_LENGTH = 28;
const struct morse_code MORSE_ALPHABET[28] = {
    {'A', ".-"},
    {'B', "-..."},
    {'C', "-.-."},
    {'D', "-.."},
    {'E', "."},
    {'F', "..-."},
    {'G', "--."},
    {'H', "...."},
    {'I', ".."},
    {'J', ".---"},
    {'K', "-.-"},
    {'L', ".-..."},
    {'M', "--"},
    {'N', "-."},
    {'O', "---"},
    {'P', ".--."},
    {'Q', "--.-"},
    {'R', ".-."},
    {'S', "..."},
    {'T', "-"},
    {'U', "..-"},
    {'V', "...-"},
    {'W', ".--"},
    {'X', "-..-"},
    {'Y', "-.--"},
    {'Z', "--.."},
    {' ', "P"},     // Represents a long pause
    {'\0', ".-.-."} // Prosign AR: end of transmission
};

// --- THE MORSE ALPHABET: HELPER FUNCTIONS -----------------------------------

// ma_get_morse(letter) returns the Morse sequence associated with the Latin
//   character letter.
// requires: letter must be a Latin letter, space, or the null-terminator
// time:     O(1)
const char *ma_get_morse(char letter) {
    for (int i = 0; i < MORSE_ALPHABET_LENGTH; ++i) {
        if ((MORSE_ALPHABET[i].latin == letter) || (MORSE_ALPHABET[i].latin == letter - 'a' + 'A')) {
            return MORSE_ALPHABET[i].morse;
        }
    }
    assert(false);
}

// ma_get_latin(morse) returns the Latin character associated with the Morse
//   sequence *morse.
// requires: *morse must represent a Latin letter, space, or AR (end of
//             transmission)
// time:     O(1)
const char ma_get_latin(const char *morse) {
    for (int i = 0; i < MORSE_ALPHABET_LENGTH; i++) {
        if (strcmp(MORSE_ALPHABET[i].morse, morse) == 0) {
            return MORSE_ALPHABET[i].latin;
        }
    }
    assert(false);
}

// === MODULE FUNCTIONS =======================================================

void morse_encode(char *morse_text, const char *plain_text) {
    int len = strlen(plain_text);
    int pos = 0;
    for (int i = 0; i <= len; i++) {
        const char *temp = ma_get_morse(plain_text[i]);
        int morse_len = strlen(temp);
        for (int j = 0; j < morse_len; j++) {
            morse_text[pos] = temp[j];
            pos++;
        }
        if (i != len) {
            morse_text[pos] = ' ';
            pos++;
        }
    }
    morse_text[pos] = '\0';
}


void morse_decode(char *plain_text, const char *morse_text) {
    int text_idx = 0;
    for (int morse_idx = 0; morse_text[morse_idx] != '\0';) {
        char morse[6] = {'\0'};
        for (int i = morse_idx; morse_text[i] != ' ' && morse_text[i] != '\0'; i++) {
            morse[i - morse_idx] = morse_text[i];
        }
        morse_idx += strlen(morse) + 1;
        plain_text[text_idx] = ma_get_latin(morse);
        text_idx++;
    }
    plain_text[text_idx] = '\0';
}