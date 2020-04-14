
CFLAGS=-Wall -O2 -ansi -pg
CC = gcc
fib: main_fib.o fib.o bmp.o timing.o
	$(CC) -o fib $? -lm -pg
runall:
	./fib 7 10 10 10 500 500 fib7.bmp
	./fib 9 10 10 5 500 500 fib9.bmp	
	./fib 14 10 10 5 500 500 fib14.bmp
	./fib 17 10 10 3 500 500 fib17.bmp
	./fib 25 15 15 2 3000 3000 fib25.bmp
	./fib 26 15 15 2 3000 3000 fib26.bmp
	./fib 30 15 15 2 15000 5000 fib30.bmp
	./fib 34 15 15 2 30000 30000 fib34.bmp
	./fib 30 10 10 5 29000 12000 fib30prof.bmp
clean:
	@rm -rf fib *.o *bmp
