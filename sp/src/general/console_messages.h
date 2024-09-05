// ----------------------------------------------------------------------------------------
// Code written by Gareth Pugh, sourced from https://cplusplus.com/reference/cstdio/printf/
// ----------------------------------------------------------------------------------------
// The following code will demonstrate how to output a variable to the developer console.
// ----------------------------------------------------------------------------------------

#ifndef CONSOLE_MESSAGES_H
#define CONSOLE_MESSAGES_H

#include "cbase.h" // Needed for the Msg command to work.

// ------------------------------
// Here are some stock variables.
// ------------------------------
int negative = -8192; // Signed integer, can be negative. Can also use the keyword unsigned, which creates an integer that cannot be negative.
unsigned int decimal = 32; // Decimal integer, base 10.
unsigned int octal = 032; // Octaldecimal integer, base 8. 032 = 26 in decimal.
unsigned int hexa = 0x3B; // Hexadecimal integer, base 16. 0x3B = 59 in decimal.
float f = 420.69f; // Floating point number.
const char* string = "Sample text."; // Strings in the Source engine need to be defined as a const char* (most of the time).

// ----------------------------------------------------------------------------
// Include this file somewhere by doing #include "console_messages.h" and
// call the function below to print some information about the above variables!
// ----------------------------------------------------------------------------
void PrintRandomVariables(void)
{
// ----------------------------------------------------------------------
// This is how you would output these variables to the developer console.
// ----------------------------------------------------------------------
	Msg("Signed integer = %i\n", negative); // Can use %i or %d.
	Msg("Unsigned integer = %u\n", decimal);
	Msg("Octal integer = %#o\n", octal);
	Msg("Unsigned Hexadecimal integer = %#x\n", hexa); // Can use %x or %X.
	Msg("Floating point decimal = %f\n", f); // Can use %f or %F, %.<i>f to specify precision i.e. %.3f for 3 decimal places.
	Msg("Scientific notation = %e\n", f); // Can use %e or %E.
	Msg("Hexadecimal floating point = %a\n", f); // Can use %a or %A.
	Msg("Character = %c\n", string[0]); // Array indexing of a string to acquire a char.
	Msg("String = %s\n", string);
	Msg("Pointer address = %p\nand %p\nand %p\nand %p\nand %p\nand %p\n", negative, decimal, octal, hexa, f, string); // Memory address shenanigans!
	Msg("I'm feeling 100%% right around now!\n"); // Printing the % symbol to the developer console.
}

// You can also have length sub-specifiers, for example:
// %llu for an unsigned long long aka an unsigned 64-bit integer aka a uint64,
// or %#x to put 0x/0 in front of a hexadecimal/octaldecimal value, respectively.
#endif // CONSOLE_MESSAGES_H