#include <stdlib.h>
#include <string.h>
#include "roman_calc.h"

#include <stdio.h>

static int convertRomanNumeralToInteger(char* romanNumeral);
static int convertRomanCharacter(char romanCharacter);
static void convertIntegerToRomanNumeral(int integer, char* destination);

struct RomanCalculator
{
	char result[10];
};

struct RomanConversionData
{
	int value;
	const char* numeralString;
};

#define NUM_ROMAN_CONVERSION 13

const struct RomanConversionData romanConversionData[NUM_ROMAN_CONVERSION] = 
{
	{1000, "M"},
	{900, "CM"},
	{500, "D"},
	{400, "CD"},
	{100, "C"},
	{90, "XC"},
	{50, "L"},
	{40, "XL"},
	{10, "X"},
	{9, "IX"},
	{5, "V"},
	{4, "IV"},
	{1, "I"}
};

RomanCalculator* roman_calc_create()
{
	RomanCalculator* roman_calc = malloc(sizeof(RomanCalculator));

	return(roman_calc);	
}

void roman_calc_add(RomanCalculator* roman_calc, char* romanOperand1, char* romanOperand2)
{
	int operand1 = convertRomanNumeralToInteger(romanOperand1);
	int operand2 = convertRomanNumeralToInteger(romanOperand2);

	memset(roman_calc->result, 0, 10);

	convertIntegerToRomanNumeral(operand1 + operand2, roman_calc->result);
}

int roman_calc_result_length(RomanCalculator* roman_calc)
{
	if(roman_calc->result != NULL)
	{
		return strlen(roman_calc->result);
	}
	return 0;	
}

char* roman_calc_result(RomanCalculator* roman_calc)
{
	return roman_calc->result;
}

void roman_calc_free(RomanCalculator* roman_calc)
{
	if(roman_calc != NULL)
	{
		free(roman_calc);
	}	
}

static int convertRomanNumeralToInteger(char* romanNumeral)
{
	int result = 0;
	int lastAddedValue = 0;
	int currentNumeral;

	for(currentNumeral = strlen(romanNumeral) - 1; 
		currentNumeral >= 0; 
		currentNumeral--)
	{
		switch(convertRomanCharacter(romanNumeral[currentNumeral]))
		{
		case 1:
			if(lastAddedValue > 1)
			{
				result -= 1;
			}
			else
			{
				result += 1;
				lastAddedValue = 1;
			}
			break;
		case 5:
			result += 5;
			lastAddedValue = 5;
			break;
		case 10:
			if(lastAddedValue > 10)
			{
				result -= 10;
			}
			else
			{
				result += 10;
				lastAddedValue = 10;
			}
			break;
		case 50:
			result += 50;
			lastAddedValue = 50;
			break;
		case 100:
			if(lastAddedValue > 100)
			{
				result -= 100;
			}
			else
			{
				result += 100;
				lastAddedValue = 100;
			}
			break;
		case 500:
			result += 500;
			lastAddedValue = 500;
			break;
		case 1000:
			result += 1000;
			lastAddedValue = 1000;
			break;
		}
	}

	return result;
}

static int convertRomanCharacter(char romanCharacter)
{
	int result = 0;

	switch(romanCharacter)
	{
	case 'I':
		result = 1;
		break;
	case 'V':
		result = 5;
		break;
	case 'X':
		result = 10;
		break;
	case 'L':
		result = 50;
		break;
	case 'C':
		result = 100;
		break;
	case 'D':
		result = 500;
		break;
	case 'M':
		result = 1000;
		break;
	}

	return result;
}

static void convertIntegerToRomanNumeral(int integer, char* destination)
{
	while(integer > 0)
	{
		int conversionIndex;
		for(conversionIndex = 0; 
			conversionIndex < NUM_ROMAN_CONVERSION; 
			++conversionIndex)
		{
			if(integer >= romanConversionData[conversionIndex].value)
			{
				integer -= romanConversionData[conversionIndex].value;
				strcat(destination, romanConversionData[conversionIndex].numeralString);
				break;
			}
		}
	}
}
