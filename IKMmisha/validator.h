#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <regex>

class Validator {
public:
    // Основные функции валидации
    static bool isValidName(const std::string& name);
    static bool isValidPhone(const std::string& phone);
    static bool isValidEmail(const std::string& email);

    // Функции для получения корректных данных
    static std::string getValidName(const std::string& prompt);
    static std::string getValidPhone(const std::string& prompt);
    static std::string getValidEmail(const std::string& prompt);

    // Вспомогательные функции
    static std::string toLower(const std::string& str);

private:
    // Упрощенная проверка имени
    static bool isValidNameSimple(const std::string& name);
    static std::string getValidNameSimple(const std::string& prompt);
};

#endif