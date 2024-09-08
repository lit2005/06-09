#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <fstream>
#include <cstring>

struct Employee {
    char firstName[50];
    char lastName[50];
    char phoneNumber[15];
    double salary;
};

void loadFromFile(const char* filename, Employee* employees, int& employeeCount, int max_size);
void saveToFile(const char* filename, Employee* employees, int employeeCount);
void displayAll(const Employee* employees, int employeeCount);
void searchByLastName(const char* lastName, const Employee* employees, int employeeCount);
void searchBySalaryRange(double minSalary, double maxSalary, const Employee* employees, int employeeCount);
void sortByLastName(Employee* employees, int employeeCount);
void addEmployee(Employee* employees, int& employeeCount, int max_size);
void deleteEmployee(Employee* employees, int& employeeCount);

bool isValidPhoneNumber(const char* phoneNumber);
bool confirmDeletion();

#endif // EMPLOYEE_H

