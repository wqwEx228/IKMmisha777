#include "phonebook.h"
#include "validator.h"
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>

// Добавление контакта
void addContact(std::vector<Contact>& contacts) {
    Contact newContact;

    std::cout << "\n=== Добавление нового контакта ===\n";
    newContact.name = Validator::getValidName("Введите имя: ");
    newContact.phone = Validator::getValidPhone("Введите номер телефона: ");
    newContact.email = Validator::getValidEmail("Введите email (формат: user@domain.com): ");

    contacts.push_back(newContact);
    std::cout << "Контакт успешно добавлен!\n";
}

// Отображение всех контактов
void displayContacts(const std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "\nСправочник пуст.\n";
        return;
    }

    std::cout << "\n=== Телефонный справочник ===\n";
    std::cout << std::left << std::setw(25) << "Имя"
              << std::setw(20) << "Телефон"
              << std::setw(30) << "Email" << "\n";
    std::cout << std::string(75, '-') << "\n";

    for (const auto& contact : contacts) {
        std::cout << std::left << std::setw(25) << contact.name
                  << std::setw(20) << contact.phone
                  << std::setw(30) << contact.email << "\n";
    }
}

// Поиск по части имени
void searchContact(const std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "\nСправочник пуст.\n";
        return;
    }

    std::string searchTerm;
    std::cout << "\n=== Поиск контакта ===\n";
    std::cout << "Введите часть имени для поиска: ";
    std::getline(std::cin, searchTerm);

    std::string searchLower = Validator::toLower(searchTerm);
    bool found = false;

    std::cout << "\nРезультаты поиска:\n";
    std::cout << std::left << std::setw(25) << "Имя"
              << std::setw(20) << "Телефон"
              << std::setw(30) << "Email" << "\n";
    std::cout << std::string(75, '-') << "\n";

    for (const auto& contact : contacts) {
        if (Validator::toLower(contact.name).find(searchLower) != std::string::npos) {
            std::cout << std::left << std::setw(25) << contact.name
                      << std::setw(20) << contact.phone
                      << std::setw(30) << contact.email << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "Контакты не найдены.\n";
    }
}

// Редактирование контакта
void editContact(std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "\nСправочник пуст.\n";
        return;
    }

    displayContacts(contacts);

    int index;
    std::cout << "\n=== Редактирование контакта ===\n";
    std::cout << "Введите номер контакта для редактирования (1-" << contacts.size() << "): ";

    if (!(std::cin >> index)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод.\n";
        return;
    }
    std::cin.ignore();

    if (index < 1 || index > contacts.size()) {
        std::cout << "Неверный номер контакта.\n";
        return;
    }

    Contact& contact = contacts[index - 1];

    std::cout << "\nТекущая информация:\n";
    std::cout << "1. Имя: " << contact.name << "\n";
    std::cout << "2. Телефон: " << contact.phone << "\n";
    std::cout << "3. Email: " << contact.email << "\n";

    int choice;
    std::cout << "\nЧто вы хотите изменить?\n";
    std::cout << "1. Имя\n2. Телефон\n3. Email\n4. Все поля\nВаш выбор: ";

    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод.\n";
        return;
    }
    std::cin.ignore();

    switch (choice) {
        case 1:
            contact.name = Validator::getValidName("Введите новое имя: ");
            break;
        case 2:
            contact.phone = Validator::getValidPhone("Введите новый номер телефона: ");
            break;
        case 3:
            contact.email = Validator::getValidEmail("Введите новый email (формат: user@domain.com): ");
            break;
        case 4:
            contact.name = Validator::getValidName("Введите новое имя: ");
            contact.phone = Validator::getValidPhone("Введите новый номер телефона: ");
            contact.email = Validator::getValidEmail("Введите новый email (формат: user@domain.com): ");
            break;
        default:
            std::cout << "Неверный выбор.\n";
            return;
    }

    std::cout << "Контакт успешно обновлен!\n";
}

// Удаление контакта
void deleteContact(std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "\nСправочник пуст.\n";
        return;
    }

    displayContacts(contacts);

    int index;
    std::cout << "\n=== Удаление контакта ===\n";
    std::cout << "Введите номер контакта для удаления (1-" << contacts.size() << "): ";

    if (!(std::cin >> index)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод.\n";
        return;
    }
    std::cin.ignore();

    if (index < 1 || index > contacts.size()) {
        std::cout << "Неверный номер контакта.\n";
        return;
    }

    std::cout << "Вы уверены, что хотите удалить контакт \""
              << contacts[index - 1].name << "\"? (1 - да, 0 - нет): ";
    int confirm;
    if (!(std::cin >> confirm)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод.\n";
        return;
    }
    std::cin.ignore();

    if (confirm == 1) {
        contacts.erase(contacts.begin() + index - 1);
        std::cout << "Контакт успешно удален!\n";
    } else {
        std::cout << "Удаление отменено.\n";
    }
}

// Сортировка контактов по имени
void sortContacts(std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "\nСправочник пуст.\n";
        return;
    }

    std::sort(contacts.begin(), contacts.end(),
              [](const Contact& a, const Contact& b) {
                  return Validator::toLower(a.name) < Validator::toLower(b.name);
              });

    std::cout << "Контакты отсортированы по имени.\n";
}

// Сохранение в файл
void saveToFile(const std::vector<Contact>& contacts, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла для записи.\n";
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.name << "\n"
             << contact.phone << "\n"
             << contact.email << "\n";
    }

    file.close();
    std::cout << "Данные сохранены в файл: " << filename << "\n";
}

// Загрузка из файла
void loadFromFile(std::vector<Contact>& contacts, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Файл не найден. Будет создан новый.\n";
        return;
    }

    contacts.clear();
    Contact contact;
    int loadedCount = 0;

    while (std::getline(file, contact.name) &&
           std::getline(file, contact.phone) &&
           std::getline(file, contact.email)) {

        // Валидация данных при загрузке
        if (!contact.name.empty() &&
            Validator::isValidPhone(contact.phone) &&
            Validator::isValidEmail(contact.email)) {
            contacts.push_back(contact);
            loadedCount++;
        }
    }

    file.close();
    std::cout << "Данные загружены из файла: " << filename << "\n";
    std::cout << "Загружено контактов: " << loadedCount << "\n";
}