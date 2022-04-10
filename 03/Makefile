CC=g++
FLAGS=-std=c++2a -O2 -ftrapv -fsanitize=undefined,address -Wall -pedantic -Wextra -Werror -lm -Wno-c++11-extensions
CFLAGS=-O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -std=gnu11 -lm
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

DenseMatrix.o: DenseMatrix.cpp DenseMatrix.hpp
	$(CC) $(FLAGS) DenseMatrix.cpp -c

test_bin: DenseMatrix.o test.cpp
	$(CC) $(FLAGS) DenseMatrix.o test.cpp -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o  test_bin
