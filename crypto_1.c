#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// READ ME
// 1. I put most of the choices as 1 or 2 so please only enter them or program will exit.
// 2. Caesar and Vigenere encryption/decryption work perfectly regardless of any other characters or numbers in the text.
// 3. Only put numbers in the key of Caesar and alphabets in the keys of Vigenere and Playfair.
// I didn't put a exit condition there as the program already looks long and naturally the program will fail.
// For Caesar, you can put numbers > 26, as I put a mod26 anyway.
// For Vigenere & Playfair, you can enter uppercase or lowercase, the program will convert them to upper anyway.
// 4. Any text which is to be encoded or decoded must be stored in the process.txt file.
// The messages from the assignment are stored in caesar.txt and vigenere.txt.

// 5. Caesar Cryptanalysis is currently programmed to compare the highest occuring alphabet with 'E' and shift it back.
// It was a bit hard to add substring matching or to add the feature choosing the next most occuring key after 'E'.

// 6. Vigenere Cryptanalysis might not work all the time. Currently, it is programmed to choose the highest occuring factor to be the length of the key.
// There needs to be a human checking the most occuring factor and make an intelligent guess as to what the length of the key could be.
// https://pages.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Examples.html <- This site clearly explains how the cryptanalysis might not work with examples.
// https://planetcalc.com/7956/ <- This site also helped in understanding how it worked.

// 7. Obviously, both of the above ciphers might fail if there is not enough data so try to enter a large message.
// 8. Playfair Cipher works good enough but sometimes a character or two are wrong, which we can guess and change.
// The key matrix comes out pretty accurate. J is replaced by I. 
// Remove the extra X's after Decryption. All other characters and numbers are removed before encoding/decoding so add them back accordingly to the result.

// 9. The temp.c was just for breaking the code into parts and doing them individually.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Frequencies of the alphabets
const double alphabet_freq[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, // A,B,C,D,E
                                  0.02228, 0.02015, 0.06094, 0.06996, 0.00153, // F,G,H,I,J
                                  0.00772, 0.04025, 0.02406, 0.06749, 0.07507, // K,L,M,N,O
                                  0.01929, 0.00095, 0.05987, 0.06327, 0.09056, // P,Q,R,S,T
                                  0.02758, 0.00978, 0.02360, 0.00150, 0.01974, // U,V,W,X,Y
                                  0.00074};                                    // Z

