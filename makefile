CC = gcc
CFLAGS = -Wall -std=c99 -pedantic

sylvlib: sylvlib.o
	$(CC) -o sylvlib sylvlib.o

sylvlib.o: sylvlib.h sylvlib.c 
	$(CC) $(CFLAGS) -c sylvlib.c -o sylvlib.o

.PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@if exist sylvlib.o del /F /Q sylvlib.o
	@if exist sylvlib.exe del /F /Q sylvlib.exe
else
	rm -f sylvlib sylvlib.o sylvlib.exe
endif