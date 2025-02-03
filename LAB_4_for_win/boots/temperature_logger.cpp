#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>
#include <iomanip>
#include <sstream>
#include <cstdlib> // Для rand() и srand()
#include <ctime> // Для time()

// Абсолютные пути к лог-файлам
const std::string RAW_DATA_LOG_FILE = "D:\\boots\\raw_data.log";
const std::string HOURLY_AVG_LOG_FILE = "D:\\boots\\hourly_avg.log";
const std::string DAILY_AVG_LOG_FILE = "D:\\boots\\daily_avg.log";

void logData(const std::string& logFile, const std::string& data, bool consoleOutput) {
    std::ofstream file(logFile, std::ios::app);
    if (file.is_open()) {
        file << data << std::endl;
        file.close();
    } else {
        std::cerr << "Error: Unable to open log file: " << logFile << std::endl;
    }
    if (consoleOutput) {
        std::cout << data << std::flush << std::endl;
    }
}

void logHourlyAverage(double avgTemp, bool consoleOutput) {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << " : " << std::fixed << std::setprecision(2) << avgTemp;
    logData(HOURLY_AVG_LOG_FILE, ss.str(), consoleOutput);
}

void logDailyAverage(double avgTemp, bool consoleOutput) {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << " : " << std::fixed << std::setprecision(2) << avgTemp;
    logData(DAILY_AVG_LOG_FILE, ss.str(), consoleOutput);
}

int main(int argc, char** argv) {
    bool consoleOutput = false;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--console-output") {
            consoleOutput = true;
        }
    }

    std::vector<double> hourlyTemperatures;
    std::vector<double> dailyTemperatures;

    int currentHour = -1;
    int currentDay = -1;

    // Инициализируем генератор случайных чисел
    srand(time(0));

    while (true) {
        // Имитация считывания данных
        double randomTemperature = 10.0 + (rand() % 2001) / 100.0; // Случайное число от 10.0 до 30.0
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << randomTemperature;
        std::string rawData = ss.str();


        // Пытаемся преобразовать данные в число
        double temperature;
        try {
            temperature = std::stod(rawData);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting data to double: " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue; // переходим к следующей итерации
        }

        // Записываем необработанные данные в лог
        logData(RAW_DATA_LOG_FILE, rawData, consoleOutput);

        // Добавляем в буферы почасовой и дневной температуры
        hourlyTemperatures.push_back(temperature);
        dailyTemperatures.push_back(temperature);

        // Получаем текущее время
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm* localTime = std::localtime(&currentTime);

        // Проверяем, наступил ли новый час
        if (localTime->tm_hour != currentHour) {
            // Вычисляем среднюю температуру за час
            double hourlyAvg = 0.0;
            if (!hourlyTemperatures.empty()) {
                for (double temp : hourlyTemperatures) {
                    hourlyAvg += temp;
                }
                hourlyAvg /= hourlyTemperatures.size();
                logHourlyAverage(hourlyAvg, consoleOutput);
                hourlyTemperatures.clear();
            }
            currentHour = localTime->tm_hour;
        }

        // Проверяем, наступил ли новый день
        if (localTime->tm_yday != currentDay) {
            // Вычисляем среднюю температуру за день
            double dailyAvg = 0.0;
             if (!dailyTemperatures.empty()) {
                for (double temp : dailyTemperatures) {
                   dailyAvg += temp;
                }
                dailyAvg /= dailyTemperatures.size();
                logDailyAverage(dailyAvg, consoleOutput);
                dailyTemperatures.clear();
             }
           currentDay = localTime->tm_yday;
        }
       std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}