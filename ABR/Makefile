CC = gcc
CFLAGS = -g -Wall -Werror
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXE = test_abr test_file test_pile

all: $(EXE)

%.o:%.c
	$(CC) $(CFLAGS) -c $<

test_abr: test_abr.o pile.o file.o abr.o
	$(CC) $(CFLAGS) -o $@ $^

test_pile: test_pile.o abr.o pile.o file.o
	$(CC) $(CFLAGS) -o $@ $^

test_file: test_file.o abr.o pile.o file.o
	$(CC) $(CFLAGS) -o $@ $^

abr.o:abr.h pile.h file.h
pile.o: pile.h
file.o: file.h
test_abr.o: abr.h
test_pile.o: abr.h pile.h file.h
test_file.o: abr.h pile.h file.h

.PHONY : clean
clean:
	rm -f $(OBJ) $(EXE)


