../testromancalc: check_roman_calc.o ../src/roman_calc.a
	gcc $^ -lcheck -lpthread -lm -lrt -o $@

check_roman_calc.o: check_roman_calc.c
	gcc -c $< -o $@

clean:
	rm *.o
