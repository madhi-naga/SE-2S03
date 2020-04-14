CFLAGS = -Wall -ansi -Werror

filter:
	gcc -o filter $(CFLAGS) filter.c 

clean:
	@rm -rf ./filter 
