#include <stdlib.h>
#include <check.h>
#include "../src/roman_calc.h"

RomanCalculator* roman_calc;

void setup(void)
{
	roman_calc = roman_calc_create();
}

void teardown(void)
{
	roman_calc_free(roman_calc);
}

START_TEST(test_roman_calc_create)
{
	ck_assert_int_eq (roman_calc_result_length(roman_calc), 0);
}
END_TEST

Suite * roman_calc_suite (void)
{
  Suite *s = suite_create ("Roman Calculator");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_checked_fixture (tc_core, setup, teardown);
  tcase_add_test (tc_core, test_roman_calc_create);
  suite_add_tcase (s, tc_core);

  return s;
}

int main (void)
{
  int number_failed;
  Suite *s = roman_calc_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
