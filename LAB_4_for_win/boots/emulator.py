import serial
import time
import random
import argparse

def main():
    parser = argparse.ArgumentParser(description="Serial port temperature emulator.")
    parser.add_argument("--port", type=str, default="/dev/ttyACM1", help="Serial port to use")
    parser.add_argument("--baud", type=int, default=9600, help="Baud rate")
    args = parser.parse_args()

    try:
        ser = serial.Serial(args.port, args.baud, timeout=1)
        while True:
            temperature = random.uniform(10.0, 30.0)  # Генерируем случайную температуру
            data = f"{temperature:.2f}\n"  # Форматируем данные как строку с 2 знаками после запятой и переводом строки
            ser.write(data.encode())  # Отправляем данные через порт
            print(f"Sent: {data.strip()}")
            time.sleep(1)  # Задержка в 1 секунду
    except Exception as e:
        print(f"Error: {e}")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()

if __name__ == "__main__":
    main()