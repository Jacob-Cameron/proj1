/*******************************************************************
 * ENGG1003 Project 1: English Text Ciphers
 * 
 * Student number: c3306038
 * Due date: Monday, 5pm, 29/04/2019
 * Last change: 29/04/2019
 * 
 * Code synopsis:
 * This code includes a variety of functions to encrypt and decrypt
 * plain english text. The ciphers considered include the rotation
 * (Caesar) cipher and the substitution cipher. The functions 
 * encrypt and decrypt these ciphers when given a key. An input
 * and output file are used for reading and writing respectively,
 * where the text can be read, a task can be selected and the key
 * given. When no key is given, a statistical approach is taken to 
 * give the most likely outcome for rotation cipher decryption and 
 * likely letter decryption for the substiution cipher for a 
 * significant number of letters.
 ******************************************************************/

#include<stdio.h>
#include<stdlib.h>


#define INPUT_FILE      "input.txt"                    //Defining "input.txt" as INPUT_FILE for easier reading and understanding for the user
#define OUTPUT_FILE     "output.txt"                   //Defining "output.txt" as OUTPUT_FILE for easier reading and understanding for the user


void RotationCipherEncryptionGivenKey(void);           //Function prototypes
void RotationCipherDecryptionGivenKey(void);
void SubstitutionCipherEncryptionGivenKey(void);
void SubstitutionCipherDecryptionGivenKey(void);
void RotationCipherDecryptionNoKey(void);
void SubstitutionCipherDecryptionNoKey(void);


int main() 
{
    FILE *input;
    input = fopen(INPUT_FILE, "r");                    //Sets input.txt as a file to be read
    if(input == NULL) {                                //If an error occurs opening the input file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return 0;
    }
    int option;
    fseek(input, 292, 0);                              //Jumps to part in file where task selection is chosen = option
    fscanf(input, "%d", &option);                      //Reads option choice
    fclose(input);                                     //Closes the input file
    switch(option) {                                   //Depending on the option chosen in the file, the switch case will chose a function to run
        case 1: RotationCipherEncryptionGivenKey();
            break;
        case 2: RotationCipherDecryptionGivenKey();
            break;
        case 3: SubstitutionCipherEncryptionGivenKey();
            break;
        case 4: SubstitutionCipherDecryptionGivenKey();
            break;
        case 5: RotationCipherDecryptionNoKey();
            break;
        case 6: SubstitutionCipherDecryptionNoKey();
            break;
    }
    return 0;
}


/*ROTATION_CIPHER_ENCRYPTION_GIVEN_KEY
 * 
 * This function encrypts given text from the file input.txt using a rotation cipher.
 * This function accepts a given text which can include any character but all letters must be upper case. The text
 * must also be followed by a space at the end of it for the encryption of the file to work as it should be working.
 * Put simply, the function adds some number to the number for each letter on the ASCII table to rotate it to some 
 * other letter. If the number is greater than 90 it will overflow to other characters and so must be brought back 
 * to the desired letters. If the key for rotation given is greater than 26, the key will be brought back to some 
 * number between 1 and 26 since this is equivalent rotation. The key must be a two digit positive number e.g. 1=01
 * (00 <= key < 100). The output comes in the same form as the input an is printed to the console and also printed
 * to the output file.
 *
 */
