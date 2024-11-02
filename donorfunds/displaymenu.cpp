//
//  displaymenu.cpp
//  donorfunds
//
//  Created by Francisco Ostolaza on 6/28/24.
//

#include "displaymenu.hpp"
#include "donorfunds.hpp"
#include "uniqueId.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <unordered_set>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

void displayMainMenu() {
    cout << "My time & Account Management" << endl;
    cout << "1. New Employee" << endl;
    cout << "2. Current Employee" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

void displaySignInMenu() {
    cout << "Sign In" << endl;
    cout << "Enter employee name: ";
}

void displayTaskMenu() {
    cout << "1. Adjust Timesheet" << endl;
    cout << "2. Adjust Accounts" << endl;
    cout << "3. Create Report" << endl;
    cout << "4. Go Back" << endl;
    cout << "Enter your choice: ";
}

void displayTimesheetTaskMenu() {
    cout << "1. Add Hours" << endl;
    cout << "2. Subtract Hours" << endl;
    cout << "3. Show Employee Hours" << endl;
    cout << "4. Show Employee Total Pay" << endl;
    cout << "5. Go Back" << endl;
    cout << "Enter your choice: ";
}

void displayAccountTaskMenu() {
    cout << "Account Menu" << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Delete Account" << endl;
    cout << "3. Add Funds" << endl;
    cout << "4. Subtract Funds" << endl;
    cout << "5. Show Account Balance" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

void displayReportMenu() {
    cout << "Report Menu" << endl;
    cout << "1. View Report" << endl;
    cout << "2. Export Report" << endl;
    cout << "3. Go Back" << endl;
    cout << "Enter your choice: ";
}

void addEmployee(EmployeeManager& manager) {
    string name;
    string securePin;
    double hourlyRate;
    
    cout << "Enter employee name: ";
    cin >> name;
    cout << "Enter 4 digit pin: ";
    cin >> securePin;
    cout << "Enter hourly rate: ";
    cin >> hourlyRate;

    manager.createEmployee(name, securePin, hourlyRate);
    cout << "Employee added successfully! \n" << endl;
}

void signInEmployee(EmployeeManager& manager) {
    string name;
    
    displaySignInMenu();
    
    cin >> name;
    Employee* emp = manager.getEmployee(name);
    
    if(!emp) {
        cout << "Employee not fount!\n" << endl;
        return;
    } else {
        cout << "Signin succesful. \n" << endl;
    }
    
    int choice;
    while(true){
        displayTaskMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                manageTimesheet(emp);
                break;
            case 2:{
                LinkedListAccounts accounts;
                manageAccounts(&accounts);
                break;
            }
            case 3:
                createReport();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice! Please try again. \n" << endl;
        }
    }
}

void addEmployeeHours(Employee* employee) {
    if (!employee) {
        cout << "Employee not found!\n" << endl;
        return;
    }
    
    string date;
    string dayOfWeek;
    string clientName;
    double hourlyRate = employee->getHourlyRate();
    int startHour, startMinute, endHour, endMinute;
    
    cout << "Enter the date (YYYY-MM-DD): ";
    cin >> date;
    
    cout << "Enter the day of the week: ";
    cin >> dayOfWeek;
    
    cout << "Enter start time (HH MM): ";
    cin >> startHour >> startMinute;
    
    cout << "Enter end time (HH MM): ";
    cin >> endHour >> endMinute;
    
    cout << "Enter client name: ";
    cin >> clientName;
    
    int totalMinutes = (endHour * 60 + endMinute) - (startHour * 60 + startMinute);
    double hoursWorked = static_cast<double>(totalMinutes) / 60.0;
    
    employee->addTimesheet(date, ClientWork(clientName, hoursWorked, hourlyRate));
    
    cout << "Hours added successfully for " << employee->getName() << "\n" << endl;
}

void subtractEmployeeHours(Employee* employee) {
    if (!employee) {
        cout << "Employee not found!" << endl;
        return;
    }

    string date, clientName;
    double hoursWorked, hourlyRate = employee->getHourlyRate();
    int startHour, startMinute, endHour, endMinute;

    cout << "Enter the date (YYYY-MM-DD): ";
    cin >> date;

    cout << "Enter client name: ";
    cin >> clientName;

    cout << "Enter start time (HH MM): ";
    cin >> startHour >> startMinute;

    cout << "Enter end time (HH MM): ";
    cin >> endHour >> endMinute;

    int totalMinutes = (endHour * 60 + endMinute) - (startHour * 60 + startMinute);
    hoursWorked = static_cast<double>(totalMinutes) / 60.0;

    employee->subtractTimesheet(date, ClientWork(clientName, hoursWorked, hourlyRate));
    cout << "Hours subtracted successfully for " << employee->getName() << "\n" << endl;
}


void showEmployeeHours(Employee* employee) {
    if (!employee) {
        cout << "Employee not found!" << endl;
        return;
    }

    cout << "Most Recent Daily Total: $" << employee->getMostRecentDailyTotal() << endl;
    cout << "Weekly Total: $" << employee->getWeeklyTotal() << endl;
    cout << "Monthly Total: $" << employee->getMonthlyTotal() << endl;
}

void showEmployeeTotalPay(Employee* employee) {
    if (!employee) {
        cout << "Employee not found!" << endl;
        return;
    }

    cout << "Total Pay: $" << employee->getTotalPay() << endl;
}

void manageTimesheet(Employee* employee) {
    int timesheetChoice;
    while (true) {
        displayTimesheetTaskMenu();
        cin >> timesheetChoice;

        switch (timesheetChoice) {
            case 1:
                addEmployeeHours(employee);
                break;
            case 2:
                subtractEmployeeHours(employee);
                break;
            case 3:
                showEmployeeHours(employee);
                break;
            case 4:
                showEmployeeTotalPay(employee);
                break;
            case 5:
                return;  // Go back to the task menu
            default:
                cout << "Invalid choice! Please try again.\n" << endl;
        }
    }
}

void createAccountMenu(LinkedListAccounts* accounts) {
    string accountName;
    int balance = 0.0;

    cout << "Enter Account's name: ";
    cin >> accountName;

    accounts->addAccount(accountName, balance);
    
    cout << "Account created! \n" << endl;
}

void deleteAccountMenu(LinkedListAccounts* accounts) {
    string accountNumber;
    cout << "Enter the account number to delete: ";
    cin >> accountNumber;

    // Attempt to delete the account
    accounts->deleteAccount(accountNumber);
    cout << "Account has been deleted." << endl;
}

void addAccountFunds(LinkedListAccounts* accounts) {
    string identifier;
    double amount;
    cout << "Enter account name: ";
    cin >> identifier;
    cout << "Enter amount to add: ";
    cin >> amount;
    accounts->addFunds(identifier, amount, true);
}

void subtractAccountFunds(LinkedListAccounts* accounts) {
    string identifier;
    double amount;
    cout << "Enter account name: ";
    cin >> identifier;
    cout << "Enter amount to subtract: ";
    cin >> amount;
    accounts->subtractFunds(identifier, amount, true);
}

void showAccountBalance(LinkedListAccounts* accounts) {
    string accountName;
    cout << "Enter account name: ";
    cin >> accountName;
    AccountNode* account = accounts->findAccountByName(accountName);
    
    if (account) {
        // Access account details directly
        string name = account->name;
        string accountNumber = account->accountNumber;
        double balance = account->balance;
        
        cout << "Account Name    Account Number      Account Balance" << endl;
        cout << name << "             " << accountNumber << "    $" << fixed << setprecision(2) << balance << endl;
    } else {
        cout << "Account not found!" << endl;
    }
}

void manageAccounts(LinkedListAccounts* accounts) {
    int accountChoice;
    while (true) {
        displayAccountTaskMenu();
        cin >> accountChoice;

        switch (accountChoice) {
            case 1:
                createAccountMenu(accounts);
                break;
            case 2:
                deleteAccountMenu(accounts);
                break;
            case 3:
                addAccountFunds(accounts);
                break;
            case 4:
                subtractAccountFunds(accounts);
                break;
            case 5:
                showAccountBalance(accounts);
                break;
            case 6:
                accounts->printAccounts();
                break;
            case 7:
                return;
            default:
                cout << "Invalid choice! Please try again.\n" << endl;
        }
    }
}

void createReport() {
    int reportChoice;
    while (true) {
        displayReportMenu();
        cin >> reportChoice;

        switch (reportChoice) {
            case 1:
                cout << "View Report functionality not implemented yet." << endl;
                break;
            case 2:
                cout << "Export Report functionality not implemented yet." << endl;
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice! Please try again.\n" << endl;
        }
    }
}
