#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <csignal>
#include <atomic>
#include <mutex>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

std::atomic<int> counter(0);
std::mutex logMutex;
std::ofstream logFile;
bool isRunning = true;

void log(const std::string& message) {
    std::lock_guard<std::mutex> guard(logMutex);
    logFile << message << std::endl;
}

void writeLogHeader() {
    std::time_t now = std::time(nullptr);
    logFile << "Process ID: " << getpid() << ", Start Time: " << std::ctime(&now);
}

void timerFunction() {
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        counter++;
    }
}

void logCurrentStatus() {
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::time_t now = std::time(nullptr);
        log("Current Time: " + std::string(std::ctime(&now)) +
            ", Process ID: " + std::to_string(getpid()) +
            ", Counter: " + std::to_string(counter.load()));
    }
}

void createChildProcess1() {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        std::ofstream childLog("log.txt", std::ios::app);
        std::time_t now = std::time(nullptr);
        childLog << "Child Process 1 ID: " << getpid() << ", Start Time: " << std::ctime(&now);
        counter += 10;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Simulate work
        now = std::time(nullptr);
        childLog << "Child Process 1 ID: " << getpid() << ", Exit Time: " << std::ctime(&now);
        childLog.close();
        exit(0);
    }
}

void createChildProcess2() {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        std::ofstream childLog("log.txt", std::ios::app);
        std::time_t now = std::time(nullptr);
        childLog << "Child Process 2 ID: " << getpid() << ", Start Time: " << std::ctime(&now);
        counter *= 2;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        counter /= 2;
        now = std::time(nullptr);
        childLog << "Child Process 2 ID: " << getpid() << ", Exit Time: " << std::ctime(&now);
        childLog.close();
        exit(0);
    }
}

void spawnChildProcesses() {
    static std::atomic<bool> childRunning1(false);
    static std::atomic<bool> childRunning2(false);

    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        
        if (!childRunning1) {
            childRunning1 = true;
            createChildProcess1();
            childRunning1 = false;
        } else {
            log("Child Process 1 is still running, not spawning again.");
        }

        if (!childRunning2) {
            childRunning2 = true;
            createChildProcess2();
            childRunning2 = false;
        } else {
            log("Child Process 2 is still running, not spawning again.");
        }
    }
}

void userInput() {
    while (isRunning) {
        std::string input;
        std::cout << "Enter new counter value (or type 'exit' to quit): ";
        std::getline(std::cin, input);
        if (input == "exit") {
            isRunning = false;
        } else {
            try {
                int newValue = std::stoi(input);
                counter = newValue;
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid input. Please enter a number." << std::endl;
            }
        }
    }
}

int main() {
    logFile.open("log.txt", std::ios::app);
    writeLogHeader();

    std::thread timer(timerFunction);
    std::thread logger(logCurrentStatus);
    std::thread spawner(spawnChildProcesses);
    std::thread inputThread(userInput);

    timer.join();
    logger.join();
    spawner.join();
    inputThread.join();

    logFile.close();
    return 0;
}
