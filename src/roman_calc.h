#ifndef ROMAN_CALC_H
#define ROMAN_CALC_H

typedef struct RomanCalculator RomanCalculator;

RomanCalculator* roman_calc_create();
int roman_calc_result_length(RomanCalculator* roman_calc);
void roman_calc_free(RomanCalculator* roman_calc);

#endif // ROMAN_CALC_H