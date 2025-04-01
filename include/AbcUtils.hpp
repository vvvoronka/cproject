/**
 * @file AbcUtils.hpp
 * @brief Набор утилит для работы с ABC (Berkeley-abc)
 * @details Класс предоставляет функциональность для базовой работы с ABC.
 * Позволяет читать файлы Verilog, файлы AIGER, выполнять оптимизации и т.д.
 */

#ifndef ABC_UTILS_H
#define ABC_UTILS_H

#include <string>
#include <vector>

#include "StandartUtils.hpp"

/**
 * @namespace AbcUtils
 * @brief Пространство имен для утилит, работающих с ABC
 * @details Содержит функции для чтения/записи Verilog/AIGER файлов,
 * выполнения оптимизаций схем и сбора статистики
 */
namespace AbcUtils {

/**
 * @defgroup AbcOptimization Оптимизации с помощью ABC
 * @brief Функции для оптимизации схем с использованием ABC
 * @{
 */

/**
 * @brief Получение статистики по схеме
 * @param i_inputFileName Имя входного файла
 * @param i_libName Имя библиотеки
 * @param i_fileDirectory Директория с файлом (по умолчанию ".")
 * @param i_libDirectory Директория с библиотекой (по умолчанию ".")
 * @return CommandWorkResult Результат выполнения команды с информацией о статистике
 */
CommandWorkResult getStats(std::string i_inputFileName, std::string i_libName,
                           std::string i_fileDirectory = ".",
                           std::string i_libDirectory = ".");

/**
 * @brief Выполнение оптимизации resyn2
 * @param i_inputFileName Имя входного файла
 * @param i_libName Имя библиотеки
 * @param i_fileDirectory Директория с файлом (по умолчанию ".")
 * @param i_libDirectory Директория с библиотекой (по умолчанию ".")
 * @return CommandWorkResult Результат выполнения команды
 */
CommandWorkResult resyn2(std::string i_inputFileName, std::string i_libName,
                         std::string i_fileDirectory = ".",
                         std::string i_libDirectory = ".");

/**
 * @brief Оптимизация схемы с использованием библиотеки
 * @param i_inputFileName Имя входного файла
 * @param i_libName Имя библиотеки
 * @param i_fileDirectory Директория с файлом (по умолчанию ".")
 * @param i_libDirectory Директория с библиотекой (по умолчанию ".")
 * @return CommandWorkResult Результат выполнения команды
 */
CommandWorkResult optimizeWithLib(std::string i_inputFileName,
                                  std::string i_libName,
                                  std::string i_fileDirectory = ".",
                                  std::string i_libDirectory = ".");

/**
 * @brief Конвертация Verilog-файла в формат BENCH
 * @param i_inputFileName Имя входного файла
 * @param i_fileDirectory Директория с файлом (по умолчанию ".")
 * @return CommandWorkResult Результат выполнения конвертации
 */
CommandWorkResult verilogToBench(std::string i_inputFileName,
                                 std::string i_fileDirectory = ".");

/** @} */ // конец группы AbcOptimization

/**
 * @defgroup AbcCommandExecution Выполнение команд ABC
 * @brief Функции для выполнения команд ABC
 * @{
 */

/**
 * @brief Разбор команды на компоненты
 * @param i_command Команда для разбора
 * @return std::vector<StandartCommandInfo> Вектор информации о командах
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
 * @brief Выполнение команды для получения статистики
 * @param i_command Команда для выполнения
 * @param i_info Информация о команде
 * @return CommandWorkResult Результат выполнения команды со статистикой
 */
CommandWorkResult runExecutorForStats(std::string i_command,
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

/** @} */ // конец группы AbcCommandExecution

}  // namespace AbcUtils

#endif