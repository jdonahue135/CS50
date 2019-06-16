import sys
from cs50 import get_float


def main():

    # prompt user for amount owed
    while True:
        n = get_float("change owed: ")
        if n > 0:
            break

    # calculate minimum number of coins
    n = n * 100
    coins = 0
    while n >= 25:
        n -= 25
        coins += 1
    while n >= 10:
        n -= 10
        coins += 1
    while n >= 5:
        n -= 5
        coins += 1
    while n >= 1:
        n -= 1
        coins += 1

    # print number of coins
    print(coins)


# calls main
if __name__ == "__main__":
    main()