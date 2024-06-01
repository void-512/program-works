#include <stdio.h>
#include "morse.h"

int main(void) {
    char message[1000] = {'\0'};
    int message_len = 0;
    while (scanf("%c", message + message_len) != EOF && message_len < 1000) {
        message_len++;
    }

    printf("Original message:\n%s\n\n", message);
    
    char morse[5000] = {'\0'};
    morse_encode(morse, message);
    printf("Morse message:\n%s\n\n", morse);
    
    morse_decode(message, morse);
    printf("Decoded message:\n%s\n", message);
}