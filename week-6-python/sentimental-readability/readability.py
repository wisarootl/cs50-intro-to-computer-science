from cs50 import get_string


def count_letters(text: str):
    return sum(1 for i in range(len(text)) if text[i].isalpha())


def count_words(text: str):
    return sum(1 for i in range(len(text)) if text[i] == ' ') + 1


def count_sentences(text: str):
    end = ['?', '.', '!']
    return sum(1 for i in range(len(text)) if text[i] in end)


def get_readability_index(letters_count, words_count, sentences_count):

    conversion_to_per_100_words = 100 / words_count
    L = letters_count * conversion_to_per_100_words
    S = sentences_count * conversion_to_per_100_words

    return round(0.0588 * L - 0.296 * S - 15.8)


def print_grade(readability_index):
    if readability_index < 1:
        print("Before Grade 1")
    elif readability_index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {readability_index}")


if __name__ == "__main__":
    text = get_string("Text: ")

    letters_count = count_letters(text)
    words_count = count_words(text)
    sentences_count = count_sentences(text)

    readability_index = get_readability_index(letters_count, words_count, sentences_count)

    print_grade(readability_index)