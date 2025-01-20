#!/bin/bash

# Логирование
log_file="/home/almaz/kiosk_project/script.log"
echo "$(date): Скрипт запущен" >> "$log_file"

# Уведомление о запуске
notify-send "Скрипт запущен" "Скрипт для записи температуры запущен успешно."

# Запуск вашего приложения
/home/almaz/kiosk_project/temperature_logger &

# Пример: просто выводим сообщение в терминал
echo "Запуск приложения для записи температуры..."

# Дайте знать, что скрипт завершился
echo "$(date): Скрипт завершен" >> "$log_file"
