
#include <fstream>
#include <iostream>
#include "Header.h"
using namespace std;

// Загрузка сотрудников из файла
void loadFromFile(const char* filename, Employee* employees, int& employeeCount, int max_size) {
    ifstream file(filename);
    if (file.is_open()) {
        while (file >> employees[employeeCount].firstName
            >> employees[employeeCount].lastName
            >> employees[employeeCount].phoneNumber
            >> employees[employeeCount].salary) {
            if (employeeCount < max_size) {
                ++employeeCount;
            }
        }
        file.close();
    }
    else {
        cerr << "Не удалось открыть файл для чтения!" << endl;
    }
}

// Сохранение сотрудников в файл
void saveToFile(const char* filename, Employee* employees, int employeeCount) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < employeeCount; ++i) {
            file << employees[i].firstName << " " << employees[i].lastName << " "
                << employees[i].phoneNumber << " " << employees[i].salary << endl;
        }
        file.close();
    }
    else {
        cerr << "Не удалось открыть файл для записи!" << endl;
    }
}

// Отображение всех сотрудников
void displayAll(const Employee* employees, int employeeCount) {
    for (int i = 0; i < employeeCount; ++i) {
       cout << "Имя: " << employees[i].firstName
            << ", Фамилия: " << employees[i].lastName
            << ", Телефон: " << employees[i].phoneNumber
            << ", Зарплата: " << employees[i].salary << endl;
    }
}

// Поиск по фамилии
void searchByLastName(const char* lastName, const Employee* employees, int employeeCount) {
    bool found = false;
    for (int i = 0; i < employeeCount; ++i) {
        if (strcmp(employees[i].lastName, lastName) == 0) {
            cout << "Имя: " << employees[i].firstName
                << ", Фамилия: " << employees[i].lastName
                << ", Телефон: " << employees[i].phoneNumber
                << ", Зарплата: " << employees[i].salary << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Сотрудник с фамилией " << lastName << " не найден." << endl;
    }
}

// Поиск по диапазону зарплат
void searchBySalaryRange(double minSalary, double maxSalary, const Employee* employees, int employeeCount) {
    bool found = false;
    for (int i = 0; i < employeeCount; ++i) {
        if (employees[i].salary >= minSalary && employees[i].salary <= maxSalary) {
            cout << "Имя: " << employees[i].firstName
                << ", Фамилия: " << employees[i].lastName
                << ", Телефон: " << employees[i].phoneNumber
                << ", Зарплата: " << employees[i].salary << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Сотрудники с зарплатой в диапазоне " << minSalary << "-" << maxSalary << " не найдены." << endl;
    }
}

// Сортировка по фамилии (пузырьковая сортировка)
void sortByLastName(Employee* employees, int employeeCount) {
    for (int i = 0; i < employeeCount - 1; ++i) {
        for (int j = 0; j < employeeCount - i - 1; ++j) {
            if (strcmp(employees[j].lastName, employees[j + 1].lastName) > 0) {
                // Обмен местами
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    cout << "Сотрудники отсортированы по фамилии." << endl;
}

// Добавление сотрудника
void addEmployee(Employee* employees, int& employeeCount, int max_size) {
    if (employeeCount >= max_size) {
        cout << "Массив сотрудников переполнен!" << endl;
        return;
    }

    Employee newEmployee;

    cout << "Введите имя: ";
    cin >> newEmployee.firstName;
    cout << "Введите фамилию: ";
    cin >> newEmployee.lastName;

    do {
        cout << "Введите номер телефона в формате (063) 5635904: ";
        cin >> newEmployee.phoneNumber;
    } while (!isValidPhoneNumber(newEmployee.phoneNumber));

    cout << "Введите зарплату: ";
    cin >> newEmployee.salary;

    employees[employeeCount++] = newEmployee;
    cout << "Сотрудник добавлен." << endl;
}

// Удаление сотрудника
void deleteEmployee(Employee* employees, int& employeeCount) {
    char lastName[50];
    cout << "Введите фамилию сотрудника для удаления: ";
    cin >> lastName;

    for (int i = 0; i < employeeCount; ++i) {
        if (strcmp(employees[i].lastName, lastName) == 0) {
            if (confirmDeletion()) {
                for (int j = i; j < employeeCount - 1; ++j) {
                    employees[j] = employees[j + 1];
                }
                --employeeCount;
                cout << "Сотрудник удален." << endl;
                return;
            }
            else {
                cout << "Удаление отменено." << endl;
                return;
            }
        }
    }
    cout << "Сотрудник с фамилией " << lastName << " не найден." << endl;
}

// Проверка корректности номера телефона
bool isValidPhoneNumber(const char* phoneNumber) {
    if (strlen(phoneNumber) != 13) return false;
    if (phoneNumber[0] != '(' || phoneNumber[4] != ')' || phoneNumber[5] != ' ') return false;

    for (int i = 1; i < 4; ++i) {
        if (!isdigit(phoneNumber[i])) return false;
    }
    for (int i = 6; i < 13; ++i) {
        if (!isdigit(phoneNumber[i])) return false;
    }
    return true;
}

// Подтверждение удаления
bool confirmDeletion() {
    char choice;
    cout << "Вы уверены, что хотите удалить сотрудника? (y/n): ";
    cin >> choice;
    return choice == 'y' || choice == 'Y';
}
