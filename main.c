#include<stdio.h>

void RotationCipherEncryption(void);
void RotationCipherDecryption(void);
void SubstitutionCipherEncryption(void);
void SubstitutionCipherDecryption(void);

int main() {
    FILE *input;
    input = fopen("input.txt", "r"); //Sets input.txt as a file to be read
    int option;
    fseek(input, 210, 0); //Jumps to part in file where task selection is chosen = option
    fscanf(input, "%d", &option);
    switch(option) { //Depending on the option chosen in the file, the switch case will chose a function to run
        case 1: RotationCipherEncryption();
            break;
        case 2: RotationCipherDecryption();
            break;
        case 3: SubstitutionCipherEncryption();
            break;
        case 4: SubstitutionCipherDecryption();
            break;
    }
    return 0;
}

/*ROTATION_CIPHER_ENCRYPTION
 * 
 * This function encrypts given text from the file input.txt using a rotation cipher.
 * Put simply, the function adds some number to the number for each letter on the ASCII table to rotate it to some 
 * other letter. If the number is greater than 90 it will overflow to other characters and so must be brought back 
 * to the desired letters. If the key for rotation given is greater than 26, the key will be brought back to some 
 * number between 1 and 26 since this is equivalent rotation. The key must be a two digit positive number 
 * (0 <= key < 100).
 *
 */
void RotationCipherEncryption(void) {
    FILE *input;
    input = fopen("input.txt", "r");//Opens the input.txt file for reading
    int k;
    fseek(input, 227, 0); //Finds the key given in the file
    fscanf(input, "%d", &k); //Assigns the key value to k
    fseek(input, 304, 0); //Jumps to text to be encrypted in the file
    
    while(!feof(input)) { //If the file is not at the end, this loop will continue to encrypt letters
        char c;
        fscanf(input, "%c", &c); //Reads letter
        
        if(c != 32) { //If character is not a space, it will be encrypted. If it is a space, it will be left as 
                      //a space and not encrypted
            while(k > 26) { //If the key is greater than 26 it will be brought back to a number between 1 and 
                            //26. This can occur multiple times if the key is very large
                k = k - 26;
            }
            if(c + k >90) { //If the key will overflow to some other non-letter character, it will be brought 
                            //back to the start of the alphabet to its letter
                c = c + k - 26;
            }

            else //If the letter is not a space and it does not overflow, just add the key to get the encrypted
                 //letter
            c = c + k;
        }
        
        printf("%c", c); //Print the encrypted letter to the console
    }
}

/*ROTATION_CIPHER_DECRYPTION
 * 
 * This function decrypts given text from the file input.txt which has been encrypted with a rotation cipher.
 * This function works similarly to the above encryption file, instead subtracting the key to decrypt the text 
 * rather than adding the key to encrypt the text. If the number becomes less than 65, 26 is added to assign
 * the letter the correct character as it 'overflows' to the other end of the alphabet. The key must be a two
 * digit positive number (0 <= key < 100).
 *
 */
void RotationCipherDecryption(void) {
    FILE *input;
    input = fopen("input.txt", "r"); //Opens the input.txtfile for reading
    int k;
    fseek(input, 227, 0); //Finds the key given in the file
    fscanf(input, "%d", &k); //Assigns the key value to k
    fseek(input, 304, 0); //Jumps to text to be decrypted in the file
    
    while(!feof(input)) { //If the file is not at the end, this loop will continue to decrypt letters
        char c;
        fscanf(input, "%c", &c); //Reads letter
        
        if(c != 32) { //If the character is not a space, it will be decrypted. If it is a space, it will be left
                      //as a space and not encrypted
            while(k > 26) { //If the key is greater than 26 it will be brought back to a number between 1 and 
                            //26. This can occur multiple times if the key is very large
                k = k - 26;
            }
            if(c - k < 65) { //If the key will overflow to some other non-letter character, it will be brought 
                            //back to the end of the alphabet to its letter
                c = c - k + 26;
            }

            else //If the letter is not a space and it does not overflow, just subtract the key to get the 
                 //decrypted letter
            c = c - k;
        }
        
        printf("%c", c); //Print the decrypted letter to the console
    }
    return;
}

