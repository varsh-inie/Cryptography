#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

void decode(const char *ciphertext, char *decoded, const char *substitution) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (ch >= '0' && ch <= '9') {
            decoded[i] = substitution[ch - '0'];
        } else {
            decoded[i] = ch;
        }
    }
    decoded[strlen(ciphertext)] = '\0';
}

int main() {
    const char *ciphertext = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 "
                             "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* "
                             ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?";

    char substitution[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    char decoded[MAX_LEN];

    decode(ciphertext, decoded, substitution);

    printf("Decoded message: %s\n", decoded);

    return 0;
}