//Function to remove any other character in the message which isn't an alphabet and convert the alphabets to uppercase
void text_clean(char text[]){
   for(int i = 0, j; text[i] != '\0'; ++i){
       while(!(text[i] >= 'a' && text[i] <= 'z') && !(text[i] >= 'A' && text[i] <= 'Z') && !(text[i] == '\0')){
           for(j = i; text[j] != '\0'; ++j){
               text[j] = text[j + 1];
            }
         text[j] = '\0';
      }
    }

    for(int i = 0, j; text[i] != '\0'; ++i){
        text[i] = toupper(text[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main Caesar Encryption/Decryption function
void caesar_cipher(char message[], int key, int option){
    if(option == 1){
        if(strlen(message)<500){
            printf("\nYour plaintext:\n%s\n\n", message);
        }
        printf("Your shift: %d\n\n", key);
        printf("Your encoded message: \n");
        for(int i=0; i<strlen(message); i++){
            if(isalpha(message[i])){
                if(islower(message[i])){
                    message[i] = (message[i] + key - 97)%26 + 97;
                }
                else if(isupper(message[i])){
                    message[i] = (message[i] + key - 65)%26 + 65;
                }
            }
        }
    }

    else if(option == 2){
        if(strlen(message)<500){
            printf("\nYour encoded message:\n%s\n\n", message);
        }
        printf("Your shift: %d\n\n", key);
        printf("Your decoded message:\n");
        for(int i=0; i<strlen(message); i++){
            if(isalpha(message[i])){
                if(islower(message[i])){
                    message[i] = (message[i] - key + 26 - 97)%26 + 97;
                }
                else if(isupper(message[i])){
                    message[i] = (message[i] - key + 26 - 65)%26 + 65;
                }
            }
        }
        
    }
    printf("%s", message);
}

//Main Caesar Cryptanalysis using frequency analysis function
void caesar_cryptanalysis(char message[]){
    int crypt_key, i, max_freq = 0;

    int rel_frequency[26] = {0};
    for(int i=0; i<strlen(message); i++){
        if(isalpha(message[i])){
            rel_frequency[toupper(message[i]) - 65]++;
        }
    }

    int temp = -1;

    for (i = 0; i < 26; i++){
        if (temp < rel_frequency[i]){
            temp = rel_frequency[i];
            max_freq = i;
        }
    }

    crypt_key = max_freq - ('E' - 65);
    crypt_key = (max_freq - 'E' + 65)%26;
    caesar_cipher(message, crypt_key, 2);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main Vigenere Encryption/Decryption function
void vigenere_cipher(char message[], char key[], int option){
    int key_length = strlen(key), temp = 0;

    if(option == 1){
        if(strlen(message)<500){
            printf("\nYour plaintext:\n%s\n\n", message);
        }
        printf("Your key: %s\n\n", key);
        printf("Your encoded message: \n");
        for(int i=0; i<strlen(message); i++){
            if(isalpha(message[i])){
                if(islower(message[i])){
                    message[i] = (message[i] + tolower(key[temp%key_length]) - 194)%26 + 97;
                }
                else if(isupper(message[i])){
                    message[i] = (message[i] + toupper(key[temp%key_length]) - 130)%26 + 65;
                }
                temp++;
            }
        }
    }

    else if(option == 2){
        if(strlen(message)<500){
            printf("\nYour encoded message:\n%s\n\n", message);
        }
        printf("Your key: %s\n\n", key);
        printf("Your decoded message: \n");
        for(int i=0; i<strlen(message); i++){
            if(isalpha(message[i])){
                if(islower(message[i])){
                    message[i] = (message[i] - tolower(key[temp%key_length]) + 26)%26 + 97;
                }
                else if(isupper(message[i])){
                    message[i] = (message[i] - toupper(key[temp%key_length]) + 26)%26 + 65;
                }
                temp++;
            }
        }
    }

    printf("%s", message);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Calculate the index of coincidence of each group
int best_match(const double *a, const double *b) {
    double sum = 0, fit, d, best_fit = 1e10;
    int i, rotate, best_rotate = 0;

    //Adding all the frequencies to sum
    for (i = 0; i < 26; i++){
        sum += a[i];
    }

    // Checking Index of coincidences 
    for (rotate = 0; rotate < 26; rotate++) {
        fit = 0;
        for (i = 0; i < 26; i++) {
            d = a[(i + rotate) % 26] / sum - b[i];
            fit += d * d / b[i];
        }
 
        if (fit < best_fit) {
            best_fit = fit;
            best_rotate = rotate;
        }
    }
 
    return best_rotate;
}

//Splits the message into n groups so that characters in the same group would have been enciphered using the same character Of the keyword
//Then, Calculate the average index of coincidence of all groups
double friedman_test(const int *msg, int len, int interval, char *key) {
    double sum_ic, d, ret;
    double out[26], accu[26] = {0};
    int i, j, rot;
 
    for (j = 0; j < interval; j++) {
        for (i = 0; i < 26; i++){
            out[i] = 0;
        }
        // Frequencies of alphabets
        for (i = j; i < len; i += interval){
            out[msg[i]]++;
        }
        key[j] = rot = best_match(out, alphabet_freq);
        key[j] += 'A';
        for (i = 0; i < 26; i++){
            accu[i] += out[(i + rot) % 26];
        }         
    }
 
    for (i = 0, sum_ic = 0; i < 26; i++)
        sum_ic += accu[i];
 
    for (i = 0, ret = 0; i < 26; i++) {
        d = accu[i] / sum_ic - alphabet_freq[i];
        ret += d * d / alphabet_freq[i];
    }
 
    key[interval] = '\0';
    return ret;
}

//Main Vigenere Cryptanalysis using Friedman Test function
void vigenere_cryptanalysis_friedman(char message[]){
    int i, j = 0;
    char alpha_message[2000] = "";
    for(i=0; message[i] != '\0'; i++){
        if(isalpha(message[i])){
            alpha_message[j++] = message[i];
        }
    }
    char vigenere_final_key[50] = "";

    int num_message[strlen(alpha_message)];
    int len = 0;
    char key[50];
    double fit, best_fit = 1e10;
    

    for (j = 0; j<strlen(alpha_message); j++){
        if (isupper(alpha_message[j])){
            num_message[len++] = alpha_message[j] - 'A';
        }
        else if (isupper(alpha_message[j])){
            num_message[len++] = alpha_message[j] - 'a';
        }
    }

    // Assume key length = 2
    for (j = 2; j < 25; j++) {
        fit = friedman_test(num_message, len, j, key);

        if (fit < best_fit) {
            best_fit = fit;
            strcpy(vigenere_final_key,key);
        }
    }
    printf("The key obtained from cryptanalysis : %s\n", vigenere_final_key);

    vigenere_cipher(message, vigenere_final_key, 2);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to do frequency analysis on a text i.e. for an n-length key, we perform frequency analysis on the group of every nth letter
void vigenere_freqanalysis(char message[],char finalkey[], int keylength){
    int i,j, max, max_freq = 0;

    for(i=0; i<keylength;i++){
        int rel_frequency[26] = {0};
        max = -1;
        for(j=i;j<strlen(message); j=j+keylength){
            rel_frequency[message[j] - 65]++;
        }
        for (int x = 0; x < 26; x++){
            if (max < rel_frequency[x]){
                max = rel_frequency[x];
                max_freq = x;
            }
        }
        finalkey[i] = (max_freq - 'E' + 65)%26 + 65;
    }
    finalkey[i] = '\0';
}

//Function to find all factors of the number i.e distance b/w the sequences
void factorize(int factors[], int distance){
    for(int i = 2; i<=distance; i++){
        if(distance%i ==0){
            factors[i]++;
        }
    }
}

//Function to find the repeated sequences and the distances between them
void repeated_sequence(char message[], char repeating_key[],int factors[], int position){
    int messageindex, keyindex, curr_size;
    int keylength = strlen(repeating_key);
    int distance;

    for(messageindex=position+keylength; messageindex<strlen(message);){
        keyindex = 0;
        curr_size = 0;
        distance++;
        while(message[messageindex] == repeating_key[keyindex] && message[messageindex] != '\0'){
            curr_size++;
            messageindex++;
            keyindex++;
        }
        if(keylength == curr_size){
            distance = messageindex-(position+keylength);
            factorize(factors, distance);
        }
        else{
            messageindex++;
        }
    }
}

//Main Vigenere Cryptanalysis using Kasiski examination function
void vigenere_cryptanalysis(char message[]){
    text_clean(message);
    message[strlen(message)] = '\0';
    int length = strlen(message);
    int possible_keylen = 3;
    int position, keyposition, max = -1, probable_key_length;
    int factors[length];

    for(int temp=0;temp<length;temp++){
        factors[temp]=0;
    }

    while(possible_keylen <= 25){
        if(length<possible_keylen){
            break;
        }
        char repeating_key[possible_keylen];
        for(position=0; position<length-possible_keylen+1; position++){
            for(keyposition=0;keyposition<possible_keylen;keyposition++){
                repeating_key[keyposition] = message[position+keyposition];
            }
            repeating_key[keyposition] = '\0';
            repeated_sequence(message, repeating_key, factors, position);
        }
        possible_keylen++;
    }

    for(int temp=2;temp<length;temp++){
        if(factors[temp] > max){
            max = factors[temp];
            probable_key_length = temp;
        }
    }

    probable_key_length = 5;
    char finalkey[probable_key_length];
    vigenere_freqanalysis(message, finalkey,probable_key_length);

    printf("The key obtained from cryptanalysis : %s\n", finalkey);
    vigenere_cipher(message,finalkey,2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Deleting any duplicates from any text, but here, the playfair key
void delete_duplicates(char key[]){
    int i, j, k = 0, c ='*';

    for(i = 0; i<strlen(key); i++){
        if(key[i] == 'J'){
            key[i] = 'I';
        }
    }

    for(i=0;key[i];i++){
        if(!(key[i] == c)){
            for(j=i+1;key[j];j++){
                if(key[i] == key[j]){
                    key[j] = c;
                }
            }
        }
    }

    for(i=0;key[i];i++){
        key[i] = key[i+k];
        if(key[i] == c){
            k++;
            i--;
        }
    }
}

//Making the Playfair Key Matrix
void playfair_matrix(char key_matrix[5][5], char key[], char final_key[]){
    int i, j, tempcheck[26] = {0}, keylen = strlen(key), templen = 0;
    char tempalpha[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for(i = 0; i<keylen; i++){
        final_key[i] = key[i];
        tempcheck[key[i] - 65]++;
    }

    strcat(final_key,tempalpha);
    delete_duplicates(final_key);
    for(i = 0; i<5; i++){
        for(j = 0; j<5;j++){
            key_matrix[i][j] = final_key[templen++];
        }
    }
}

//Encryption of text using Playfair Cipher
void playfair_encrypt(char letter1, char letter2, char key_matrix[5][5]){
    
    int i, j, w, x, y, z;
    for (i = 0; i < 5; i++) {  
        for (j = 0; j < 5; j++) {  
            if (letter1 == key_matrix[i][j]) {  
                w = i;  
                x = j;  
            } else if (letter2 == key_matrix[i][j]) {  
                y = i;  
                z = j;  
            }  
        }
    }
    
    if (w == y){  
        x = (x + 1) % 5;  
        z = (z + 1) % 5;  
        printf("%c%c", key_matrix[w][x], key_matrix[y][z]);    
    } else if (x == z) {  
        w = (w + 1) % 5;  
        y = (y + 1) % 5;  
        printf("%c%c", key_matrix[w][x], key_matrix[y][z]);   
    } else {  
        printf("%c%c", key_matrix[w][z], key_matrix[y][x]);  
    }
}

//Decryption of text using Playfair Cipher
void playfair_decrypt(char letter1, char letter2, char key_matrix[5][5]){
    int i, j, w, x, y, z;
    for (i = 0; i < 5; i++) {  
        for (j = 0; j < 5; j++) {  
            if (letter1 == key_matrix[i][j]) {  
                w = i;  
                x = j;  
            } else if (letter2 == key_matrix[i][j]) {  
                y = i;  
                z = j;  
            }  
        }
    }
    
    if (w == y){  
        x = (x - 1) % 5;  
        z = (z - 1) % 5;  
        printf("%c%c", key_matrix[w][x], key_matrix[y][z]);    
    } else if (x == z) {  
        w = (w - 1) % 5;  
        y = (y - 1) % 5;  
        printf("%c%c", key_matrix[w][x], key_matrix[y][z]);   
    } else {  
        printf("%c%c", key_matrix[w][z], key_matrix[y][x]);  
    }
}

//Main Playfair function
void playfair_cipher(char message[], char key[], int option){
    char key_matrix[5][5], final_key[26] = "";

    if(strlen(message)<500){
        printf("\nYour encoded/decoded message:\n%s\n\n", message);
    }

    printf("The playfair matrix for the key, %s, is:\n", key);
    text_clean(message);
    text_clean(key);
    delete_duplicates(key);
    playfair_matrix(key_matrix, key, final_key);

    //Printing the key matrix
    for(int i=0;i<5;i++){
        for(int j=0; j<5;j++){
            printf("%c ", key_matrix[i][j]);
        }
        printf("\n");
    }

    //Encoding or Decoding the text
    printf("\n");
    if(option == 1){
        printf("Your encoded message: \n");
        for (int i = 0; i < strlen(message); i++) {   
            if (message[i + 1] == '\0') playfair_encrypt(message[i], 'X', key_matrix);  
            else {   
                if (message[i] == message[i + 1]) playfair_encrypt(message[i], 'X', key_matrix);  
                else {  
                    playfair_encrypt(message[i], message[i + 1], key_matrix);  
                    i++;  
                }  
            }
        }
    }

    if(option == 2){
        printf("Your decoded message: \n");
        for(int i = 0; i < strlen(message); i++){   
            playfair_decrypt(message[i], message[i + 1], key_matrix);
            i++;
        }  
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main Program
int main(){
    // All the variables declared and initialized
    int cipher_choice = 0, enc_choice = 0, dec_choice = 0, vigenere_crypt_choice = 0,caesar_key = 0, length = 0;
    char curr, message[2000], vigenere_key[50], playfair_key[50];

    //Starting timer
    clock_t start, end;
    double total_time;
    start = clock();

    // File Procesing
    FILE *fptr;
    if((fptr = fopen("process.txt","r")) == NULL){
        printf("Error! File not found!");   
        exit(1);
        }

    //Processing file data into an array
    int message_freq[26] = {0};
    rewind(fptr);
    while ((curr = fgetc(fptr)) != EOF){
        message[length++] = curr;
    }

    fclose(fptr);

    // Taking the choice for encryption routine
    printf("\n----------------------------------------------------------------\n");
    printf("\nWelcome!\nWhich encryption routine would you like to use? (Enter 1, 2 or 3)\n\n");
    printf("1. Caesar Cipher\n2. Vigenère Cipher\n3. Playfair Cipher\n");
    scanf("%d", &cipher_choice);

    // Choose Encyption or Decryption
    printf("\nWould you like to Encrypt(1) or Decrypt(2) the text? (Enter 1 or 2) -- ");
    scanf("%d", &enc_choice);

    switch(cipher_choice){
        case 1:
            printf("\nYou are using Caesar Cipher to ");
            break;
        case 2:
            printf("\nYou are using Vigenère Cipher to ");
            break;
        case 3:
            printf("\nYou are using Playfair Cipher to ");
            break;
        default:
            printf("\nYou chose an invalid cipher option! Exiting...\n");
            printf("----------------------------------------------------------------\n");
            exit(1);
    }

    switch(enc_choice){
        case 1:
            printf("encrypt the text.\nStarting Encryption process...\n");
            break;
        case 2:
            printf("decrypt the text.\nStarting Decryption process...\n");
            break;
        default:
            printf("\nYou chose an invalid process option! Exiting...\n");
            printf("----------------------------------------------------------------\n");
            exit(1);
    }

    if(enc_choice == 2){
        //Choose user-input decryption or cryptanalysis decryption
        printf("\nWould you like to give the key to decode(1) or perform a cipher-text only attack i.e. cryptanalysis technique(2)? (Enter 1 or 2)  -- ");
        scanf("%d", &dec_choice);
        switch(dec_choice){
            case 1:
                printf("You chose to decrypt the text with user-input key.\n");
                break;
            case 2:
                printf("You chose to decrypt the text using cryptanalysis techniques.\nIf you chose this for Playfair, it'll take you to user-input anyway. \n");
                break;
            default:
                printf("You chose an invalid decode option! Exiting...\n");
                printf("----------------------------------------------------------------\n");
                exit(1);
        }

    }

    // Caesar cipher encryption/decryption using user-input key & cryptanalysis
    if(cipher_choice == 1){
        if(enc_choice == 2 && dec_choice == 2){
            caesar_cryptanalysis(message);
        }
        else{
            printf("\nEnter the key(shift) for Caesar Cipher - ");
            scanf("%d",&caesar_key);
            caesar_key = caesar_key%26;
            caesar_cipher(message, caesar_key, enc_choice);
        }
    }

    // Vigenere cipher encryption/decryption using user-input key & cryptanalysis
    if(cipher_choice == 2){
        if(enc_choice == 2 && dec_choice == 2){
            printf("Would you like to perform the Kasiski Examination(1) or the Friedman Test(2)? (Enter 1 or 2)  -- ");
            scanf("%d",&vigenere_crypt_choice);
            switch(vigenere_crypt_choice){
                case 1:
                    printf("You chose Kasiski Examination! Starting the process...\n");
                    message[strlen(message)] = '\0';
                    vigenere_cryptanalysis(message);
                    break;
                case 2:
                    printf("You chose Friedman Test! Starting the process...\n");
                    vigenere_cryptanalysis_friedman(message);
                    break;
                default:
                    printf("You chose an invalid decode option! Exiting...\n");
                    printf("----------------------------------------------------------------\n");
                    exit(1);
            }
        }
        else{
            printf("\nEnter the key for Vigenere Cipher - ");
            scanf("%s",vigenere_key);
            vigenere_cipher(message, vigenere_key, enc_choice);
        }
    }

    // Playfair cipher encryption/decryption using user-input key
    if(cipher_choice == 3){
        printf("\nEnter the key for Playfair Cipher - ");
        scanf("%s", playfair_key);
        playfair_cipher(message, playfair_key, enc_choice);
    }

    //End of timer and program
    end = clock();
    total_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\n\nTotal execution time was %f seconds.", total_time);
    printf("\n----------------------------------------------------------------\n");
    return 0;

}