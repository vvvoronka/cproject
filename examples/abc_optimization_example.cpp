/**
 * @file abc_optimization_example.cpp
 * @brief Пример использования AbcUtils для оптимизации схемы
 * @details Этот пример демонстрирует, как использовать библиотеку для оптимизации
 * схемы с помощью ABC.
 */

#include <iostream>
#include <string>
#include <AbcUtils.hpp>

/**
 * Пример использования AbcUtils для оптимизации схемы.
 * Этот пример показывает:
 * 1. Как получить статистику о схеме
 * 2. Как выполнить оптимизацию схемы
 * 3. Как обработать результаты выполнения команд
 */
int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <путь_к_файлу> <имя_библиотеки>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string libName = argv[2];

    // Получение статистики перед оптимизацией
    std::cout << "Получение статистики перед оптимизацией..." << std::endl;
    CommandWorkResult statsBeforeResult = AbcUtils::getStats(inputFileName, libName);
    
    if (!statsBeforeResult.correct) {
        std::cerr << "Ошибка при получении статистики." << std::endl;
        return 1;
    }
    
    // Вывод статистики перед оптимизацией
    for (const auto& output : statsBeforeResult.commandsOutput) {
        std::cout << "Команда: " << output.first << std::endl;
        std::cout << "Результат:" << std::endl << output.second << std::endl;
    }
    
    // Выполнение оптимизации
    std::cout << std::endl << "Выполнение оптимизации..." << std::endl;
    CommandWorkResult optimizationResult = AbcUtils::optimizeWithLib(inputFileName, libName);
    
    if (!optimizationResult.correct) {
        std::cerr << "Ошибка при оптимизации схемы." << std::endl;
        return 1;
    }
    
    // Получение статистики после оптимизации
    std::cout << std::endl << "Получение статистики после оптимизации..." << std::endl;
    CommandWorkResult statsAfterResult = AbcUtils::getStats(inputFileName, libName);
    
    if (!statsAfterResult.correct) {
        std::cerr << "Ошибка при получении статистики после оптимизации." << std::endl;
        return 1;
    }
    
    // Вывод статистики после оптимизации
    for (const auto& output : statsAfterResult.commandsOutput) {
        std::cout << "Команда: " << output.first << std::endl;
        std::cout << "Результат:" << std::endl << output.second << std::endl;
    }
    
    std::cout << std::endl << "Оптимизация успешно завершена." << std::endl;
    return 0;
} 