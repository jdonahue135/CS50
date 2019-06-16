from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # Split each string into lines
    LinesA = set(a.splitlines())
    LinesB = set(b.splitlines())

    return LinesA & LinesB


def sentences(a, b):
    """Return sentences in both a and b"""

    # Split each string into sentences
    SentencesA = set(sent_tokenize(a))
    SentencesB = set(sent_tokenize(b))

    return SentencesA & SentencesB


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    SubstringsA = substring_divider(a, n)
    SubstringsB = substring_divider(b, n)

    identical_substrings = set()
    for substring in SubstringsA:
        if substring == substring in SubstringsB:
            identical_substrings.add(substring)

    return identical_substrings


def substring_divider(s, n):
    """returns list of substrings of a certain length using recursion"""

    substrings = set()
    while(True):
        if len(s) < n:
            break
        else:
            substring = s[0:(n)]
            substrings.add(substring)
            s = s[1:]
    return substrings