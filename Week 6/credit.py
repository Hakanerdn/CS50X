from cs50 import get_int

def main():
    # Initialize variables
    sum_of_double_odds = 0
    sum_of_evens = 0

    # Get the credit card number from the user
    cc_number = get_int("Number: ")

    # Convert the credit card number to a string to calculate its length
    cc_str = str(cc_number)
    num_digits = len(cc_str)

    # Loop through the digits of the credit card number
    for i in range(num_digits):
        # Extract the digit from the right
        digit = int(cc_str[num_digits - 1 - i])

        if i % 2 == 1:
            # Double every other digit starting from the right
            multiple = 2 * digit
            sum_of_double_odds += (multiple // 10) + (multiple % 10)
        else:
            # Sum the remaining digits
            sum_of_evens += digit

    # Check if the credit card number is valid
    is_valid = (sum_of_evens + sum_of_double_odds) % 10 == 0

    # Extract the first two digits for further validation
    first_two_digits = int(cc_str[:2])

    # Determine the card issuer and print the result
    if cc_str[0] == '4' and (num_digits == 13 or num_digits == 16) and is_valid:
        print("VISA")
    elif 51 <= first_two_digits <= 55 and num_digits == 16 and is_valid:
        print("MASTERCARD")
    elif (first_two_digits == 34 or first_two_digits == 37) and num_digits == 15 and is_valid:
        print("AMEX")
    else:
        print("INVALID")

if __name__ == "__main__":
    main()
