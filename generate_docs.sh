#!/bin/bash

# Проверка наличия Doxygen
if ! command -v doxygen &> /dev/null; then
    echo "Ошибка: Doxygen не установлен."
    echo "Установите Doxygen для генерации документации:"
    echo "  - В Ubuntu/Debian: sudo apt-get install doxygen"
    echo "  - В macOS: brew install doxygen"
    exit 1
fi

# Проверка наличия конфигурационного файла
if [ ! -f Doxyfile ]; then
    echo "Ошибка: Файл Doxyfile не найден в текущей директории."
    exit 1
fi

# Создание директории для документации, если её нет
if [ ! -d docs ]; then
    mkdir -p docs
fi

# Запуск Doxygen
echo "Генерация документации..."
doxygen Doxyfile

# Проверка результата
if [ $? -eq 0 ]; then
    echo "Документация успешно сгенерирована в директории docs/"
    echo "Откройте docs/html/index.html в браузере для просмотра."
else
    echo "Ошибка при генерации документации."
    exit 1
fi 