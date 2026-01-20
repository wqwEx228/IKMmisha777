#include "phonebook.h"
#include "validator.h"
#include <iostream>
#include <limits>
#include <windows.h>

// Функция для отображения меню
void showMenu() {
    std::cout << "\n=== Умный телефонный справочник ===\n";
    std::cout << "1. Показать все контакты\n";
    std::cout << "2. Добавить контакт\n";
    std::cout << "3. Поиск контакта\n";
    std::cout << "4. Редактировать контакт\n";
    std::cout << "5. Удалить контакт\n";
    std::cout << "6. Сортировать контакты по имени\n";
    std::cout << "7. Сохранить в файл\n";
    std::cout << "8. Загрузить из файла\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

// Функция для получения числового ввода с проверкой
int getValidNumber(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Введите число от " << min << " до " << max << ".\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value >= min && value <= max) {
            return value;
        }

        std::cout << "Число должно быть от " << min << " до " << max << ".\n";
    }
}

// Главная функция
int main() {
    system("chcp 65001");

    std::vector<Contact> contacts;
    const std::string filename = "contacts.txt";

    // Загружаем данные из файла при старте
    loadFromFile(contacts, filename);

    bool running = true;

    while (running) {
        showMenu();

        // Получаем выбор пользователя с проверкой
        int choice = getValidNumber("", 0, 8);

        switch (choice) {
            case 0: {
                std::cout << "Выход из программы...\n";

                // Предлагаем сохранить перед выходом
                std::cout << "\nХотите сохранить изменения перед выходом? (1 - да, 0 - нет): ";
                int saveChoice = getValidNumber("", 0, 1);

                if (saveChoice == 1) {
                    saveToFile(contacts, filename);
                    std::cout << "Изменения сохранены.\n";
                }

                running = false;
                break;
            }

            case 1: {
                displayContacts(contacts);
                break;
            }

            case 2: {
                addContact(contacts);
                break;
            }

            case 3: {
                searchContact(contacts);
                break;
            }

            case 4: {
                editContact(contacts);
                break;
            }

            case 5: {
                deleteContact(contacts);
                break;
            }

            case 6: {
                sortContacts(contacts);
                std::cout << "\nСортировка завершена. Текущий список:\n";
                displayContacts(contacts);
                break;
            }

            case 7: {
                saveToFile(contacts, filename);
                break;
            }

            case 8: {
                loadFromFile(contacts, filename);
                break;
            }

            default: {
                std::cout << "Неверный выбор. Попробуйте снова.\n";
                break;
            }
        }
    }

    std::cout << "Спасибо за использование программы!\n";
    return 0;
}