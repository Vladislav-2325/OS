#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

class ProcessManager {
public:
    // Запускает программу в фоновом режиме
    static int runInBackground(const std::string& command, bool waitForCompletion = true);
};

#endif // PROCESS_MANAGER_H
