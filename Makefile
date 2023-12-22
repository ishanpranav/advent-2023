CC = gcc
CFLAGS = -O3 -pedantic -std=c99 -Wall -Wextra
CMATH = -lm

all: \
	day01a day01b \
	day02a day02b \
	day03a day03b \
	day04a day04b \
	day05a day05b \
	day06a day06b \
	day07a day07b \
	day08a day08b \
	day09a day09b \
	day10a day10b \
	day11a day11b \
	day12a day12b \
	day13a day13b \
	day14a day14b \
	day15a day15b \
	day16a day16b

test:
	cat alt01.txt | ./day01a.o > out.txt
	cat alt01.txt | ./day01b.o >> out.txt
	cat alt02.txt | ./day02a.o >> out.txt
	cat alt02.txt | ./day02b.o >> out.txt
	cat alt03.txt | ./day03a.o >> out.txt
	cat alt03.txt | ./day03b.o >> out.txt
	cat alt04.txt | ./day04a.o >> out.txt
	cat alt04.txt | ./day04b.o >> out.txt
	cat alt05.txt | ./day05a.o >> out.txt
	cat alt05.txt | ./day05b.o >> out.txt
	cat alt06.txt | ./day06a.o >> out.txt
	cat alt06.txt | ./day06b.o >> out.txt
	cat alt07.txt | ./day07a.o >> out.txt
	cat alt07.txt | ./day07b.o >> out.txt
	cat alt08.txt | ./day08a.o >> out.txt
	cat alt08.txt | ./day08b.o >> out.txt
	cat alt09.txt | ./day09a.o >> out.txt
	cat alt09.txt | ./day09b.o >> out.txt
	cat alt10.txt | ./day10a.o >> out.txt
	cat alt10.txt | ./day10b.o >> out.txt
	cat alt11.txt | ./day11a.o >> out.txt
	cat alt11.txt | ./day11b.o >> out.txt
	cat alt12.txt | ./day12a.o >> out.txt
	cat alt12.txt | ./day12b.o >> out.txt
	cat alt13.txt | ./day13a.o >> out.txt
	cat alt13.txt | ./day13b.o >> out.txt
	cat alt14.txt | ./day14a.o >> out.txt
	cat alt14.txt | ./day14b.o >> out.txt
	cat alt15.txt | ./day15a.o >> out.txt
	cat alt15.txt | ./day15b.o >> out.txt
	cat alt16.txt | ./day16a.o >> out.txt
	cat alt16.txt | ./day16b.o >> out.txt
	cat out.txt
	
day01a: src/day01a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day01b: src/day01b.c
	$(CC) $(CFLAGS) $< -o $@.o

day02a: src/day02a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day02b: src/day02b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day03a: src/day03a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day03b: src/day03b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day04a: src/day04a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day04b: src/day04b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day05a: src/day05a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day05b: src/day05b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day06a: src/day06a.c
	$(CC) $(CFLAGS) $< -o $@.o $(CMATH)
	
day06b: src/day06b.c
	$(CC) $(CFLAGS) $< -o $@.o $(CMATH)
	
day07a: src/day07a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day07b: src/day07b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day08a: src/day08a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day08b: src/day08b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day09a: src/day09a.c
	$(CC) $(CFLAGS) $< -o $@.o $(CMATH)
	
day09b: src/day09b.c
	$(CC) $(CFLAGS) $< -o $@.o $(CMATH)
	
day10a: src/day10a.c
	$(CC) $(CFLAGS) $< -o $@.o

day10b: src/day10b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day11a: src/day11a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day11b: src/day11b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day12a: src/day12a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day12b: src/day12b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day13a: src/day13a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day13b: src/day13b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day14a: src/day14a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day14b: src/day14b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day15a: src/day15a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day15b: src/day15b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day16a: src/day16a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day16b: src/day16b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
clean:
	rm -rf *.o