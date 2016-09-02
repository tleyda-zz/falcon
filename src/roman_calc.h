#ifndef ROMAN_CALC_H
#define ROMAN_CALC_H

typedef struct RomanCalculator RomanCalculator;

RomanCalculator* romanCalcCreate();
void romanCalcAdd(RomanCalculator* roman_calc, const char* romanOperand1, const char* romanOperand2);
void romanCalcSubtract(RomanCalculator* roman_calc, const char* romanOperand1, const char* romanOperand2);
int romanCalcResultLength(RomanCalculator* roman_calc);
char* romanCalcResult(RomanCalculator* roman_calc);
void romanCalcFree(RomanCalculator* roman_calc);

#endif // ROMAN_CALC_H