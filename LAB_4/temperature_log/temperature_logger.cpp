#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

class TemperatureLogger {
public:
    TemperatureLogger(const std::string& port) {
        // Открытие последовательного порта
        serialPort = open(port.c_str(), O_RDONLY | O_NOCTTY);
        if (serialPort == -1) {
            std::cerr << "Error opening serial port: " << port << std::endl;
            exit(EXIT_FAILURE);
        }
        configurePort();
    }

    ~TemperatureLogger() {
        close(serialPort);
    }

    void startLogging() {
        char buffer[256];
        while (true) {
            int bytesRead = read(serialPort, buffer, sizeof(buffer) - 1);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0'; // Нуль-терминатор для строки
                std::cout << "Bytes read: " << bytesRead << ", Data: '" << buffer << "'" << std::endl; // Отладочное сообщение
                double temperature = std::atof(buffer); // Преобразование строки в число
                logTemperature(temperature);
            } else {
                std::cerr << "No data read from port." << std::endl;
            }
            usleep(1000000); // Задержка 1 секунда
        }
    }

private:
    int serialPort;

    void configurePort() {
        struct termios options;
        tcgetattr(serialPort, &options);
        options.c_cflag = B9600 | CS8 | CLOCAL | CREAD; // Настройка скорости и параметров порта
        options.c_iflag = IGNPAR;
        options.c_oflag = 0;
        options.c_lflag = 0;
        tcflush(serialPort, TCIFLUSH);
        tcsetattr(serialPort, TCSANOW, &options);
    }

    void logTemperature(double temperature) {
        std::ofstream logFile("temperature_logger.txt", std::ios::app);
        if (logFile.is_open()) {
            std::time_t now = std::time(nullptr);
            logFile << std::ctime(&now) << ": " << temperature << std::endl;
            logFile.close();
            std::cout << "Temperature logged: " << temperature << std::endl; // Отладочное сообщение
        } else {
            std::cerr << "Failed to open log file." << std::endl; // Сообщение об ошибке
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <serial_port>" << std::endl;
        return EXIT_FAILURE;
    }

    TemperatureLogger logger(argv[1]);
    logger.startLogging();

    return EXIT_SUCCESS;
}
