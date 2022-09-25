#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int get_readability_index(int letters, int words, int sentences);


int main(void)
{
    string text = get_string("Text: ");
    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);
    int index = get_readability_index(letter_count, word_count, sentence_count);
    printf("\n");

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}


int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
        if (isalpha(text[i]))
        {
            count ++;
        }
    return count;
}

int count_words(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // check current char and the next char
        // 39 = '
        // 45 = -
        bool is_apostrophe = text[i] == 39 && isalpha(text[i - 1]);
        bool is_hyphen = text[i] == 45 && isalpha(text[i - 1]);
        bool is_not_alphabet = !isalpha(text[i]) && isalpha(text[i - 1]);

        if (is_apostrophe || is_hyphen)
        {
            continue;
        }
        else if (is_not_alphabet)
        {
            count ++;
        }
    }
    return count;
}


int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int character = text[i];
        // 46 = .
        // 33 = !
        // 63 = ?
        if (character == 46 || character == 33 || character == 63)
        {
            count ++;
        }
    }
    return count;
}

int get_readability_index(int letter_count, int word_count, int sentence_count)
{
    float conversion_to_per_100_words = 100.0 / word_count;
    float L = letter_count * conversion_to_per_100_words;
    float S = sentence_count * conversion_to_per_100_words;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}