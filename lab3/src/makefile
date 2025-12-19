CC = gcc
CFLAGS = -I.

all: sequential_min_max parallel_min_max runner

sequential_min_max: sequential_min_max.o find_min_max.o utils.o
	$(CC) -o $@ $^

parallel_min_max: parallel_min_max.o find_min_max.o utils.o
	$(CC) -o $@ $^

sequential_min_max.o: sequential_min_max.c find_min_max.h utils.h
	$(CC) -c -o $@ $< $(CFLAGS)

parallel_min_max.o: parallel_min_max.c find_min_max.h utils.h
	$(CC) -c -o $@ $< $(CFLAGS)

find_min_max.o: find_min_max.c find_min_max.h
	$(CC) -c -o $@ $< $(CFLAGS)

utils.o: utils.c utils.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o sequential_min_max parallel_min_max result_*.txt

test_sequential: sequential_min_max
	./sequential_min_max 42 100

test_parallel: parallel_min_max
	./parallel_min_max --seed 42 --array_size 100 --pnum 4

.PHONY: all clean test_sequential test_parallel

runner: runner.o
	$(CC) -o $@ $^

runner.o: runner.c
	$(CC) -c -o $@ $< $(CFLAGS)

test_runner: runner sequential_min_max
	./runner

.PHONY: test_runner
