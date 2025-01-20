#include <iostream>
#include "process_manager.h"

int main() {
    try {
        std::string command = "sleep 5"; // Запуск команды sleep на 5 секунд

        std::cout << "Запуск команды: " << command << std::endl;

        // Запуск программы в фоновом режиме и ожидание завершения
        int exitCode = ProcessManager::runInBackground(command, true);
        std::cout << "Команда завершилась с кодом: " << exitCode << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
