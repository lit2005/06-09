
#include <fstream>
#include <iostream>
#include "Header.h"
using namespace std;

// �������� ����������� �� �����
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
        cerr << "�� ������� ������� ���� ��� ������!" << endl;
    }
}

// ���������� ����������� � ����
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
        cerr << "�� ������� ������� ���� ��� ������!" << endl;
    }
}

// ����������� ���� �����������
void displayAll(const Employee* employees, int employeeCount) {
    for (int i = 0; i < employeeCount; ++i) {
       cout << "���: " << employees[i].firstName
            << ", �������: " << employees[i].lastName
            << ", �������: " << employees[i].phoneNumber
            << ", ��������: " << employees[i].salary << endl;
    }
}

// ����� �� �������
void searchByLastName(const char* lastName, const Employee* employees, int employeeCount) {
    bool found = false;
    for (int i = 0; i < employeeCount; ++i) {
        if (strcmp(employees[i].lastName, lastName) == 0) {
            cout << "���: " << employees[i].firstName
                << ", �������: " << employees[i].lastName
                << ", �������: " << employees[i].phoneNumber
                << ", ��������: " << employees[i].salary << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "��������� � �������� " << lastName << " �� ������." << endl;
    }
}

// ����� �� ��������� �������
void searchBySalaryRange(double minSalary, double maxSalary, const Employee* employees, int employeeCount) {
    bool found = false;
    for (int i = 0; i < employeeCount; ++i) {
        if (employees[i].salary >= minSalary && employees[i].salary <= maxSalary) {
            cout << "���: " << employees[i].firstName
                << ", �������: " << employees[i].lastName
                << ", �������: " << employees[i].phoneNumber
                << ", ��������: " << employees[i].salary << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "���������� � ��������� � ��������� " << minSalary << "-" << maxSalary << " �� �������." << endl;
    }
}

// ���������� �� ������� (����������� ����������)
void sortByLastName(Employee* employees, int employeeCount) {
    for (int i = 0; i < employeeCount - 1; ++i) {
        for (int j = 0; j < employeeCount - i - 1; ++j) {
            if (strcmp(employees[j].lastName, employees[j + 1].lastName) > 0) {
                // ����� �������
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    cout << "���������� ������������� �� �������." << endl;
}

// ���������� ����������
void addEmployee(Employee* employees, int& employeeCount, int max_size) {
    if (employeeCount >= max_size) {
        cout << "������ ����������� ����������!" << endl;
        return;
    }

    Employee newEmployee;

    cout << "������� ���: ";
    cin >> newEmployee.firstName;
    cout << "������� �������: ";
    cin >> newEmployee.lastName;

    do {
        cout << "������� ����� �������� � ������� (063) 5635904: ";
        cin >> newEmployee.phoneNumber;
    } while (!isValidPhoneNumber(newEmployee.phoneNumber));

    cout << "������� ��������: ";
    cin >> newEmployee.salary;

    employees[employeeCount++] = newEmployee;
    cout << "��������� ��������." << endl;
}

// �������� ����������
void deleteEmployee(Employee* employees, int& employeeCount) {
    char lastName[50];
    cout << "������� ������� ���������� ��� ��������: ";
    cin >> lastName;

    for (int i = 0; i < employeeCount; ++i) {
        if (strcmp(employees[i].lastName, lastName) == 0) {
            if (confirmDeletion()) {
                for (int j = i; j < employeeCount - 1; ++j) {
                    employees[j] = employees[j + 1];
                }
                --employeeCount;
                cout << "��������� ������." << endl;
                return;
            }
            else {
                cout << "�������� ��������." << endl;
                return;
            }
        }
    }
    cout << "��������� � �������� " << lastName << " �� ������." << endl;
}

// �������� ������������ ������ ��������
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

// ������������� ��������
bool confirmDeletion() {
    char choice;
    cout << "�� �������, ��� ������ ������� ����������? (y/n): ";
    cin >> choice;
    return choice == 'y' || choice == 'Y';
}
