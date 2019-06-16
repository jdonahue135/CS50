import sys
from cs50 import get_string


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python caesar.py k")

    # prompt user for plaintext
    plaintext = get_string("plaintext: ")
    print("ciphertext: ", end="")

    # gets key
    k = int(sys.argv[1]) % 26

    # iterates over characters in plaintext with key
    for c in plaintext:
        if(c.isalpha()) == True:
            if(c.isupper()) == True:
                x = ord(c) + k
                if x > 90:
                    x -= 26
                x = chr(x)
                print(x, end="")
            else:
                x = ord(c) + k
                if x > 122:
                    x -= 26
                x = chr(x)
                print(x, end="")
        else:
            print(c, end="")
    print()


# calls main
if __name__ == "__main__":
    main()