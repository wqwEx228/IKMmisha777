#include "validator.h"
#include <iostream>
#include <algorithm>
#include <cctype>

// Простая проверка имени - принимаем любые символы, кроме пустой строки и некоторых спецсимволов
bool Validator::isValidNameSimple(const std::string& name) {
    if (name.empty()) return false;

    // Проверяем, что имя не состоит только из пробелов
    bool hasNonSpace = false;
    for (char ch : name) {
        if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r') {
            hasNonSpace = true;
            break;
        }
    }

    if (!hasNonSpace) return false;

    // Запрещаем некоторые спецсимволы
    std::string forbidden = "@#$%^&*()_+=[]{}|\\:;\"<>?/`~";
    for (char ch : name) {
        if (forbidden.find(ch) != std::string::npos) {
            return false;
        }
    }

    return true;
}

// Функция для получения корректного имени
std::string Validator::getValidNameSimple(const std::string& prompt) {
    std::string name;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, name);

        // Убираем начальные и конечные пробелы
        size_t start = name.find_first_not_of(" \t\n\r");
        size_t end = name.find_last_not_of(" \t\n\r");

        if (start == std::string::npos) {
            std::cout << "Имя не может быть пустым! Попробуйте снова.\n";
            continue;
        }

        name = name.substr(start, end - start + 1);

        if (name.empty()) {
            std::cout << "Имя не может быть пустым! Попробуйте снова.\n";
            continue;
        }

        // Проверяем запрещенные символы
        std::string forbidden = "@#$%^&*()_+=[]{}|\\:;\"<>?/`~";
        bool hasForbidden = false;
        for (char ch : name) {
            if (forbidden.find(ch) != std::string::npos) {
                hasForbidden = true;
                break;
            }
        }

        if (hasForbidden) {
            std::cout << "Имя содержит недопустимые символы! Разрешены буквы, цифры, пробелы, дефисы, точки, запятые.\n";
            continue;
        }

        return name;
    }
}

// Основная функция проверки имени (использует упрощенную версию)
bool Validator::isValidName(const std::string& name) {
    return isValidNameSimple(name);
}

// Функция для получения корректного имени
std::string Validator::getValidName(const std::string& prompt) {
    return getValidNameSimple(prompt);
}

// Проверка телефона
bool Validator::isValidPhone(const std::string& phone) {
    if (phone.empty()) return false;

    for (char ch : phone) {
        unsigned char c = static_cast<unsigned char>(ch);
        if (!std::isdigit(c) &&
            ch != '+' && ch != '-' && ch != ' ' &&
            ch != '(' && ch != ')' && ch != '.') {
            return false;
        }
    }

    // Проверяем, что есть хотя бы одна цифра
    return std::any_of(phone.begin(), phone.end(),
                       [](char ch) {
                           return std::isdigit(static_cast<unsigned char>(ch));
                       });
}

// Проверка email
bool Validator::isValidEmail(const std::string& email) {
    if (email.empty()) return false;

    // Простая проверка email с помощью регулярного выражения
    try {
        std::regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
        return std::regex_match(email, emailPattern);
    } catch (...) {
        // Если regex не поддерживается, используем простую проверку
        size_t atPos = email.find('@');
        if (atPos == std::string::npos || atPos == 0 || atPos == email.length() - 1) {
            return false;
        }

        size_t dotPos = email.find('.', atPos);
        if (dotPos == std::string::npos || dotPos == email.length() - 1) {
            return false;
        }

        // Проверяем допустимые символы
        for (char ch : email) {
            unsigned char c = static_cast<unsigned char>(ch);
            if (!std::isalnum(c) && ch != '.' && ch != '_' && ch != '%' &&
                ch != '+' && ch != '-' && ch != '@') {
                return false;
            }
        }

        return true;
    }
}

// Получение корректного телефона
std::string Validator::getValidPhone(const std::string& prompt) {
    std::string phone;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, phone);

        if (isValidPhone(phone)) {
            return phone;
        }
        std::cout << "Неверный телефон! Используйте только цифры, +, -, пробелы, скобки.\n";
        std::cout << "Пример: +7 (999) 123-45-67 или 89991234567\n";
    }
}

// Получение корректного email
std::string Validator::getValidEmail(const std::string& prompt) {
    std::string email;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, email);

        if (isValidEmail(email)) {
            return email;
        }
        std::cout << "Неверный email! Формат: username@domain.com\n";
    }
}

// Функция для приведения строки к нижнему регистру
std::string Validator::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) -> unsigned char {
                       // Английские буквы
                       if (c >= 'A' && c <= 'Z') {
                           return c + ('a' - 'A');
                       }
                       // Русские буквы (Windows-1251)
                       if (c >= 192 && c <= 223) {
                           return c + 32; // А-Я -> а-я
                       }
                       if (c == 168) {
                           return 184; // Ё -> ё
                       }
                       return c;
                   });
    return result;
}