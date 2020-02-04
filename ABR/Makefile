all: test_abr test_pile test_file

abr.o: abr.c abr.h pile.h file.h
	gcc -g -Wall -c abr.c

pile.o: pile.h pile.c
	gcc -Wall -c pile.c

file.o: file.h file.c
	gcc -Wall -c file.c

test_abr.o: test_abr.c abr.h
	gcc -Wall -c test_abr.c

test_abr: test_abr.o pile.o file.o abr.o
	gcc -o test_abr abr.o pile.o file.o test_abr.o

test_pile.o: test_pile.c abr.h pile.h file.h
	gcc -Wall -g -c test_pile.c

test_pile: test_pile.o abr.o pile.o file.o
	gcc -g -o test_pile abr.o pile.o test_pile.o file.o
	
test_file.o: test_file.c abr.h pile.h file.h
	gcc -Wall -g -c test_file.c

test_file: test_file.o abr.o pile.o file.o
	gcc -g -o test_file abr.o pile.o test_file.o file.o

clean:
	rm -f *.o *~ test_abr test_pile test_file


