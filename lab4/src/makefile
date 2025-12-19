all: parallel_min_max_timeout process_memory zombie zombie_prevent parallel_sum
CC = gcc
CFLAGS = -I.

# Главная цель (можно оставить new или поменять на all)
all: parallel_min_max_timeout zombie process_memory parallel_sum

# 1. Программа с таймаутом
parallel_min_max_timeout: parallel_min_max_timeout.o utils.o find_min_max.o
	$(CC) -o $@ $^

parallel_min_max_timeout.o: parallel_min_max_timeout.c find_min_max.h utils.h
	$(CC) -c $< -o $@ $(CFLAGS)

# 2. Программа-зомби
zombie: zombie.o
	$(CC) -o $@ $^

zombie.o: zombie.c
	$(CC) -c $< -o $@ $(CFLAGS)

# 3. Программа памяти
process_memory: process_memory.o
	$(CC) -o $@ $^

process_memory.o: process_memory.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Общие библиотечные файлы
utils.o: utils.c utils.h
	$(CC) -c $< -o $@ $(CFLAGS)

find_min_max.o: find_min_max.c find_min_max.h
	$(CC) -c $< -o $@ $(CFLAGS)

# Очистка
clean:
	rm -f *.o parallel_min_max_timeout zombie process_memory result_*.txt

# Псевдонимы (чтобы работало и с new)
new: all
.PHONY: all new clean

# Параллельное суммирование (задание 5)
parallel_sum: parallel_sum.o sum_lib.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ -pthread

parallel_sum.o: parallel_sum.c utils.h sum_lib.h
	$(CC) $(CFLAGS) -c $< -o $@

sum_lib.o: sum_lib.c sum_lib.h
	$(CC) $(CFLAGS) -c $< -o $@

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c $< -o $@

# Тест
test_sum: parallel_sum
	@echo "=== Тест параллельного суммирования ==="
	./parallel_sum --seed 123 --array_size 1000000 --threads_num 4

.PHONY: test_sum
