#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "roman_calc.h"

static int convertRomanNumeralToInteger(const char* romanNumeral);
static int findRomanToIntegerConversion(const char romanCharacter);
static int calculateNumeralAdjustment(const int specialNumeral, int* lastAddedValue, 
	const int currentNumeralValue, const int repeatedNumeralCount);
static int handleSpecialRomanNumeral(int* lastAddedValue, const int currentNumeralValue, 
	const int repeatedNumeralCount);
static int handleStandardRomanNumeral(int* lastAddedValue, const int currentNumeralValue, 
	const int repeatedNumeralCount);
static void convertIntegerToRomanNumeral(int integer, char* destination);

struct RomanCalculator
{
	char result[10];
};

struct IntegerToRomanConversion
{
	int value;
	const char* numeralString;
};

struct RomanToIntegerConversion
{
	char numeral;
	int value;
	int isSpecial;
};

#define MAX_REPEATED_NUMERAL_COUNT 3
#define NUM_ROMAN_CONVERSION 13

const struct IntegerToRomanConversion integerToRomanConversionTable[NUM_ROMAN_CONVERSION] = 
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

#define NUM_ROMAN_NUMERAL 7

const struct RomanToIntegerConversion romanToIntegerConversion[NUM_ROMAN_NUMERAL] = 
{
	{'I', 1, 1},
	{'V', 5, 0},
	{'X', 10, 1},
	{'L', 50, 0},
	{'C', 100, 1},
	{'D', 500, 0},
	{'M', 1000, 1}
};

RomanCalculator* roman_calc_create()
{
	RomanCalculator* roman_calc = malloc(sizeof(RomanCalculator));

	return(roman_calc);	
}

void roman_calc_add(RomanCalculator* roman_calc, const char* romanOperand1, const char* romanOperand2)
{
	int operand1 = convertRomanNumeralToInteger(romanOperand1);
	int operand2 = convertRomanNumeralToInteger(romanOperand2);

	memset(roman_calc->result, 0, 10);

	if((0 < operand1) && (0 < operand2))
	{
		convertIntegerToRomanNumeral(operand1 + operand2, roman_calc->result);
	}
}

void roman_calc_subtract(RomanCalculator* roman_calc, const char* romanOperand1, const char* romanOperand2)
{
	int operand1 = convertRomanNumeralToInteger(romanOperand1);
	int operand2 = convertRomanNumeralToInteger(romanOperand2);

	memset(roman_calc->result, 0, 10);

	if((0 < operand1) && (0 < operand2))
	{
		convertIntegerToRomanNumeral(operand1 - operand2, roman_calc->result);
	}
}

int roman_calc_result_length(RomanCalculator* roman_calc)
{
	return strlen(roman_calc->result);
}

char* roman_calc_result(RomanCalculator* roman_calc)
{
	return roman_calc->result;
}

void roman_calc_free(RomanCalculator* roman_calc)
{
	if(NULL != roman_calc)
	{
		free(roman_calc);
	}	
}

static int convertRomanNumeralToInteger(const char* romanNumeral)
{
	int result = 0;
	int lastAddedValue = 0;
	int currentNumeral;
	char lastNumeral = 0;
	int repeatedNumeralCount = 0;

	for(currentNumeral = strlen(romanNumeral) - 1; 
		currentNumeral >= 0; 
		currentNumeral--)
	{
		char inputNumeral = (char)toupper(romanNumeral[currentNumeral]);
		int conversionIndex = findRomanToIntegerConversion(inputNumeral);

		if(0 > conversionIndex)
		{
			result = 0;
			break;
		}

		if(inputNumeral == lastNumeral)
		{
			repeatedNumeralCount++;
		}
		else
		{
			repeatedNumeralCount = 0;
		}

		int currentNumeralValue = romanToIntegerConversion[conversionIndex].value;
		int adjustment = calculateNumeralAdjustment(
							romanToIntegerConversion[conversionIndex].isSpecial,
							&lastAddedValue, 
							currentNumeralValue, 
							repeatedNumeralCount);

		if(0 == adjustment)
		{
			result = 0;
			break;
		}
		else
		{
			result += adjustment;
		}
		lastNumeral = inputNumeral;
	}

	return result;
}

static int findRomanToIntegerConversion(const char romanCharacter)
{
	int conversionIndex;

	for(conversionIndex = 0; 
		conversionIndex < NUM_ROMAN_NUMERAL; 
		++conversionIndex)
	{
		if(romanCharacter == romanToIntegerConversion[conversionIndex].numeral)
		{
			break;
		}
	}

	return NUM_ROMAN_NUMERAL > conversionIndex ? conversionIndex : -1;
}

static int calculateNumeralAdjustment(const int specialNumeral, int* lastAddedValue, 
	const int currentNumeralValue, const int repeatedNumeralCount)
{
	return specialNumeral ?
				handleSpecialRomanNumeral(lastAddedValue, currentNumeralValue, 
					repeatedNumeralCount) :
				handleStandardRomanNumeral(lastAddedValue, currentNumeralValue, 
					repeatedNumeralCount);
}

static int handleSpecialRomanNumeral(int* lastAddedValue, const int currentNumeralValue, 
	const int repeatedNumeralCount)
{
	int adjustment = 0;

	if(currentNumeralValue < *lastAddedValue)
	{
		if(0 == repeatedNumeralCount)
		{
			adjustment = -currentNumeralValue;
		}
	}
	else
	{
		if(MAX_REPEATED_NUMERAL_COUNT > repeatedNumeralCount)
		{
			adjustment = currentNumeralValue;
			*lastAddedValue = currentNumeralValue;
		}
	}

	return adjustment;
}

static int handleStandardRomanNumeral(int* lastAddedValue, const int currentNumeralValue, 
	const int repeatedNumeralCount)
{
	int adjustment = 0;

	if(0 == repeatedNumeralCount)
	{
		adjustment = currentNumeralValue;
		*lastAddedValue = currentNumeralValue;
	}

	return adjustment;
}

static void convertIntegerToRomanNumeral(int integer, char* destination)
{
	while(0 < integer)
	{
		int conversionIndex;
		for(conversionIndex = 0; 
			conversionIndex < NUM_ROMAN_CONVERSION; 
			++conversionIndex)
		{
			if(integerToRomanConversionTable[conversionIndex].value <= integer)
			{
				integer -= integerToRomanConversionTable[conversionIndex].value;
				strcat(destination, integerToRomanConversionTable[conversionIndex].numeralString);
				break;
			}
		}
	}
}
