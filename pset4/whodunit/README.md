# Questions

## What's `stdint.h`?

Library of BMP-related data types based on Microsoft's own.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

They define the size of and if the first bit is signed/unsigned of a data type.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE: 1, DWORD: 4, LONG: 4, WORD: 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM.

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of a file, biSize is the size of a structure

## What does it mean if `biHeight` is negative?

the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The file specified in command line argument does not exist in that location

## Why is the third argument to `fread` always `1` in our code?

We want our program to only read the headers in the file, if it were more it would start reading the bitmap, and less would not read enough.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Allows you to change the position of a file pointer

## What is `SEEK_CUR`?

Where we are changing the position of a file pointer from. It means the current location

## Whodunit?

It was professor plum with the candlestick in the library