/*SUBSTITUTION_CIPHER_ENCRYPTION
 * 
 * This function encrypts given text in the input.txt file using a substitution cipher.
 * This function finds each character's place in the alphabet (e.g. a = 0, b = 1...) and assigns each letter
 * a new encrypted character given in the substitution key using each characters' place that was found. This
 * function stores where it is up to in reading the text since it jumps to other spots to encrypt it so must
 * 'remember' where it was up to in order to keep encrypting the text. The key given must be in upper case
 * letters, be 26 characters long and should include each letter once. Letters can be given in any order.
 *
 */
void SubstitutionCipherEncryption(void) {
    FILE *input;
    input = fopen("input.txt", "r"); //Opens the input.txt file for reading
    fseek(input, 304, 0); //Jumps to given text to be encrypted
    while(!feof(input)) { //If the file is not at the end, this loop will continue to encrypt letters
        int p = ftell(input); //Assignment to remember point in the text to use later to continue
                              //encryption. The file jumps to other points so needs a memory of where
                              //it was initially
        char c;
        fscanf(input, "%c", &c); //Reads the character
        if(c == 32) { //If the character is a space, print a space and go to the next character
            printf(" ");
            }
        else { //If the character is not a space, find the letters place in the normal alphabet and 
               //using the key, find the corresponding encryption character in the same place in 
               //the key alphabet
            c = c - 65; //Find character's place in the alphabet
            fseek(input, 248 + c, 0); //Jump to key alphabet and find corresponding character in the 
                                      //same place
            fscanf(input, "%c", &c); //Assign this encrypted character to c
            printf("%c", c); //Print encrypted letter to console
        }
        fseek(input, p + 1, 0); //Use the stored starting place and add 1 to move to next character
                                //in the given text
    }
    return;
}

/*SUBSTITUTION_CIPHER_DECRYPTION
 * 
 * This function decrypts an encrypted text that was encrypted using a substitution cipher and a key.
 * The key must come in the form of 26 upper case letters, where each letter should only be used once.
 * The first letter encrypts the letter A, the second B, the third C... The twenty sixth letter Z.
 * The letters can come in any order. This function turns a letter into its corresponding number on the
 * ASCII table and checks through the key given to find the place of the letter in the key. The place 
 * Corresponds to a decrypted letter and this letter is printed to the console. For example, if H was 
 * the fifth letter of the key, it would be printed as an E. This process loops until the end of the 
 * file is reached which is equivalent to the end of the encrypted text.
 * 
 */
void SubstitutionCipherDecryption(void) {
    FILE *input;
    input = fopen("input.txt", "r"); //Opens the input.txt file for reading
    fseek(input, 304, 0); //Jumps to the encrypted text given
    while(!feof(input)) { //If the file is not at the end, this loop will continue to decrypt letters
        int p = ftell(input); //The place in the given text is stored, so that when the file is accessed
                              //at different points the point in the given text is 'remembered'. This 
                              //value is later used to jump to the next letter in the text to decrypt it.
        char c;
        fscanf(input, "%c", &c); //Reads the encrypted character
        if(c == 32) { //If the character is a space, print a space. Else decrypt the character
            printf(" ");
        } else { //If the character is not a space, find the character's place in the given key and print
                 //the corresponding decrpyted character
            int loop = 0; //Initialise a loop condition
            while(loop >= 0) { //This loop checks to see if the character's ASCII number is equal to the 
                               //character in the key. If it is, print the corresponding decrypted
                               //character. If not, check the next letter in the key. Rinse and repeat...
                fseek(input, 248 + loop, 0); //Jumps to a certain character in the key
                char cs; //Uninitialised variable for the key character
                fscanf(input, "%c", &cs); //Reads key character
                if(c == cs) { //If the key character and the text character are the same, print the
                              //corresponding decrypted letter
                    char decrypt = ftell(input) - 248; //Finds the place in the key e.g. first, second...
                    c = 64 + decrypt; //Assigns c a new value as the decrypted letter
                    printf("%c", c);
                    loop = -1; //Breaks condition for loop so the next letter in the text can be tested
                } else {
                    loop = loop + 1; //By incrementing the variable loop by 1, the next character is checked.
                                     //This only occurs if the characters were not equal to each other
                }
            }
        }
        fseek(input, p + 1, 0); //Increment p to jump to the next letter of the text
    }
    return;
}