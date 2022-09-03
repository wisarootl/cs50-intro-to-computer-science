#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long cc_number = get_long_long("Number: ");
    int digit = 0, second_digit = 0, num_digits = 0, sum_of_double_odds = 0, sum_of_evens = 0;

    while (cc_number > 0)
    {
        second_digit = digit;
        digit = cc_number % 10;

        if (num_digits % 2 == 0)
        {
            sum_of_evens += digit;
        }
        else
        {
            int multiple = 2 * digit;
            sum_of_double_odds += (multiple / 10) + (multiple % 10);
        }

        cc_number /= 10;
        num_digits++;
    }

    // digit after exiting the loop will be the first digit
    int first_digit = digit;
    bool is_valid = (sum_of_evens + sum_of_double_odds) % 10 == 0;
    int first_two_digits = (first_digit * 10) + second_digit;

    if (first_digit== 4 && num_digits >= 13 && num_digits <= 16 && is_valid)
    {
        printf("VISA\n");
    }
    else if (first_two_digits >= 51 && first_two_digits <= 55 && num_digits == 16 && is_valid)
    {
        printf("MASTERCARD\n");
    }
    else if ((first_two_digits == 34 || first_two_digits == 37) && num_digits == 15 && is_valid)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}