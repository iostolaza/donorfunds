// donorfunds
// donnorfunds.cpp

// Implementation file for donorfunds.

// Created by: Ostolaza
// Date: 2024-06-26

#include "donorfunds.hpp"
#include "uniqueId.hpp"
#include "displaymenu.hpp"


#include <iostream>
#include <ctime>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <iomanip>
  
using namespace std;

// Section 1 implementation - Accounts

AccountNode::AccountNode(const string& name, const string& accountNumber, double balance)
    : name(name), accountNumber(accountNumber), balance(balance), next(nullptr) {}


LinkedListAccounts::LinkedListAccounts() : head(nullptr) {}

LinkedListAccounts::~LinkedListAccounts() {
    AccountNode* current = head;
    while(current) {
        AccountNode* next = current->next;
        delete current;
        current = next;
    }
}

AccountNode* LinkedListAccounts::findAccountByNumber(const string& accountNumber) {
    AccountNode* current = head;
    while(current) {
        if(current->accountNumber == accountNumber){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

AccountNode* LinkedListAccounts::findAccountByName(const string& name) {
    AccountNode* current = head;
    while(current) {
        if(current->name == name){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void LinkedListAccounts::logTransaction(AccountNode* account, const string& transaction) {
    if (account) {
        account->transactionLog.push_back(transaction);
    }
}


void LinkedListAccounts::addAccount(const string& name, double balance){
    string newAccountNumber = uniqueIDGenerator.generateUniqueID();
    AccountNode* newNode = new AccountNode(name, newAccountNumber, balance);
    newNode->next = head;
    head = newNode;
}

void LinkedListAccounts::deleteAccount(const string& accountNumber){
    AccountNode* current = head;
    AccountNode* prev = nullptr;
    while(current)  {
        if(current->accountNumber == accountNumber) {
            if(prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            uniqueIDGenerator.removeID(accountNumber);
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void LinkedListAccounts::addFunds(const string& identifier, double amount, bool byName) {
    AccountNode* account = byName ? findAccountByName(identifier) : findAccountByNumber(identifier);
    if (account) {
        account->balance += amount;
        string log = "Deposited $" + to_string(amount) + " on " + to_string(time(nullptr));
        logTransaction(account, log);
    } else {
        cout << "Account not found!" << endl;
    }
}

void LinkedListAccounts::subtractFunds(const string& identifier, double amount, bool byName) {
    AccountNode* account = byName ? findAccountByName(identifier) : findAccountByNumber(identifier);
    if (account) {
        account->balance -= amount;
        string log = "Withdrew $" + to_string(amount) + " on " + to_string(time(nullptr));
        logTransaction(account, log);
    } else {
        cout << "Account not found!" << endl;
    }
}


double LinkedListAccounts::getAccountBalance(const string& identifier, bool byName) {
    // Use the appropriate find method based on the boolean byName flag
    AccountNode* account = byName ? findAccountByName(identifier) : findAccountByNumber(identifier);
    
    if (account) {
        // Print account details
        cout << "Account Name: " << account->name << "\n"
             << "Account Number: " << account->accountNumber << "\n"
             << "Current Balance: $" << fixed << setprecision(2) << account->balance << endl;
        return account->balance;
    } else {
        cout << "Account not found!" << endl;
        return -1.0;  // Return an error value indicating the account was not found
    }
}

AccountNode LinkedListAccounts::getAccountInfo(const string& identifier, bool byName) {
    AccountNode* account = byName ? findAccountByName(identifier) : findAccountByNumber(identifier);
    if (account) {
        return {account->name, account->accountNumber, account->balance};
    } else {
        // Return an empty AccountInfo object to indicate not found
        return {"", "", -1.0};
    }
}

void LinkedListAccounts::printAccounts() const{
    AccountNode* current = head;
    while(current) {
        cout << "Account Number: " << current->accountNumber << "\n"
        << "Name: " << current->name << "\n"
        << "Balance: " << current->balance << "\n" << endl;
        
        current = current->next;
    }
}

AccountNode* LinkedListAccounts::getHead() const {
    return head;
}

// Section 2 implementation - Client and Timesheet

ClientWork::ClientWork(const string& clientName, double hoursWorked, double hourlyRate)
    : clientName(clientName), hoursWorked(hoursWorked), hourlyRate(hourlyRate) {}

string ClientWork::getClientName() const {
    return clientName;
}

double ClientWork::getHoursWorked() const {
    return hoursWorked;
}

double ClientWork::getHourlyRate() const {
    return hourlyRate;
}

double ClientWork::getTotalPay() const {
    return hoursWorked * hourlyRate;
}

Timesheet::Timesheet() {}

void Timesheet::addWork(const string& date, const ClientWork& work) {
    workLog.emplace(date, work);
    dates.insert(date);
}

void Timesheet::subtractWork(const string& date, const ClientWork& work){
    auto range = workLog.equal_range(date);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second.getClientName() == work.getClientName() &&
            it->second.getHoursWorked() == work.getHoursWorked() &&
            it->second.getHourlyRate() == work.getHourlyRate()) {
            workLog.erase(it);
            break;
        }
    }
}

double Timesheet::getDailyTotal(const string& date) const {
    double total = 0;
    auto range = workLog.equal_range(date);
    for (auto it = range.first; it != range.second; ++it) {
        total += it->second.getTotalPay();
    }
    return total;
}

double Timesheet::getMostRecentDailyTotal() const {
    if (dates.empty()) return 0;
    return getDailyTotal(*dates.rbegin());
}

double Timesheet::getWeeklyTotal() const {
    double total = 0;
    for (const auto& [date, work] : workLog) {
        total += work.getTotalPay();
    }
    return total;
}

double Timesheet::getMonthlyTotal() const {
    return getWeeklyTotal();
}

Employee::Employee(const string& name, const string& securePin, double hourlyRate)
    : name(name), securePin(securePin), hourlyRate(hourlyRate) {}

string Employee::getName() const {
    return name;
}

string Employee::getSecurePin() const {
    return securePin;
}

double Employee::getHourlyRate() const {
    return hourlyRate;
}

void Employee::addTimesheet(const string& date, const ClientWork& work) {
    timesheet.addWork(date, work);
}

void Employee::subtractTimesheet(const string& date, const ClientWork& work) {
    timesheet.subtractWork(date, work);
}

double Employee::getDailyTotal(const string& date) const {
    return timesheet.getDailyTotal(date);
}

double Employee::getMostRecentDailyTotal() const {
    return timesheet.getMostRecentDailyTotal();
}

double Employee::getWeeklyTotal() const {
    return timesheet.getWeeklyTotal();
}

double Employee::getMonthlyTotal() const {
    return timesheet.getMonthlyTotal();
}

double Employee::getTotalPay() const {
    return getMonthlyTotal();
}


//EmployeeManager Class

void EmployeeManager::createEmployee(const string& name, const string& securePin, double hourlyRate) {
    employees.emplace(name, Employee(name, securePin, hourlyRate));
}

void EmployeeManager::deleteEmployee(const string& name) {
    employees.erase(name);
}

Employee* EmployeeManager::getEmployee(const string& name) {
    auto it = employees.find(name);
    if (it != employees.end()) {
        return &it->second;
    }
    return nullptr;
}

void AccountLinkedList::deductFundsForTimesheet(EmployeeManager& manager) {
    for (auto& [name, employee] : manager.employees) {
        for (const auto& [date, work] : employee.timesheet.workLog) {
            string clientName = work.getClientName();
            double totalPay = work.getTotalPay();
            AccountNode* account = findAccountByName(clientName);
            if (account && account->balance >= totalPay) {
                account->balance -= totalPay;
            } else {
                cout << "Insufficient funds in account: " << clientName << endl;
            }
        }
    }
} 