void RotationCipherEncryptionGivenKey(void) 
{
    FILE *input, *output;
    input = fopen(INPUT_FILE, "r");                    //Opens the input.txt file for reading
    if(input == NULL) {                                //If an error occurs opening the input file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    output = fopen(OUTPUT_FILE, "w");                  //Opens the output.txt file for writing
    if(output == NULL) {                               //If an error occurs opening the output file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    int k;
    fseek(input, 309, 0);                              //Finds the key given in the file
    fscanf(input, "%d", &k);                           //Assigns the key value to k
    fseek(input, 386, 0);                              //Jumps to text to be encrypted in the file
    while(feof(input) == 0) {                          //If the file is not at the end, this loop will continue to encrypt letters
        char c;
        fscanf(input, "%c", &c);                       //Reads letter
        if(c > 64 && c < 91) {                         //If character is not a space, it will be encrypted. If it is a space, it will be left as a space and not encrypted
            if(k > 25) {                               //If the key is greater than 26 it will be brought back to a number between 0 and 25
                k = k % 26;
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
    
    fclose(input);                                     //Closes the input file
    fclose(output);                                    //Closes the output file
}


/*ROTATION_CIPHER_DECRYPTION_GIVEN_KEY
 * 
 * This function decrypts given text from the file input.txt which has been encrypted with a rotation cipher.
 * The given text can include any characters but all letters must be upper case for the decryption to work.
 * This function works similarly to the above encryption file, instead subtracting the key to decrypt the text 
 * rather than adding the key to encrypt the text. If the number becomes less than 65, 26 is added to assign
 * the letter the correct character as it 'overflows' to the other end of the alphabet. The key must be a two
 * digit positive number (0 <= key < 100). The output text comes in the same form as the given input text, and 
 * is printed to the console and the output file.
 *
 */
void RotationCipherDecryptionGivenKey(void) 
{
    FILE *input, *output;
    input = fopen(INPUT_FILE, "r");                    //Opens the input.txtfile for reading
    if(input == NULL) {                                //If an error occurs opening the input file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    output = fopen(OUTPUT_FILE, "w");                  //Opens the output.txt file for writing
    if(output == NULL) {                               //If an error occurs opening the output file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    int k;
    fseek(input, 309, 0);                              //Finds the key given in the file
    fscanf(input, "%d", &k);                           //Assigns the key value to k
    fseek(input, 386, 0);                              //Jumps to text to be decrypted in the file
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
    
    fclose(input);                                     //Closes the input file
    fclose(output);                                    //Closes the output file
    return;
}


/*SUBSTITUTION_CIPHER_ENCRYPTION_GIVEN_KEY
 * 
 * This function encrypts given text in the input.txt file using a substitution cipher.
 * The given text can include any character but all letters must be upper case for the correct encryption.
 * This function finds each character's place in the alphabet (e.g. a = 0, b = 1...) and assigns each letter
 * a new encrypted character given in the substitution key using each characters' place that was found. The
 * key must be given as 26 consecutive upper case letters e.g. ABCDEFGHIJKLMNOPQRSTUVWXYZ for encryption. This
 * function stores where it is up to in reading the text since it jumps to other spots to encrypt, so must
 * 'remember' where it was up to in order to keep encrypting the text. Letters in the key can be given in any order.
 * Each letter should only be used once each in the key.
 * The encrypted output text is printed to the console and the ouput file in the same form as the given text.
 *
 */
void SubstitutionCipherEncryptionGivenKey(void) 
{
    FILE *input, *output;
    input = fopen(INPUT_FILE, "r");                    //Opens the input.txt file for reading
    if(input == NULL) {                                //If an error occurs opening the input file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    output = fopen(OUTPUT_FILE, "w");                  //Opens the output.txt file for writing
    if(output == NULL) {                               //If an error occurs opening the output file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    fseek(input, 386, 0);                              //Jumps to given text to be encrypted
    while(feof(input) == 0) {                          //If the file is not at the end, this loop will continue to encrypt letters
        int p = ftell(input);                          //Assignment to remember point in the text to use later to continue encryption. The file jumps to other points so needs a memory of where it was initially
        char c;
        fscanf(input, "%c", &c);                       //Reads the character
        if(c < 65 || c > 90) {                         //If the character is not a letter, skip encryption and print the character as it is
        } else {                                       //If the character is not a space, find the letters place in the normal alphabet and using the key, find the corresponding encryption character in the same place in the key alphabet
            c = c - 65;                                //Find character's place in the alphabet
            fseek(input, 330 + c, 0);                  //Jump to key alphabet and find corresponding character in the same place
            fscanf(input, "%c", &c);                   //Assign this encrypted character to c
        }
        fprintf(output, "%c", c);                      //Prints to output.txt file
        printf("%c", c);                               //Prints to console
        fseek(input, p + 1, 0);                        //Use the stored starting place and add 1 to move to next character in the given text
    }
    
    fclose(input);                                     //Closes the input file
    fclose(output);                                    //Closes the output file
    return;
}


/*SUBSTITUTION_CIPHER_DECRYPTION_GIVEN_KEY
 * 
 * This function decrypts an encrypted text that was encrypted using a substitution cipher and a key.
 * The given text can include any character but letters must be upper case for the correct decryption.
 * The key must come in the form of 26 upper case letters e.g. ABCDEFGHIJKLMNOPQRSTUVWXYZ , where each 
 * letter should only be used once. The first letter encrypts the letter A, the second B, the third C... 
 * The twenty sixth letter Z. The letters can come in any order. This function turns a letter into its 
 * corresponding number on the ASCII table and checks through the key given to find the place of the 
 * letter in the key. The place Corresponds to a decrypted letter and this letter is printed to the console. 
 * For example, if H was  the fifth letter of the key, it would be printed as an E. This process loops until 
 * the end of the file is reached which is equivalent to the end of the encrypted text. The decrypted output 
 * text comes in the same form as the input text and is printed to the console and the output file.
 * 
 */
void SubstitutionCipherDecryptionGivenKey(void) 
{
    FILE *input, *output;
    input = fopen(INPUT_FILE, "r");                    //Opens the input.txt file for reading
    if(input == NULL) {                                //If an error occurs opening the input file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    output = fopen(OUTPUT_FILE, "w");                  //Opens the output.txt file for writing
    if(output == NULL) {                               //If an error occurs opening the output file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    fseek(input, 386, 0);                              //Jumps to the encrypted text given
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
                fseek(input, 330 + loop, 0);           //Jumps to a certain character in the key
                char cs;                               //Uninitialised variable for the key character
                fscanf(input, "%c", &cs);              //Reads key character
                if(c == cs) {                          //If the key character and the text character are the same, print the corresponding decrypted letter
                    char decrypt = ftell(input) - 330; //Finds the place in the key e.g. first, second...
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
    
    fclose(input);                                     //Closes the input file
    fclose(output);                                    //Closes the output file
    return;
}


/*ROTATION_CIPHER_DECRYPTION_NO_KEY
 * 
 * This function decrypts a given text that was encrypted with a rotation cipher with some key. The given text
 * can include any character but letters must all be upper case for correct decryption to occur. The idea behind
 * this decryption function is by assuming the most common letter in the given text is an 'E' - so the key can
 * be found by finding the most common encrypted letter and finding how many places it is away from  'E' and 
 * using this as the key for decryption. The frequenecy of each letter is counted and the most frequent letter 
 * will give the greatest value - assumed to be 'E'. This function must receive text from the input.txt file
 * and must be all upper case letters and can include spaces and special characters. This function will only 
 * decrypt correctly IF AND ONLY IF the most common letter in the decrypted message is the letter 'E'. The output
 * text comes in the same form as the given text and is printed to the console and the output file.
 * 
 */
void RotationCipherDecryptionNoKey(void) 
{
    FILE *input, *output;
    input = fopen(INPUT_FILE, "r");                    //Opens the file input.txt for reading
    if(input == NULL) {                                //If an error occurs opening the input file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    output = fopen(OUTPUT_FILE, "w");                  //Opens the output.txt file for writing
    if(output == NULL) {                               //If an error occurs opening the output file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    fseek(input, 386, 0);                              //Jump to given encrypted text
    //Below - the variables initialised are for the letters of the alphabet that are going to be counted
    int A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, G = 0, H = 0, I = 0, J = 0, K = 0, L = 0, M = 0, N = 0, O = 0, P = 0, Q = 0, R = 0, S = 0, T = 0, U = 0, V = 0, W = 0, X = 0, Y = 0, Z = 0;
    char c;                                            //This variable is assigned letters read
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
    
    int k = location - 4;                              //The key 'k' is derived by assuming the most frequent letter was an 'E'
    printf("Key = %d\n\n", k);
    fprintf(output, "Key = %d\n\n", k);
    fseek(input, 386, 0);                              //Jump back from the end of the file to the start of the encrypted text
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
    
    fclose(input);                                     //Closes the input file
    fclose(output);                                    //Closes the output file
    return;
}


/*SUBSTITUTION_CIPHER_DECRYPTION_NO_KEY
 * 
 * This function aims to decrypt a given encrypted message that was encrypted with a substitution cipher.
 * The text must be given in the input file, taking any character but any letters must be upper case. The
 * approach taken for this decryption involves assuming the most common letter in the text is an encrypted
 * 'E', the second most 'T', the third most 'A' etc... This approach is purely statistical and usually can
 * decrypt a significant amount of letters. The output comes in the same form as the input, and will be 
 * printed to the console and the output.txt file. The flow control of the function involves opening files,
 * counting the frequency of each letter in the text, assigning the greatest of these 'E', and the following
 * next highest 'T' and so on - giving each letter statistically the most probable outcome for decryption.
 * The larger the given text, the better this function will be able to decrypt it. The output text in is the
 * same form as the given input text and is printed to the console and to the output file.
 *
 */
void SubstitutionCipherDecryptionNoKey(void)
{
    FILE *input, *output;
    input = fopen(INPUT_FILE, "r");                    //Opens the input.txt file for reading
    if(input == NULL) {                                //If an error occurs opening the output file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    output = fopen(OUTPUT_FILE, "w");                  //Opens the output.txt file for writing
    if(output == NULL) {                               //If an error occurs opening the output file, a friendly error message will be printed and the functions will not do anything
        perror("fopen() ");
        return;
    }
    fseek(input, 386, 0);                              //Jumps to the given text to be decrypted in the input file
    char c;                                            //This variable is assigned letters read
    //Below - these variables are for the counter of each letter
    int A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, G = 0, H = 0, I = 0, J = 0, K = 0, L = 0, M = 0, N = 0, O = 0, P = 0, Q = 0, R = 0, S = 0, T = 0, U = 0, V = 0, W = 0, X = 0, Y = 0, Z = 0;
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
    
    //Below - this array takes the values that have been found by the previous while loop
    int letters26[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z}; 
    int location, n, maximum = 0;                      //Location refers to place of the letter in the alphabet e.g. 'A'=0. 'n' is a counter, maximum is the total number of occurences
    //Below - these variables will be assigned the new value for the letters in the text. They will be used to replace encrypted letters with new decrypted letters
    int nA, nB, nC, nD, nE, nF, nG, nH, nI, nJ, nK, nL, nM, nN, nO, nP, nQ, nR, nS, nT, nU, nV, nW, nX, nY;
    //Below - these variables keep track of the position of letters that have already been assigned a new value after the for loop. This will avoid any letters being found as the greatest more than once
    int n1, n2, n3 , n4 , n5 , n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16, n17, n18, n19, n20, n21, n22, n23, n24, n25;
    //These for loops assign the most common letter the most probable decrypted letter. For each loop, the previous greatest values cannot be chosen, so the new greatest value is always the next greatest compared to the previous one
    for(n = 0; n < 26; n++) {                          //This loop runs through all the variables of the array and finds the most frequent letter and the number of times it occured
        if(letters26[n] > maximum) {                   //If the frequency of a letter is greater than the others so far. This condition finds the greatest letter
            location = n;
            n1 = n;
            maximum = letters26[n];
        }
    }

    nE = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters25[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters25[n] > maximum && n != n1) {        //This added condition %% n != n1 means that the greatest cannot be the same as the previous loop, so the second greatest can be found
            location = n;
            n2 = n;
            maximum = letters25[n];
        }
    }

    nT = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters24[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters24[n] > maximum && n != n1 && n != n2) {
            location = n;
            n3 = n;
            maximum = letters24[n];
        }
    }
    
    nA = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters23[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters23[n] > maximum && n != n1 && n != n2 && n != n3) {
            location = n;
            n4 = n;
            maximum = letters23[n];
        }
    }
    
    nO = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters22[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters22[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4) {
            location = n;
            n5 = n;
            maximum = letters22[n];
        }
    }
    
    nI = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters21[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters21[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5) {
            location = n;
            n6 = n;
            maximum = letters21[n];
        }
    }
    
    nN = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters20[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters20[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6) {
            location = n;
            n7 = n;
            maximum = letters20[n];
        }
    }
    
    nS = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters19[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters19[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7) {
            location = n;
            n8 = n;
            maximum = letters19[n];
        }
    }
    
    nR = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters18[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters18[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8) {
            location = n;
            n9 = n;
            maximum = letters18[n];
        }
    }
    
    nH = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters17[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters17[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9) {
            location = n;
            n10 = n;
            maximum = letters17[n];
        }
    }
    
    nL = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters16[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters16[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10) {
            location = n;
            n11 = n;
            maximum = letters16[n];
        }
    }
    
    nD = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters15[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          //This loop runs through all the variables of the array and finds the most frequent letter and the number of times it occured
        if(letters15[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11) {
            location = n;
            n12 = n;
            maximum = letters15[n];
        }
    }
    
    nC = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters14[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters14[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12) {
            location = n;
            n13 = n;
            maximum = letters14[n];
        }
    }
    
    nU = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters13[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters13[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13) {
            location = n;
            n14 = n;
            maximum = letters13[n];
        }
    }
    
    nM = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters12[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters12[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14) {
            location = n;
            n15 = n;
            maximum = letters12[n];
        }
    }
    
    nF = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters11[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters11[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15) {
            location = n;
            n16 = n;
            maximum = letters11[n];
        }
    }
    
    nP = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters10[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters10[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15 && n != n16) {
            location = n;
            n17 = n;
            maximum = letters10[n];
        }
    }
    
    nG = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters9[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters9[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15 && n != n16 && n != n17) {
            location = n;
            n18 = n;
            maximum = letters9[n];
        }
    }
    
    nW = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters8[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters8[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15 && n != n16 && n != n17 && n != n18) {
            location = n;
            n19 = n;
            maximum = letters8[n];
        }
    }
    
    nY = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters7[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters7[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15 && n != n16 && n != n17 && n != n18 && n != n19) {
            location = n;
            n20 = n;
            maximum = letters7[n];
        }
    }
    
    nB = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters6[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                         
        if(letters6[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15 && n != n16 && n != n17 && n != n18 && n != n19 && n != n20) {
            location = n;
            n21 = n;
            maximum = letters6[n];
        }
    }
    
    nV = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters5[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters5[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15 && n != n16 && n != n17 && n != n18 && n != n19 && n != n20 && n != n21) {
            location = n;
            n22 = n;
            maximum = letters5[n];
        }
    }
    
    nK = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters4[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters4[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15 && n != n16 && n != n17 && n != n18 && n != n19 && n != n20 && n != n21 && n != n22) {
            location = n;
            n23 = n;
            maximum = letters4[n];
        }
    }
    
    nX = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters3[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters3[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15 && n != n16 && n != n17 && n != n18 && n != n19 && n != n20 && n != n21 && n != n22 && n != n23) {
            location = n;
            n24 = n;
            maximum = letters3[n];
        }
    }
    
    nJ = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters2[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters2[n] > maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15 && n != n16 && n != n17 && n != n18 && n != n19 && n != n20 && n != n21 && n != n22 && n != n23 && n != n24) {
            location = n;
            n25 = n;
            maximum = letters2[n];
        }
    }
    
    nQ = 65 + location;                                //New value for most common letter that has not already been found
    maximum = 0;                                       //Maximum set back to 0
    int letters1[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
        for(n = 0; n < 26; n++) {                          
        if(letters1[n] >= maximum && n != n1 && n != n2 && n != n3 && n != n4 && n != n5 && n != n6 && n != n7 && n != n8 && n != n9 && n != n10 && n != n11 && n != n12 && n != n13 && n != n14 && n != n15 && n != n16 && n != n17 && n != n18 && n != n19 && n != n20 && n != n21 && n != n22 && n != n23 && n != n24 && n != n25) {
            location = n;
            maximum = letters1[n];
        }
    }
    
    Z = 65 + location;                                 //New value for most common letter that has not already been found
    fseek(input, 386, 0);                              //Jumps back to the start of the given encrypted text
    while(!feof(input)) {                              //This loop assigns each letter its new letter according to statistical probablity. Ouput is printed to the console and the output file. The loop ends when the end of the file is reached (feof(input) will equal 1)
        fscanf(input, "%c", &c);
        if(c == nE) {
            printf("E");
            fprintf(output, "E");
        } else if(c == nT) {
            printf("T");
            fprintf(output, "T");
        } else if(c == nA) {
            printf("A");
            fprintf(output, "A");
        } else if(c == nO) {
            printf("O");
            fprintf(output, "O");
        } else if(c == nI) {
            printf("I");
            fprintf(output, "I");
        } else if(c == nN) {
            printf("N");
            fprintf(output, "N");
        } else if(c == nS) {
            printf("S");
            fprintf(output, "S");
        } else if(c == nR) {
            printf("R");
            fprintf(output, "R");
        } else if(c == nH) {
            printf("H");
            fprintf(output, "H");
        } else if(c == nL) {
            printf("L");
            fprintf(output, "L");
        } else if(c == nD) {
            printf("D");
            fprintf(output, "D");
        } else if(c == nC) {
            printf("C");
            fprintf(output, "C");
        } else if(c == nU) {
            printf("U");
            fprintf(output, "U");
        } else if(c == nM) {
            printf("M");
            fprintf(output, "M");
        } else if(c == nF) {
            printf("F");
            fprintf(output, "F");
        } else if(c == nP) {
            printf("P");
            fprintf(output, "P");
        } else if(c == nG) {
            printf("G");
            fprintf(output, "G");
        } else if(c == nW) {
            printf("W");
            fprintf(output, "W");
        } else if(c == nY) {
            printf("Y");
            fprintf(output, "Y");
        } else if(c == nB) {
            printf("B");
            fprintf(output, "B");
        } else if(c == nV) {
            printf("V");
            fprintf(output, "V");
        } else if(c == nK) {
            printf("K");
            fprintf(output, "K");
        } else if(c == nX) {
            printf("X");
            fprintf(output, "X");
        } else if(c == nJ) {
            printf("J");
            fprintf(output, "J");
        } else if(c == nQ) {
            printf("Q");
            fprintf(output, "Q");
        } else if(c == Z) {
            printf("Z");
            fprintf(output, "Z");
        } else {                                       //If the character is not a letter e.g. c == '!' or '?' or ',' etc... Print it
            printf("%c", c);
            fprintf(output, "%c", c);
        }
    }
    
    fclose(input);                                     //Closes the input file
    fclose(output);                                    //Closes the output file
    return;
}

