#include <stdio.h>
#include <cs50.h>
#include <math.h>

void credit(long no);
int main(void)
{
    long no = 0;
    credit(no);
}
void credit(long no)
{
    do
    {
        no = get_long("Enter a credit card number: ");
    } while (no < 0);
    {
        int sum = 0;
        long ck = no;
        int nDigits = floor(log10(ck)) + 1; // 1
        int parity = nDigits % 2;           // 2
        for (int i = nDigits; i >= 0; i--)
        {
            int digit = ck % 10;
            if (i % 2 != parity)
            { // 3
                digit = digit * 2;
            }
            if (digit > 9)
            {
                digit = digit - 9;
            }
            sum = sum + digit;
            ck /= 10;
        }
        if (sum % 10 == 0 && nDigits == 15 && ((floor(no / pow(10, 13)) == 34) || (floor(no / pow(10, 13)) == 37))) // 4
        {
            printf("%s\n", "AMEX");
        }
        else if (sum % 10 == 0 && (nDigits == 13 || nDigits == 16) && ((floor(no / pow(10, 12)) == 4) || (floor(no / pow(10, 15)) == 4))) // 5
        {
            printf("%s\n", "VISA");
        }
        else if (sum % 10 == 0 && nDigits == 16 && ((floor(no / pow(10, 14)) == 51) || (floor(no / pow(10, 14)) == 52) || (floor(no / pow(10, 14)) == 53) || (floor(no / pow(10, 14)) == 54) || (floor(no / pow(10, 14)) == 55))) // 6
        {
            printf("%s\n", "MASTERCARD");
        }
        else
        {
            printf("%s\n", "INVALID");
        }
    }
}