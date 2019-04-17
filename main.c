#include <stdio.h>

//The argument for encryption and decryption is the key of rotation
void Rotation_Encryption(int k);
void Rotation_Decryption(int key);

int main()
{
    Rotation_Encryption(1); 
    Rotation_Decryption(1);
    return 0;
}

//This function encrypts a given message by a given key
void Rotation_Encryption(int key) {
    char input[] = "HELLO WORLD";
    int n = sizeof(input) - 1;
    for(int i = 0; i < n; i++) {
        input[i] = input[i] + key%26;
        if(input[i] > 90) {
            input[i] = input[i] - 26;
        } else if(input[i] - key%26 == 32) {
            input[i] = 32;
        }
    }
    printf("%s \n", input);    
}

//This function decrypts a message given the key and the encrypted text
void Rotation_Decryption(int key) {
    char input[] = "IFMMP XPSME";
    int n = sizeof(input) - 1;
    for(int i = 0; i < n; i++) {
        input[i] = input[i] - key%26;
        if(input[i] + key%26 == 32) {
            input[i] = 32;
        } else if(input[i] < 65) {
            input[i] = input[i] + 26;
        }
    }
    printf("%s \n", input);
}