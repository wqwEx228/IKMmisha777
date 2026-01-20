#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <iostream>
#include <vector>
#include <string>

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};

// Основные функции
void addContact(std::vector<Contact>& contacts);
void displayContacts(const std::vector<Contact>& contacts);
void searchContact(const std::vector<Contact>& contacts);
void editContact(std::vector<Contact>& contacts);
void deleteContact(std::vector<Contact>& contacts);
void sortContacts(std::vector<Contact>& contacts);
void saveToFile(const std::vector<Contact>& contacts, const std::string& filename);
void loadFromFile(std::vector<Contact>& contacts, const std::string& filename);

#endif