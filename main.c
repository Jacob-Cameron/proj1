#include <stdio.h>

//The argument for encryption is the key of rotation
void Rotation_Encryption(int k);

int main()
{
    Rotation_Encryption(0); 
    return 0;
}

//This function encrypts a given message by a given key
void Rotation_Encryption(int key) {
    char input[] = "HELLO WORLD";
    int n = sizeof(input) - 1;
    for(int i = 0; i<n; i++) {
        input[i] = input[i] + key%26;
        if(input[i]>90) {
            input[i] = input[i] - 26;
        } else if(input[i] - key%26 == 32) {
            input[i] = 32;
        }
    }
    printf("%s", input);    
    }