#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COUNT_OF_LETTERS 26 // eng. alphabet
#define KEY_LEN 1024

void msg_show(void);
void fun_fflush_stdin(void);

int main()
{
    char string[1024];
    char ciphertext[1024];
    int key[KEY_LEN];
    int count = 0;
    int ch, j;
    int act;

    msg_show();
    printf("\nDo you wanna encrypt/decrypt? Choose e/d: ");
    act = getchar();
    if (act == 'e')
        goto encryption;
    else if (act == 'd')
        goto decryption;
    else {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }


encryption:
    printf("\nInput a message: ");
    fun_fflush_stdin();
    if (fgets(string, sizeof (string), stdin) == NULL) {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }
    // let's make all letters uppercase
    for (unsigned long i = 0; i < strlen(string) - 1; i++)
        if (string[i] >= 'A' && string[i] <= 'Z')
            continue;
        else if (string[i] >= 'a' && string[i] <= 'z')
            string[i] = (char)((int)string[i] - 32);
        else if (string[i] == ' ')
            continue;
        else {
            printf("Error\n");
            exit(EXIT_FAILURE);
        }
    printf("Now the message looks like this: %s\n", string);

    for (int i = 0; i < KEY_LEN; i++) // delete garbage and make key = 0
        key[i] = 0;

    printf("Input a key: ");
    for (int i = 0; i < KEY_LEN; i++) {
        ch = getchar();
        if (ch == '\n') {
            count = i;
            break;
        }
        else if (ch > '9' || ch < '0') {
            printf("Error\n");
            exit(EXIT_FAILURE);
        }
        else key[i] = ch - '0';
        count = i;
    }
    //printf("Your key: ");
    //for (int i = 0; i < count; i++)
        //printf("%d", key[i]);

    j = 0;
    for (unsigned long i = 0; i < strlen(string) - 1; i++) {
        if (string[i] == ' ') {
            ciphertext[i] = ' ';
            continue;
        }
        ciphertext[i] = (char)((((int)string[i] - 'A' + key[j++]) %
                                        COUNT_OF_LETTERS) + 'A');
        if (j >= count)
            j = 0;
    }
    ciphertext[strlen(string) - 1] = '\0';
    printf("\nCiphertext: %s\n\n", ciphertext);
    goto end;


decryption:
    printf("\nInput a message: ");
    fun_fflush_stdin();
    if (fgets(string, sizeof (string), stdin) == NULL) {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }
    // let's make all letters uppercase
    for (unsigned long i = 0; i < strlen(string) - 1; i++)
        if (string[i] >= 'A' && string[i] <= 'Z')
            continue;
        else if (string[i] >= 'a' && string[i] <= 'z')
            string[i] = (char)((int)string[i] - 32);
        else if (string[i] == ' ')
            continue;
        else {
            printf("Error\n");
            exit(EXIT_FAILURE);
        }
    printf("Now the message looks like this: %s\n", string);

    for (int i = 0; i < KEY_LEN; i++) // delete garbage and make key = 0
        key[i] = 0;

    printf("Input a key: ");
    for (int i = 0; i < KEY_LEN; i++) {
        ch = getchar();
        if (ch == '\n') {
            count = i;
            break;
        }
        else if (ch > '9' || ch < '0') {
            printf("Error\n");
            exit(EXIT_FAILURE);
        }
        else key[i] = ch - '0';
        count = i;
    }
    //printf("Your key: ");
    //for (int i = 0; i < count; i++)
        //printf("%d", key[i]);

    j = 0;
    for (unsigned long i = 0; i < strlen(string) - 1; i++) {
        if (string[i] == ' ') {
            ciphertext[i] = ' ';
            continue;
        }
        ciphertext[i] = (char)((((int)string[i] - 'A' - key[j++] + COUNT_OF_LETTERS) %
                                        COUNT_OF_LETTERS) + 'A');
        if (j >= count)
            j = 0;
    }
    ciphertext[strlen(string) - 1] = '\0';
    printf("\nDecrypted message: %s\n\n", ciphertext);

end:

    return 0;
}


void fun_fflush_stdin(void){
    int c;
    while( (c = getchar()) != 10)
        ;
}

void msg_show(void)
{
    printf("#############################################\n"
           "# The Gronsfeld cipher is a polyalphabetic  #\n"
           "# cipher, a series of Caesar ciphers, where #\n"
           "# the shift is determined by numbers        #\n"
           "# (between 0 and 9). It is similar to the   #\n"
           "# Vigenère cipher, but the key uses digits  #\n"
           "# instead of letters.                       #\n"
           "#############################################\n");
}
