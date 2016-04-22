MKDIR_P=@mkdir -p
RM_R=@rm -r
CC=@g++
CFLAGS=-Wall -Wextra -ggdb -O0 -fprofile-arcs -ftest-coverage -std=c++11
font_light_green=\e[92m
font_light_red=\e[91m
font_default=\e[37m

.PHONY: all, run_tests, clean

all: dirs run_tests

run_tests: dirs build/unit_tests.elf
	@echo -e "$(font_light_green)Running tests (valgrind)...$(font_default)"
	@LC_ALL="C" valgrind --leak-check=full --track-origins=yes --suppressions=suppressions.supp  --show-leak-kinds=all \
		./build/unit_tests.elf 2>valgrind-res.txt
	@echo -e "$(font_light_green)Running gcov...$(font_default)"
	@LC_ALL="C" gcov -b ./build/UnsignedNumber.o >gcov-unsigned-number.txt
	@LC_ALL="C" gcov -b ./build/Number.o >gcov-number.txt
	@echo -en '$(font_light_green)'
	@grep -o 'ERROR SUMMARY:.*' valgrind-res.txt
	@echo -en '$(font_default)'
	@! grep -o 'loss record' valgrind-res.txt >/dev/null \
		|| (echo -e "$(font_light_red)There were unsuppressed memory leaks$(font_default)"; exit 1)
	@grep -o 'ERROR SUMMARY: 0 errors' valgrind-res.txt >/dev/null \
		|| (echo -e "$(font_light_red)There were memory errors$(font_default)"; exit 1)
	@# Output gcov results without checking
	@grep -A 4 "File 'src/UnsignedNumber.cpp'" gcov-unsigned-number.txt
	@grep -A 4 "File 'src/Number.cpp'" gcov-number.txt
	
	@grep -A 4 "File 'src/UnsignedNumber.cpp'" gcov-unsigned-number.txt | grep -o 'Lines executed:100.00%' \
		|| (echo -e "$(font_light_red)Not all lines are executed in src/UnsignedNumber.cpp$(font_default)"; exit 1)
	@grep -A 4 "File 'src/Number.cpp'" gcov-number.txt | grep -o 'Lines executed:100.00%' \
		|| (echo -e "$(font_light_red)Not all lines are executed in src/Number.cpp$(font_default)"; exit 1)

clean:
	$(RM_R) build

dirs:
	$(MKDIR_P) -p build

build/unit_tests.elf: build/UnitTests.o build/NumberException.o build/Number.o build/UnsignedNumber.o
	$(CC) $(CFLAGS) build/UnitTests.o build/NumberException.o build/Number.o build/UnsignedNumber.o -o build/unit_tests.elf

build/UnitTests.o: src/UnitTests.cpp src/Number.hpp src/NumberException.hpp src/UnsignedNumber.hpp
	$(CC) $(CFLAGS) -c src/UnitTests.cpp -o build/UnitTests.o

build/Number.o: src/Number.cpp src/Number.hpp
	$(CC) $(CFLAGS) -c src/Number.cpp -o build/Number.o
	
build/UnsignedNumber.o: src/UnsignedNumber.cpp src/UnsignedNumber.hpp
	$(CC) $(CFLAGS) -c src/UnsignedNumber.cpp -o build/UnsignedNumber.o
	
build/NumberException.o: src/NumberException.cpp src/NumberException.hpp
	$(CC) $(CFLAGS) -c src/NumberException.cpp -o build/NumberException.o
