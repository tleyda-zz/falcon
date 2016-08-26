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
   roman_calc = NULL;
}

START_TEST(test_roman_calc_create)
{
	 ck_assert_int_eq (roman_calc_result_length(roman_calc), 0);
}
END_TEST

START_TEST(test_roman_calc_add_I_to_I)
{
    roman_calc_add(roman_calc, "I", "I");
    ck_assert_int_eq (roman_calc_result_length(roman_calc), 2);
    ck_assert_str_eq (roman_calc_result(roman_calc), "II");
}
END_TEST

START_TEST(test_roman_calc_add_X_to_X)
{
    roman_calc_add(roman_calc, "X", "X");
    ck_assert_int_eq (roman_calc_result_length(roman_calc), 2);
    ck_assert_str_eq (roman_calc_result(roman_calc), "XX");
}
END_TEST

START_TEST(test_roman_calc_add_C_to_C)
{
    roman_calc_add(roman_calc, "C", "C");
    ck_assert_int_eq (roman_calc_result_length(roman_calc), 2);
    ck_assert_str_eq (roman_calc_result(roman_calc), "CC");
}
END_TEST

START_TEST(test_roman_calc_add_I_to_V)
{
    roman_calc_add(roman_calc, "I", "V");
    ck_assert_int_eq (roman_calc_result_length(roman_calc), 2);
    ck_assert_str_eq (roman_calc_result(roman_calc), "VI");
}
END_TEST

START_TEST(test_roman_calc_add_I_to_X)
{
    roman_calc_add(roman_calc, "I", "X");
    ck_assert_int_eq (roman_calc_result_length(roman_calc), 2);
    ck_assert_str_eq (roman_calc_result(roman_calc), "XI");
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

    TCase *tc_add = tcase_create ("Addition");
    tcase_add_checked_fixture (tc_add, setup, teardown);
    tcase_add_test (tc_add, test_roman_calc_add_I_to_I);
    tcase_add_test (tc_add, test_roman_calc_add_X_to_X);
    tcase_add_test (tc_add, test_roman_calc_add_C_to_C);
    tcase_add_test (tc_add, test_roman_calc_add_I_to_V);
    tcase_add_test (tc_add, test_roman_calc_add_I_to_X);
    suite_add_tcase (s, tc_add);

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
