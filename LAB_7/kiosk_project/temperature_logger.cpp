#include <iostream>
#include <fstream>
#include <ctime>

int main() {
    std::ofstream outfile("temperature_log.txt", std::ios::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    
    // Здесь вы можете добавить код для получения данных о температуре
    float temperature = 25.0; // Замените на реальное значение температуры
    
    outfile << "Temperature recorded at: " << dt << " - " << temperature << "°C" << std::endl;
    outfile.close();
    
    return 0;
}
