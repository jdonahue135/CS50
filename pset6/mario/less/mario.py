import sys
from cs50 import get_int


def main():

    # prompt user for height
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break

    # build pyramid
    for i in range(n):
        for j in range(n - 1 - i):
            print(" ", end="")
        for k in range(i + 1):
            print("#", end="")
        print()


# calls main
if __name__ == "__main__":
    main()