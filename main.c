#include<stdio.h>

void RotationCipherEncryption(void);
void RotationCipherDecryption(void);

int main() {
    FILE *input;
    input = fopen("input.txt", "r");
    int option;
    fseek(input, 99, 0);
    fscanf(input, "%d", &option);
    switch(option) {
        case 1: RotationCipherEncryption();
            break;
        case 2: RotationCipherDecryption();
            break;
    }
    return 0;
}

void RotationCipherEncryption(void) {
    FILE *input;
    input = fopen("input.txt", "r");
    int k;
    fseek(input, 107, 0);
    fscanf(input, "%d", &k);
    fseek(input, 140, 0);
    
    while(!feof(input)) {
        char c;
        fscanf(input, "%c", &c);
        
        if(c != 32) {
            while(k > 26) {
                k = k - 26;
            }
            if(c + k >90) {
                c = c + k - 26;
            }

            else
            c = c + k;
        }
        
        printf("%c", c);
    }
}

void RotationCipherDecryption(void) {
        FILE *input;
    input = fopen("input.txt", "r");
    int k;
    fseek(input, 107, 0);
    fscanf(input, "%d", &k);
    fseek(input, 140, 0);
    
    while(!feof(input)) {
        char c;
        fscanf(input, "%c", &c);
        
        if(c != 32) {
            while(k > 26) {
                k = k - 26;
            }
            if(c - k < 65) {
                c = c - k + 26;
            }

            else
            c = c - k;
        }
        
        printf("%c", c);
    }
    return;
}