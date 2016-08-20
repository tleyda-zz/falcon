TARGET = romancalcapp

$(TARGET): main.o roman_calc.a
	gcc $^ -o $@

main.o: main.c
	gcc -c $< -o $@

roman_calc.a: roman_calc.o
	ar rcs $@ $^

roman_calc.o: roman_calc.c roman_calc.h
	gcc -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET)
