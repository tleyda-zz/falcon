#include <stdlib.h>
#include <string.h>
#include "roman_calc.h"

#include <stdio.h>

static int convertRomanNumeralToInteger(char* romanNumeral);
static int convertRomanCharacter(char romanCharacter);
static void convertIntegerToRomanNumeral(int integer, char* destination);

struct RomanCalculator
{
	char* result;
};

RomanCalculator* roman_calc_create()
{
	RomanCalculator* roman_calc = malloc(sizeof(RomanCalculator));

	roman_calc->result = NULL;

	return(roman_calc);	
}

void roman_calc_add(RomanCalculator* roman_calc, char* romanOperand1, char* romanOperand2)
{
	int operand1 = convertRomanNumeralToInteger(romanOperand1);
	int operand2 = convertRomanNumeralToInteger(romanOperand2);

	roman_calc->result = realloc(roman_calc->result, 4);
	memset(roman_calc->result, 0, 4);

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
		if(roman_calc->result != NULL)
		{
			free(roman_calc->result);
		}

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
			result += 100;
			break;
		case 500:
			result += 500;
			break;
		case 1000:
			result += 1000;
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
	char* currentNumeral = destination;
	while(integer > 0)
	{
		if(integer >= 1000)
		{
			integer -= 1000;
			*currentNumeral = 'M';
		}
		else if(integer >= 500)
		{
			integer -= 500;
			*currentNumeral = 'D';
		}
		else if(integer == 400)
		{
			*currentNumeral = 'C';
			currentNumeral++;
			*currentNumeral = 'D';
			integer -= 400;
		}
		else if(integer >= 100)
		{
			integer -= 100;
			*currentNumeral = 'C';
		}
		else if(integer == 90)
		{
			*currentNumeral = 'X';
			currentNumeral++;
			*currentNumeral = 'C';
			integer -= 90;
		}
		else if(integer >= 50)
		{
			integer -= 50;
			*currentNumeral = 'L';
		}
		else if(integer == 40)
		{
			*currentNumeral = 'X';
			currentNumeral++;
			*currentNumeral = 'L';
			integer -= 40;
		}
		else if(integer >= 10)
		{
			integer -= 10;
			*currentNumeral = 'X';
		}
		else if(integer == 9)
		{
			*currentNumeral = 'I';
			currentNumeral++;
			*currentNumeral = 'X';
			integer -= 9;
		}
		else if(integer >= 5)
		{
			integer -= 5;
			*currentNumeral = 'V';
		}
		else if(integer == 4)
		{
			*currentNumeral = 'I';
			currentNumeral++;
			*currentNumeral = 'V';
			integer -= 4;
		}
		else
		{
			integer--;
			*currentNumeral = 'I';
		}
		currentNumeral++;
	}
}
