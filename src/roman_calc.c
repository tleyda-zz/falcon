#include <stdlib.h>
#include "roman_calc.h"

struct RomanCalculator
{
	char* result;
};

RomanCalculator* roman_calc_create()
{
	RomanCalculator* roman_calc = malloc(sizeof(RomanCalculator));

	if(roman_calc != NULL)
	{
		roman_calc->result = NULL;
	}

	return(roman_calc);	
}

int roman_calc_result_length(RomanCalculator* roman_calc)
{
	return 0;	
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
