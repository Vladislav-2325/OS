#!/bin/bash
echo "Начало выполнения скрипта"
git pull origin main
if [ $? -ne 0 ]; then
    echo "Ошибка при выполнении git pull"
    exit 1
fi

mkdir -p build
cd build
cmake ..
if [ $? -ne 0 ]; then
    echo "Ошибка при выполнении cmake"
    exit 1
fi

make
if [ $? -ne 0 ]; then
    echo "Ошибка при выполнении make"
    exit 1
fi

echo "Скрипт выполнен успешно"
