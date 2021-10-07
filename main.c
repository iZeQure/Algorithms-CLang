#include <stdio.h>

void string_reverse(char *rawStr) {
    int len; char temp;
    len = strlen(rawStr);

    for (int i = 0; i < len / 2; ++i) {
        temp = rawStr[i];
        rawStr[i] = rawStr[len - i - 1];
        rawStr[len - i  - 1] = temp;
    }

    printf("Reverse: %s Address: %p", rawStr, &rawStr);
}

int main(void) {
    char s[100];

    printf("Enter word to reverse: \n");

    gets_s(s, 100);

    // Reverse String.
    string_reverse(s);

    return 0;
}
