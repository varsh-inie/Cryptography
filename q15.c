#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000

// English letter frequency (in percentages)
const double englishFreq[26] = {
    12.70, 9.06, 8.17, 7.51, 6.97, 6.75, 6.33, 6.09, 5.99, 4.25,
    2.78, 2.78, 2.41, 2.36, 2.23, 2.03, 1.93, 1.82, 1.49, 1.11,
    0.69, 0.63, 0.57, 0.11, 0.10, 0.07
};

// Function to calculate letter frequencies in a text
void calculateFrequencies(const char* text, double freq[26]) {
    int count[26] = {0};
    int total = 0;
    
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            count[tolower(text[i]) - 'a']++;
            total++;
        }
    }
    
    for (int i = 0; i < 26; i++) {
        freq[i] = (double)count[i] * 100.0 / total;
    }
}

// Function to decrypt ciphertext using a given key
void decryptWithKey(const char* ciphertext, char* plaintext, int key) {
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - key + 26) % 26 + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to calculate the chi-squared statistic
double chiSquared(const double observed[26], const double expected[26]) {
    double chi2 = 0.0;
    for (int i = 0; i < 26; i++) {
        double diff = observed[i] - expected[i];
        chi2 += diff * diff / expected[i];
    }
    return chi2;
}

// Function to perform frequency attack and print top N possible plaintexts
void frequencyAttack(const char* ciphertext, int topN) {
    char possiblePlaintexts[26][MAX_TEXT_LENGTH];
    double freq[26];
    double chi2Values[26];
    
    for (int key = 0; key < 26; key++) {
        decryptWithKey(ciphertext, possiblePlaintexts[key], key);
        calculateFrequencies(possiblePlaintexts[key], freq);
        chi2Values[key] = chiSquared(freq, englishFreq);
    }
    
    // Sort keys based on chi-squared values
    int keys[26];
    for (int i = 0; i < 26; i++) {
        keys[i] = i;
    }
    
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (chi2Values[keys[i]] > chi2Values[keys[j]]) {
                int temp = keys[i];
                keys[i] = keys[j];
                keys[j] = temp;
            }
        }
    }
    
    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN && i < 26; i++) {
        printf("Key %2d: %s\n", keys[i], possiblePlaintexts[keys[i]]);
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    int topN;
    
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline character

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);
    
    frequencyAttack(ciphertext, topN);
    
    return 0;
}