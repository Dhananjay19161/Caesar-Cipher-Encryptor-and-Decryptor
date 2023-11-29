#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILENAME_LENGTH 100

void encryptCaesar(FILE *input, FILE *output, int key) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (isalpha(ch)) {
            if (isupper(ch)) {
                ch = (ch + key - 'A') % 26 + 'A';
            } else {
                ch = (ch + key - 'a') % 26 + 'a';
            }
        }
        fputc(ch, output);
    }
}

void decryptCaesar(FILE *input, FILE *output, int key) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (isalpha(ch)) {
            if (isupper(ch)) {
                ch = (ch - key - 'A' + 26) % 26 + 'A';
            } else {
                ch = (ch - key - 'a' + 26) % 26 + 'a';
            }
        }
        fputc(ch, output);
    }
}

void encryptVigenere(FILE *input, FILE *output, const char *key) {
    int keyLen = strlen(key);
    char ch;
    int keyIndex = 0;

    while ((ch = fgetc(input)) != EOF) {
        if (isalpha(ch)) {
            int offset = isupper(ch) ? 'A' : 'a';
            ch = (ch + key[keyIndex] - offset) % 26 + offset;
            keyIndex = (keyIndex + 1) % keyLen;
        }
        fputc(ch, output);
    }
}

void decryptVigenere(FILE *input, FILE *output, const char *key) {
    int keyLen = strlen(key);
    char ch;
    int keyIndex = 0;

    while ((ch = fgetc(input)) != EOF) {
        if (isalpha(ch)) {
            int offset = isupper(ch) ? 'A' : 'a';
            ch = (ch - key[keyIndex] + 26 - offset) % 26 + offset;
            keyIndex = (keyIndex + 1) % keyLen;
        }
        fputc(ch, output);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <operation> <key>\n", argv[0]);
        return 1;
    }

    char *inputFilename = argv[1];
    char *outputFilename = argv[2];
    char *operation = argv[3];
    char *key = argv[4];

    FILE *input = fopen(inputFilename, "r");
    if (input == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output = fopen(outputFilename, "w");
    if (output == NULL) {
        perror("Error creating output file");
        fclose(input);
        return 1;
    }

    if (strcmp(operation, "encrypt") == 0) {
        encryptVigenere(input, output, key);
        printf("File encrypted successfully.\n");
    } else if (strcmp(operation, "decrypt") == 0) {
        decryptVigenere(input, output, key);
        printf("File decrypted successfully.\n");
    } else {
        fprintf(stderr, "Invalid operation. Use 'encrypt' or 'decrypt'.\n");
    }

    fclose(input);
    fclose(output);

    return 0;
}
