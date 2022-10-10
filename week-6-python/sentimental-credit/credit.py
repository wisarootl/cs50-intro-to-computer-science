import re


def get_card():
    while True:
        card_number = input("Number: ")
        if card_number.isnumeric():
            break

    return card_number


def get_card_digit_sum(card_number):
    card_digit_sum = 0

    # Reverse str to simplify the for loop
    card_number = card_number[::-1]

    for i in range(len(card_number)):

        # Multiply every other digit by 2, starting with the number’s second-to-last digit
        if i % 2 != 0:
            product = int(card_number[i]) * 2
            card_digit_sum += (product // 10) + (product % 10)

        # Add the sum to the sum of the digits that weren’t multiplied by 2
        else:
            card_digit_sum += int(card_number[i])

    # If the total’s last digit is 0, the number is valid
    return card_digit_sum % 10 == 0


def print_card_type(card_number):

    # start with 34 or 37, length = 15
    is_amex = re.search("^3[47]\d{13}$", card_number)

    # start with 4, lenght is 13 or 16
    is_visa = re.search("^4\d{12}(?:[0-9]{3})?$", card_number)

    # start wtih 51-55, length 16
    is_mastercard = re.search("^5[1-5]\d{14}$", card_number)

    if is_amex:
        print("AMEX")
    elif is_visa:
        print("VISA")
    elif is_mastercard:
        print("MASTERCARD")
    else:
        print("INVALID")


if __name__ == "__main__":
    card_number = get_card()
    card_digit_sum = get_card_digit_sum(card_number)
    if card_digit_sum != 0:
        print_card_type(card_number)
    else:
        print("INVALID")