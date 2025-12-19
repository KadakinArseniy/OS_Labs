#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Входные аргументы отсутствуют!"
    exit 1
fi

echo "Количество введённых аргументов: $#"

sum=0
for arg in "$@"; do
    if ! expr "$arg" + 0 &> /dev/null; then
        echo "Ошибка: '$arg' не является числом."
        exit 1
    fi
    sum=$((sum + arg))
done

average=$((sum / $#))
echo "Среднее арифметическое: $average"
