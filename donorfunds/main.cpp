// donorfunds
// main.cpp

// main cpp file for the donnorfunds and timesheet algorithym

// Created by: Ostolaza
// Date: 2024-06-26

#include "displaymenu.hpp"
#include "donorfunds.hpp"
#include <iostream>

using namespace std;
 
int main() {
    EmployeeManager manager;

    while (true) {
        displayMainMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee(manager);
                break;
            case 2:
                signInEmployee(manager);
                break;
            case 3:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again. " << endl;
        }
    }
    
    return 0;
}
