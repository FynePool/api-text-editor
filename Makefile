CC = gcc
CFLAGS = -O2 -Wall -Wextra

.PHONY: build test clean

build: editor

editor: main.c
	$(CC) $(CFLAGS) -o editor main.c

test: build
	./tests/run_tests.sh ./editor

clean:
	rm -f editor
