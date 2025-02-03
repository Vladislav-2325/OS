Программа для считывания температуры с серийного порта и логирования.

Файлы:
  - temperature_logger.cpp: Основная программа на C++.
  - emulator.py: Эмулятор серийного порта на Python.

Компиляция (Windows):
  x86_64-w64-mingw32-g++ -std=c++11 -o temperature_logger.exe temperature_logger.cpp -I "C:\Новая папка\boost_1_87_0" -L "C:\Новая папка\boost_1_87_0\libs\stage\lib" -lboost_system-mt -lboost_program_options-mt
  или
  x86_64-w64-mingw32-g++ -std=c++11 -o temperature_logger.exe temperature_logger.cpp -I "C:\Новая папка\boost_1_87_0" -L "C:\Новая папка\boost_1_87_0\libs\gcc\x64" -lboost_system-mt -lboost_program_options-mt
  Замените "C:\Новая папка\boost_1_87_0" на путь к установленной библиотеке Boost.
  Замените "C:\Новая папка\boost_1_87_0\libs\stage\lib" или "C:\Новая папка\boost_1_87_0\libs\gcc\x64" на путь к папке с скомпилированными библиотеками boost.

Запуск эмулятора:
  python emulator.py --port COM3
  (Замените COM3 на номер вашего порта)

Запуск основной программы (примеры):
  temperature_logger.exe --port COM4 --baud 115200
  (Замените COM4 и другие параметры по необходимости)

Параметры:
  --port: Указывает порт для подключения.
  --baud: Скорость передачи данных.
   --raw-log-limit: Максимальное количество строк в лог-файле сырых данных (для отслеживания последних 24 часов)
  --hourly-log-limit: Максимальное количество строк в лог-файле средней почасовой температуры (для отслеживания последнего месяца)
