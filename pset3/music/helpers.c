// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = fraction[0] - 48; //changes ASCII to number
    int denominator = fraction[2] - 48; //changes ASCII to number
    //returns int of eigth notes
    if (denominator == 8)
    {
        return numerator;
    }
    else if (denominator == 4)
    {
        return numerator * 2;
    }
    else
    {
        return numerator * 4;
    }
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int letter;
    int octave;
    int accidental;
    int n;
    //if format is XY
    if (strlen(note) <= 2)
    {
        letter = note[0];
        octave = note[1] - 4 - 48; //changes ASCII to number and sets octave 4 as "0"
        //assigns value to n as distance from Octave 4
        n = octave * 12;
        //assigns value to n as distance from note "A"
        if (letter == 'A')
        {
            n += 0;
        }
        else if (letter == 'B')
        {
            n += 2;
        }
        else if (letter == 'C')
        {
            n -= 9;
        }
        else if (letter == 'D')
        {
            n -= 7;
        }
        else if (letter == 'E')
        {
            n -= 5;
        }
        else if (letter == 'F')
        {
            n -= 4;
        }
        else if (letter == 'G')
        {
            n -= 2;
        }
    }
    //If format is XYZ
    else
    {
        letter = note[0];
        octave = note[2] - 4 - 48; //changes ASCII to number and sets octave 4 as "0"
        n = octave * 12;
        accidental = note[1];
        //assigns value to distance from note "A"
        if (letter == 'A')
        {
            n += 0;
        }
        else if (letter == 'B')
        {
            n += 2;
        }
        else if (letter == 'C')
        {
            n -= 9;
        }
        else if (letter == 'D')
        {
            n -= 7;
        }
        else if (letter == 'E')
        {
            n -= 5;
        }
        else if (letter == 'F')
        {
            n -= 4;
        }
        else if (letter == 'G')
        {
            n -= 2;
        }
        //applies accidental value to distance from A4
        if (accidental == 98)
        {
            n -= 1;
        }
        if (accidental == 35)
        {
            n += 1;
        }
    }
    //Calculates HZ
    return round(pow(2, n / 12.0) * 440);
}
// Determines whether a string represents a rest
bool is_rest(string s)
{
    //compares 2 strings
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
