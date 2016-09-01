#ifndef ROMAN_CALC_H
#define ROMAN_CALC_H

typedef struct RomanCalculator RomanCalculator;

enum
{
	LESS_THAN = -1,
	EQUAL_TO,
	GREATER_THAN
};

RomanCalculator* roman_calc_create();
void roman_calc_add(RomanCalculator* roman_calc, char* romanOperand1, char* romanOperand2);
void roman_calc_subtract(RomanCalculator* roman_calc, char* romanOperand1, char* romanOperand2);
int roman_calc_result_length(RomanCalculator* roman_calc);
char* roman_calc_result(RomanCalculator* roman_calc);
void roman_calc_free(RomanCalculator* roman_calc);

#endif // ROMAN_CALC_H