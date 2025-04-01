/**
 * @file yosys_example.cpp
 * @brief Пример использования YosysUtils для оптимизации схемы
 * @details Этот пример демонстрирует, как использовать библиотеку для оптимизации
 * схемы с помощью Yosys и конвертации в формат FIRRTL.
 */

#include <iostream>
#include <string>
#include <YosysUtils.hpp>

/**
 * Пример использования YosysUtils для оптимизации схемы и конвертации форматов.
 * Этот пример показывает:
 * 1. Как оптимизировать Verilog-файл
 * 2. Как конвертировать Verilog-файл в формат FIRRTL
 * 3. Как обработать результаты выполнения команд
 */
int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <входной_файл> <выходной_файл>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];
    
    // Оптимизация Verilog-файла
    std::cout << "Оптимизация Verilog-файла..." << std::endl;
    CommandWorkResult optResult = YosysUtils::optVerilog(inputFileName, outputFileName + "_opt.v");
    
    if (!optResult.correct) {
        std::cerr << "Ошибка при оптимизации Verilog-файла." << std::endl;
        return 1;
    }
    
    std::cout << "Verilog-файл успешно оптимизирован." << std::endl;
    
    // Конвертация в FIRRTL
    std::cout << std::endl << "Конвертация в формат FIRRTL..." << std::endl;
    CommandWorkResult firrtlResult = YosysUtils::writeFirrtl(inputFileName, outputFileName + ".fir");
    
    if (!firrtlResult.correct) {
        std::cerr << "Ошибка при конвертации в формат FIRRTL." << std::endl;
        return 1;
    }
    
    std::cout << "Verilog-файл успешно конвертирован в формат FIRRTL." << std::endl;
    
    return 0;
} 