/**
 * @file StandartUtils.hpp
 * @brief Стандартные утилиты для работы с командами и форматированием
 * @details Содержит структуры и функции для обработки команд, их результатов и форматирования строк
 */

#ifndef STANDART_UTIL_H
#define STANDART_UTIL_H

#include <map>
#include <sstream>
#include <string>
#include <tuple>

/**
 * @struct StandartCommandInfo
 * @brief Структура для хранения информации о многострочных командах
 * @details Используется для передачи информации о командах для abc, yosys и т.д.
 */
struct StandartCommandInfo {
  /// @brief Длина команды
  int sumLen;
  /// @brief Информация о том, какая команда вызвала ошибку
  std::string info;
};

/**
 * @struct CommandWorkResult
 * @brief Результат выполнения команды
 * @details Содержит информацию о корректности выполнения и вывод команд
 */
struct CommandWorkResult {
  /// @brief Флаг успешности выполнения команды
  bool correct;
  /// @brief Мапа с выводом команд, где ключ - имя команды, значение - её вывод
  std::map<std::string, std::string> commandsOutput;
};

/**
 * @namespace StandartUtils
 * @brief Пространство имен для стандартных утилит
 * @details Содержит функции форматирования и вспомогательные структуры
 */
namespace StandartUtils {
// link on used code - https://gist.github.com/en4bz/f07ef13706c3ae3a4fb2

/**
 * @struct TuplePrinter
 * @brief Вспомогательная структура для форматирования строк с использованием кортежей
 * @tparam Tuple Тип кортежа
 * @tparam N Размер кортежа
 */
template <class Tuple, std::size_t N>
struct TuplePrinter {
  /**
   * @brief Печать форматированной строки с использованием значений из кортежа
   * @param fmt Формат строки
   * @param os Поток вывода
   * @param t Кортеж с данными
   */
  static void print(const std::string& fmt, std::ostream& os, const Tuple& t) {
    const size_t idx = fmt.find_last_of('%');
    TuplePrinter<Tuple, N - 1>::print(std::string(fmt, 0, idx), os, t);
    os << std::get<N - 1>(t) << std::string(fmt, idx + 1);
  }
};

/**
 * @struct TuplePrinter<Tuple, 1>
 * @brief Специализация TuplePrinter для кортежа размера 1
 * @tparam Tuple Тип кортежа
 */
template <class Tuple>
struct TuplePrinter<Tuple, 1> {
  /**
   * @brief Печать форматированной строки с использованием значения из кортежа размера 1
   * @param fmt Формат строки
   * @param os Поток вывода
   * @param t Кортеж с данными
   */
  static void print(const std::string& fmt, std::ostream& os, const Tuple& t) {
    const size_t idx = fmt.find_first_of('%');
    os << std::string(fmt, 0, idx) << std::get<0>(t)
       << std::string(fmt, idx + 1);
  }
};

/**
 * @brief Форматирование строки с использованием переданных аргументов
 * @tparam Args Типы аргументов
 * @param fmt Формат строки, где % используется как заполнитель
 * @param args Аргументы для подстановки
 * @return std::string Отформатированная строка
 */
template <class... Args>
std::string format(const std::string& fmt, Args&&... args) {
  std::stringstream ss;

  const auto t = std::make_tuple(std::forward<Args>(args)...);

  TuplePrinter<decltype(t), sizeof...(Args)>::print(fmt, ss, t);
  return ss.str();
}

}  // namespace StandartUtils

#endif