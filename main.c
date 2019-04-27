#include<stdio.h>
#include<stdlib.h>

void RotationCipherEncryption(void);
void RotationCipherDecryption(void);
void SubstitutionCipherEncryption(void);
void SubstitutionCipherDecryption(void);
void RotationCipherDecryptionNoKey(void);

int main() 
{
    FILE *input;
    input = fopen("input.txt", "r");                   //Sets input.txt as a file to be read
    int option;
    fseek(input, 249, 0);                              //Jumps to part in file where task selection is chosen = option
    fscanf(input, "%d", &option);                      //Reads option choice
    switch(option) {                                   //Depending on the option chosen in the file, the switch case will chose a function to run
        case 1: RotationCipherEncryption();
            break;
        case 2: RotationCipherDecryption();
            break;
        case 3: SubstitutionCipherEncryption();
            break;
        case 4: SubstitutionCipherDecryption();
            break;
        case 5: RotationCipherDecryptionNoKey();
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
void RotationCipherEncryption(void) 
{
    FILE *input, *output;
    input = fopen("input.txt", "r");                   //Opens the input.txt file for reading
    output = fopen("output.txt", "w");                 //Opens the output.txt file for writing
    int k;
    fseek(input, 266, 0);                              //Finds the key given in the file
    fscanf(input, "%d", &k);                           //Assigns the key value to k
    fseek(input, 343, 0);                              //Jumps to text to be encrypted in the file
    while(feof(input) == 0) {                          //If the file is not at the end, this loop will continue to encrypt letters
        char c;
        fscanf(input, "%c", &c);                       //Reads letter
        if(c > 64 && c < 91) {                         //If character is not a space, it will be encrypted. If it is a space, it will be left as a space and not encrypted
            while(k > 26) {                            //If the key is greater than 26 it will be brought back to a number between 1 and 26. This can occur multiple times if the key is very large
                k = k - 26;
            }
            
            if(c + k > 'Z') {                          //If the key will overflow to some other non-letter character, it will be brought back to the start of the alphabet to its letter
                c = c + k - 26;
            } else {                                   //If the letter is not a space and it does not overflow, just add the key to get the encrypted letter
            c = c + k;
            }
        }
        fprintf(output, "%c", c);                      //Prints to output.txt file
        printf("%c", c);                               //Print the encrypted letter to the console
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
void RotationCipherDecryption(void) 
{
    FILE *input, *output;
    input = fopen("input.txt", "r");                   //Opens the input.txtfile for reading
    output = fopen("output.txt", "w");                 //Opens the output.txt file for writing
    int k;
    fseek(input, 266, 0);                              //Finds the key given in the file
    fscanf(input, "%d", &k);                           //Assigns the key value to k
    fseek(input, 343, 0);                              //Jumps to text to be decrypted in the file
    while(feof(input) == 0) {                          //If the file is not at the end, this loop will continue to decrypt letters
        char c;
        fscanf(input, "%c", &c);                       //Reads letter
        if(c > 64 && c < 91) {                         //If the character is not a space, it will be decrypted. If it is a space, it will be left as a space and not encrypted
            while(k > 26) {                            //If the key is greater than 26 it will be brought back to a number between 1 and 26. This can occur multiple times if the key is very large
                k = k - 26;
            }
            
            if(c - k < 'A') {                          //If the key will overflow to some other non-letter character, it will be brought back to the end of the alphabet to its letter
                c = c - k + 26;
            } else {                                   //If the letter is not a space and it does not overflow, just subtract the key to get the decrypted letter
            c = c - k;
            }
        }
        fprintf(output, "%c", c);                      //Prints to output.txt file
        printf("%c", c);                               //Print the decrypted letter to the console
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
void SubstitutionCipherEncryption(void) 
{
    FILE *input, *output;
    input = fopen("input.txt", "r");                   //Opens the input.txt file for reading
    output = fopen("output.txt", "w");                 //Opens the output.txt file for writing
    fseek(input, 343, 0);                              //Jumps to given text to be encrypted
    while(feof(input) == 0) {                          //If the file is not at the end, this loop will continue to encrypt letters
        int p = ftell(input);                          //Assignment to remember point in the text to use later to continue encryption. The file jumps to other points so needs a memory of where it was initially
        char c;
        fscanf(input, "%c", &c);                       //Reads the character
        if(c < 65 || c > 90) {                         //If the character is not a letter, skip encryption and print the character as it is
        } else {                                       //If the character is not a space, find the letters place in the normal alphabet and using the key, find the corresponding encryption character in the same place in the key alphabet
            c = c - 65;                                //Find character's place in the alphabet
            fseek(input, 287 + c, 0);                  //Jump to key alphabet and find corresponding character in the same place
            fscanf(input, "%c", &c);                   //Assign this encrypted character to c
        }
        fprintf(output, "%c", c);                      //Prints to output.txt file
        printf("%c", c);                               //Prints to console
        fseek(input, p + 1, 0);                        //Use the stored starting place and add 1 to move to next character in the given text
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
void SubstitutionCipherDecryption(void) 
{
    FILE *input, *output;
    input = fopen("input.txt", "r");                   //Opens the input.txt file for reading
    output = fopen("output.txt", "w");                 //Opens the output.txt file for writing
    fseek(input, 343, 0);                              //Jumps to the encrypted text given
    while(feof(input) == 0) {                          //If the file is not at the end, this loop will continue to decrypt letters
        int p = ftell(input);                          //The place in the given text is stored, so that when the file is accessed at different points the point in the given text is 'remembered'. This value is later used to jump to the next letter in the text to decrypt it.
        char c;
        fscanf(input, "%c", &c);                       //Reads the encrypted character
        if(c < 65 || c > 90) {                         //If the character is a space, print a space. Else decrypt the character
            fprintf(output, "%c", c);
            printf("%c", c);
        } else {                                       //If the character is not a space, find the character's place in the given key and print the corresponding decrpyted character
            int loop = 0;                              //Initialise a loop condition
            while(loop >= 0) {                         //This loop checks to see if the character's ASCII number is equal to the character in the key. If it is, print the corresponding decrypted character. If not, check the next letter in the key. Rinse and repeat...
                fseek(input, 287 + loop, 0);           //Jumps to a certain character in the key
                char cs;                               //Uninitialised variable for the key character
                fscanf(input, "%c", &cs);              //Reads key character
                if(c == cs) {                          //If the key character and the text character are the same, print the corresponding decrypted letter
                    char decrypt = ftell(input) - 287; //Finds the place in the key e.g. first, second...
                    c = 64 + decrypt;                  //Assigns c a new value as the decrypted letter
                    fprintf(output, "%c", c);          //Prints to output.txt file
                    printf("%c", c);                   //Prints to console
                    loop = -1;                         //Breaks condition for loop so the next letter in the text can be tested
                } else {
                    loop = loop + 1;                   //By incrementing the variable loop by 1, the next character is checked. This only occurs if the characters were not equal to each other
                }
            }
            
        }
        fseek(input, p + 1, 0);                        //Increment p to jump to the next letter of the text
    }
    
    return;
}

/*ROTATION_CIPHER_DECRYPTION_NO_KEY
 * 
 * This function decrypts a given text that was encrypted with a rotation cipher with some key. The idea behind
 * this decryption function is by assuming the most common letter in the given text is an 'E' - so the key can
 * be found by finding the most common encrypted letter and finding how many places it is away from  'E' and 
 * using this as the key for decryption. The frequenecy of each letter is counted and the most frequent letter 
 * will give the greatest value - assumed to be 'E'. This function must receive text from the input.txt file
 * and must be all upper case letters and can include spaces and special characters. This function will only 
 * decrypt correctly IF AND ONLY IF the most common letter in the decrypted message is the letter 'E'.
 * 
 */
void RotationCipherDecryptionNoKey(void) 
{
    FILE *input, *output;
    input = fopen("input.txt", "r");                   //Opens the file input.txt for reading
    output = fopen("output.txt", "w");                 //Opens the output.txt file for writing
    fseek(input, 343, 0);                              //Jump to given encrypted text
    //Below - the variables initialised are for the letters of the alphabet that are going to be counted
    int A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, G = 0, H = 0, I = 0, J = 0, K = 0, L = 0, M = 0, N = 0, O = 0, P = 0, Q = 0, R = 0, S = 0, T = 0, U = 0, V = 0, W = 0, X = 0, Y = 0, Z = 0;
    char c;
    while(!feof(input)) {                              //While the file is not at the end, this loop will continue to run
        fscanf(input, "%c", &c);                       //Read a character
        switch(c) {                                    //If the character is a letter, one of the cases are true and the letter variable will be incremented by one, representing the frequency of that particular letter
            case 65: A++;
                break;
            case 66: B++;
                break;
            case 67: C++;
                break;
            case 68: D++;
                break;
            case 69: E++;
                break;
            case 70: F++;
                break;
            case 71: G++;
                break;
            case 72: H++;
                break;
            case 73: I++;
                break;
            case 74: J++;
                break;
            case 75: K++;
                break;
            case 76: L++;
                break;
            case 77: M++;
                break;
            case 78: N++;
                break;
            case 79: O++;
                break;
            case 80: P++;
                break;
            case 81: Q++;
                break;
            case 82: R++;
                break;
            case 83: S++;
                break;
            case 84: T++;
                break;
            case 85: U++;
                break;
            case 86: V++;
                break;
            case 87: W++;
                break;
            case 88: X++;
                break;
            case 89: Y++;
                break;
            case 90: Z++;
                break;
            default: break;                            //If the character is not a letter, exit the switch case
        }
    }
    
    //Below - this array takes the values that have been found by the previous while loop. This array
    //must be initialised after the loop to hold the correct values rather than 0 which is the value
    //of the variables before the loop
    int letters[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z}; 
    int location, n, maximum = 0;                      //Location refers to place of the letter in the alphabet e.g. 'A'=0. 'n' is a counter, maximum is the total number of occurences
    for(n = 0; n < 26; n++) {                          //This loop runs through all the variables of the array and finds the most frequent letter and the number of times it occured
        if(letters[n] > maximum) {
            location = n;
            maximum = letters[n];
        }
    }
    
    char k = location - 4;                             //The key 'k' is derived by assuming the most frequent letter was an 'E'
    fseek(input, 343, 0);                              //Jump back from the end of the file to the start of the encrypted text
    while(!feof(input)) {                              //While the file is not at the end, the loop will continue. This loop finds the decrypted text and prints it
        fscanf(input, "%c", &c);                       //Read a character
        if(c < 65 || c > 90) {                         //If the character is not a letter e.g c=' ' or c='?'... print it
            fprintf(output, "%c", c);                  //Prints to output.txt file
            printf("%c", c);
        } else if(c - k < 65) {                        //If the character is a letter but overflows outside of the capital letters on the ASCII table it will be brought back in
            c = c - k + 26;
            fprintf(output, "%c", c);                  //Prints to output.txt file
            printf("%c", c);                           //Prints to console
        } else if(c - k > 90) { 
            c = c - k -26;
            fprintf(output, "%c", c);                  //Prints to output.txt file
            printf("%c", c);                           //Prints to console
        } else {                                       //If the character is a letter and does not overflow, just subtract the key
            c = c - k;
            fprintf(output, "%c", c);                  //Prints to output.txt file
            printf("%c", c);                           //Prints to console
        }
    }
    
    return;
}