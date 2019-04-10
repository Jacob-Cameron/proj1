#include <stdio.h>
#include <stdlib.h>

void letters(char *x, int N);

int main() {
    
    char alphabet[26]; //Array containing 26 elements to be set as the letters of the alphabet
    letters(alphabet, 26); //Setting elements to ASCII numbers for letters
    int a = 11; //number of letters including spaces
    char text[a];
    sprintf(text, "HELLO WORLD"); //creates a string with elements as the letters
    
//    for(int i = 0; i <26; i++) {
//    printf("%c\n", alphabet[i]); //Print the alphabet by converting ASCII numbers to their respective letters
//    }
//    
//    for(int i = 0; i<5; i++){
//        printf("%d\n", text[i]);
//    }
    
    for(int i = 0; i<a; i++){
        if(text[i]==32) { //if there is a space ASCII code=32 then print a space
            printf(" ");
        } else { int x = text[i]-65; //if there is a capital letter print it
            printf("%c", alphabet[x]);
        }

    }
    return 0;
    
 }
 
 //would like to create a function that counts the number of letters and spaces in a given text
 
 //Setting alphabet
 void letters(char *x, int N) { //Function to set letters
     int i;
     srand(8);
     int rotation = rand()%26 + 1;
     for(i=0; i<N; i++) {
         x[i]=i+65+rotation; //+65 is used to allow letters to be called with a number[0,25] but calls letter which is n+65. Rotates by random number
         
         if(x[i]>90) { //if letters overflow into other ASCII code then bring it back round to the start of the alphabet
             x[i]=x[i]-26;
         }
         
     }
     
     return;
 }