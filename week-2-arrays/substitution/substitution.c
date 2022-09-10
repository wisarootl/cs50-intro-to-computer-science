#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int is_valid_argument(int argc, string key[]);
int encrypt(string text, string key);


int main(int argc, string argv[])
{
    if (!is_valid_argument(argc, argv))
    {
        return 1;
    }
    string key = argv[1];
    string plaintext = get_string("plaintext: ");
    return encrypt(plaintext, key);

}


int is_valid_argument(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return false;
    }
    else if (strlen(argv[1]) != 26)
    {

        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        char i_char = argv[1][i];
        if (!isalpha(i_char))
        {
            printf("Key must contain only alphabetic characters.\n");
            return false;
        }
        for (int j = 0; j < n; j++)
        {
            char j_char = argv[1][j];
            if (toupper(i_char) == toupper(j_char) && i != j)
            {
                printf("Key must not contain repeated characters.\n");
                return false;
            }
        }
    }

    return true;
}


int encrypt(string plaintext, string key)
{
    int index;
    string ciphertext = plaintext;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            index = (int) plaintext[i];
            if (index >= 65 && index <= 90)
            {
                index -= 65;
                ciphertext[i] = toupper(key[index]);
            }
            else
            {
                index -= 97;
                ciphertext[i] = tolower(key[index]);
            }
        }
    }
    printf("ciphertext: %s", ciphertext);
    printf("\n");
    return 0;
}