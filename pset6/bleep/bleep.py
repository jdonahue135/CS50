from cs50 import get_string
import sys


def main():

    # Accepts only one command line argument
    if len(sys.argv) != 2:
        sys.exit("Usage: python bleep.py dictionary")
        exit(1)

    # load dictionary into memory
    banned = set()
    dictionary = sys.argv[1]
    file = open(dictionary, "r")
    for line in file:
        banned.add(line.rstrip("\n"))
    file.close()

    # prompts user for message
    m = get_string("What message would you like to censor?\n")

    # splits string into individual words
    words = m.split()

    # checks if words are banned
    for word in words:
        if(word.isalpha()) == True:
            if(word.islower()) == True:
                if word in banned:
                    print("*" * len(word), end=" ")
                else:
                    print(word, end=" ")
            else:
                new_word = word.lower()
                if new_word in banned:
                    print("*" * len(word), end=" ")
                else:
                    print(word, end=" ")
    print()


if __name__ == "__main__":
    main()
