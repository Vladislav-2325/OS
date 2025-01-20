#include <iostream>
#include <string>

void startProcess(const std::string& processName) {
    // Здесь будет логика для запуска процесса
    // Например, вы можете использовать fork() и exec() для запуска нового процесса

    // Предположим, что процесс успешно запущен
    bool success = true; // Замените на вашу логику проверки

    if (success) {
        std::cout << "Процесс '" << processName << "' успешно запущен." << std::endl;
    } else {
        std::cout << "Не удалось запустить процесс '" << processName << "'." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <command> <process_name>" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string processName = argv[2];

    if (command == "start") {
        startProcess(processName);
    } else {
        std::cerr << "Неизвестная команда: " << command << std::endl;
    }

    return 0;
}
