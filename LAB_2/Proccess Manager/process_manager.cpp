#include "process_manager.h"
#include <iostream>
#include <stdexcept>

int ProcessManager::runInBackground(const std::string& command, bool waitForCompletion) {
#ifdef _WIN32
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    si.cb = sizeof(si);
    if (!CreateProcess(nullptr, const_cast<char*>(command.c_str()), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        throw std::runtime_error("Failed to create process");
    }

    if (waitForCompletion) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return exitCode;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0; // Успех, но не ждем завершения
#else
    pid_t pid = fork();
    if (pid < 0) {
        throw std::runtime_error("Failed to fork process");
    }

    if (pid == 0) {
        // Дочерний процесс
        char* args[] = {const_cast<char*>(command.c_str()), nullptr};
        execvp(args[0], args);
        // Если execvp вернется, произошла ошибка
        exit(EXIT_FAILURE);
    } else {
        // Родительский процесс
        if (waitForCompletion) {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                return WEXITSTATUS(status);
            }
            return -1; // Процесс завершился неудачно
        }
    }
    return 0; // Успех, но не ждем завершения
#endif
}
