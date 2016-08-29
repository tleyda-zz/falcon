#include <stdlib.h>
#include <string.h>
#include "roman_calc.h"

#include <stdio.h>

struct RomanCalculator
{
	char* result;
};

RomanCalculator* roman_calc_create()
{
	RomanCalculator* roman_calc = malloc(sizeof(RomanCalculator));

	// if(roman_calc != NULL)
	// {
		roman_calc->result = NULL;
	// }

	return(roman_calc);	
}

void roman_calc_add(RomanCalculator* roman_calc, char* romanOperand1, char* romanOperand2)
{
	roman_calc->result = realloc(roman_calc->result, 3);
	memset(roman_calc->result, 0, 3);

	switch(romanOperand1[0])
	{
	case 'I':
		switch(romanOperand2[0])
		{
		case 'I':
		case 'V':
		case 'X':
		case 'L':
		case 'C':
		case 'D':
		case 'M':
			roman_calc->result[0] = romanOperand2[0];	
			break;	
		}
		roman_calc->result[1] = 'I';
		break;
	case 'V':
		switch(romanOperand2[0])
		{
		case 'I':
			roman_calc->result[0] = 'V';
			roman_calc->result[1] = 'I';
			break;
		case 'V':
			roman_calc->result[0] = 'X';
			break;
		case 'X':
		case 'C':
		case 'D':
		case 'M':
			roman_calc->result[0] = romanOperand2[0];
			roman_calc->result[1] = 'V';
			break;
		}
		break;
	case 'X':
		switch(romanOperand2[0])
		{
		case 'I':
		case 'V':
		case 'X':
			roman_calc->result[0] = 'X';
			roman_calc->result[1] = romanOperand2[0];
			break;
		case 'C':
		case 'D':
		case 'M':
			roman_calc->result[0] = romanOperand2[0];
			roman_calc->result[1] = 'X';
			break;
		}
		break;
	case 'L':
		roman_calc->result[0] = 'L';
		roman_calc->result[1] = 'I';
		break;
	case 'C':
		roman_calc->result[0] = 'C';	
		roman_calc->result[1] = 'C';
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
