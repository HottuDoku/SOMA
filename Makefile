#
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror

.PHONY: all

all:
	@gcc $(CFLAGS) editor.c -o editor
	@./editor < input3.txt

test:
	@gcc $(CFLAGS) editor.c -o editor
	@./editor < input.txt
	@./editor < input1.txt
	@./editor < input2.txt
	@./editor < input3.txt
	@./editor < input4.txt
	@./editor < input5.txt
	@./editor < input6.txt