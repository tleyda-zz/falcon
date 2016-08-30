#include <stdlib.h>
#include <string.h>
#include "roman_calc.h"

#include <stdio.h>

static int compareRomanNumeral(char leftNumeral, char  rightNumeral);

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
	roman_calc->result = realloc(roman_calc->result, 3);
	memset(roman_calc->result, 0, 3);

	switch(compareRomanNumeral(romanOperand1[0], romanOperand2[0]))
	{
	case LESS_THAN:
		roman_calc->result[0] = romanOperand2[0];
		roman_calc->result[1] = romanOperand1[0];
		break;	
	case EQUAL_TO:
		switch(romanOperand1[0])
		{
		case 'I':
		case 'X':
		case 'C':
		case 'M':
			roman_calc->result[0] = romanOperand1[0];
			roman_calc->result[1] = romanOperand1[0];
			break;
		case 'V':
			roman_calc->result[0] = 'X';
			break;
		case 'L':
			roman_calc->result[0] = 'C';
			break;
		case 'D':
			roman_calc->result[0] = 'M';
			break;
		}
		break;	
	case GREATER_THAN:
		roman_calc->result[0] = romanOperand1[0];
		roman_calc->result[1] = romanOperand2[0];
		break;	
	}

	roman_calc->result[2] = 0;	
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

static int compareRomanNumeral(char leftNumeral, char  rightNumeral)
{
	int result = EQUAL_TO;

	if(leftNumeral != rightNumeral)
	{
		switch(leftNumeral)
		{
		case 'I':
			result = LESS_THAN;
			break;
		case 'V':
			switch(rightNumeral)
			{
			case 'I':
				result = GREATER_THAN;
				break;
			case 'X':
			case 'C':
			case 'D':
			case 'M':
				result = LESS_THAN;
				break;
			}
			break;
		case 'X':
			switch(rightNumeral)
			{
			case 'I':
			case 'V':
				result = GREATER_THAN;
				break;
			case 'C':
			case 'D':
			case 'M':
				result = LESS_THAN;
				break;
			}
			break;
		case 'L':
			switch(rightNumeral)
			{
			case 'I':
			case 'V':
			case 'X':
				result = GREATER_THAN;
				break;
			case 'C':
			case 'D':
			case 'M':
				result = LESS_THAN;
				break;
			}
			break;
		case 'C':
			switch(rightNumeral)
			{
			case 'I':
			case 'V':
			case 'X':
			case 'L':
				result = GREATER_THAN;
				break;
			case 'D':
			case 'M':
				result = LESS_THAN;
				break;
			}
			break;
		case 'D':
			switch(rightNumeral)
			{
			case 'I':
			case 'V':
			case 'X':
			case 'L':
			case 'C':
				result = GREATER_THAN;
				break;
			case 'M':
				result = LESS_THAN;
				break;
			}
			break;
		case 'M':
			result = GREATER_THAN;
			break;
		}
	}

	return result;
}

