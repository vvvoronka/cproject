/**
 * @file YosysUtils.hpp
 * @brief Набор утилит для работы с Yosys
 * @details Класс предоставляет функциональность для базовой работы с Yosys.
 * Позволяет читать файлы Verilog, выполнять оптимизации и конвертировать в различные форматы.
 */

#ifndef YOSYS_UTILS_H
#define YOSYS_UTILS_H

#include <string>
#include <vector>

#include "StandartUtils.hpp"

/*
This class is made for basic work with yosys.
Using it, it is possible to read verlog file,
make opt and to write file into verilog
*/

/**
 * @namespace YosysUtils
 * @brief Пространство имен для утилит, работающих с Yosys
 * @details Содержит функции для чтения/записи Verilog файлов,
 * выполнения оптимизаций схем и конвертации в другие форматы
 */
namespace YosysUtils {

/**
 * @defgroup YosysOperations Операции с Yosys
 * @brief Функции для выполнения основных операций с использованием Yosys
 * @{
 */

/**
 * @brief Оптимизирует Verilog-файл
 * @param i_inputFileName Имя входного файла
 * @param i_outputFileName Имя выходного файла
 * @param i_directory Директория с файлами (по умолчанию ".")
 * @return CommandWorkResult Результат выполнения команды
 */
CommandWorkResult optVerilog(std::string i_inputFileName,
                             std::string i_outputFileName,
                             std::string i_directory = ".");

/**
 * @brief Конвертирует Verilog-файл в формат FIRRTL
 * @param i_inputFileName Имя входного файла
 * @param i_outputFileName Имя выходного файла
 * @param i_directory Директория с файлами (по умолчанию ".")
 * @return CommandWorkResult Результат выполнения команды
 */
CommandWorkResult writeFirrtl(std::string i_inputFileName,
                              std::string i_outputFileName,
                              std::string i_directory = ".");

/** @} */ // конец группы YosysOperations

/**
 * @defgroup YosysCommandExecution Выполнение команд Yosys
 * @brief Функции для выполнения команд Yosys
 * @{
 */

/**
 * @brief Разбор команды на компоненты
 * @param i_command Команда для разбора
 * @return std::vector<StandartCommandInfo> Вектор информации о командах
 * @note IMPORTANT parseAll здесь установлен TRUE
 */
std::vector<StandartCommandInfo> parseCommand(std::string i_command);

/**
 * @brief Стандартное выполнение команды
 * @param i_command Команда для выполнения
 * @param i_info Информация о команде
 * @return CommandWorkResult Результат выполнения команды
 */
CommandWorkResult standartExecutor(std::string i_command,
                                   std::vector<StandartCommandInfo> i_info);

/**
 * @brief Шаблонная функция для выполнения команд
 * @tparam Args Типы аргументов для форматирования команды
 * @param i_command Шаблон команды
 * @param executableFunc Функция-исполнитель
 * @param filenames Аргументы для форматирования команды
 * @return CommandWorkResult Результат выполнения команды
 */
template <typename... Args>
CommandWorkResult runCommand(const std::string& i_command,
                             CommandWorkResult (*executableFunc)(
                                 std::string, std::vector<StandartCommandInfo>),
                             Args&&... filenames) {
  std::string command = StandartUtils::format(i_command, filenames...);

  return executableFunc(command, parseCommand(command));
}

/** @} */ // конец группы YosysCommandExecution

}  // namespace YosysUtils

#endif