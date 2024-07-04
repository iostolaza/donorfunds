// donorfunds
// donnorfunds.hpp

// Header file for the donorfunds program. Below will be several classes.
// The first section is the funds class declaration.
// The second section is the timesheet class declaration.

// Created by: Ostolaza
// Date: 2024-06-26

#ifndef DONORFUNDS_HPP
#define DONORFUNDS_HPP

#include "uniqueId.hpp"

#include <iostream>
#include <ctime>
#include <string>
#include <unordered_set>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

//Account Section

struct AccountNode {
    string name;
    string accountNumber;
    double balance;
    AccountNode* next;
    vector<string> transactionLog;
    AccountNode(const string& name, const string& accountNumber, double balance);
    };
 
class LinkedListAccounts {
public:
    LinkedListAccounts();
    ~LinkedListAccounts();
    void addAccount(const string& name, double balance = 0.0);
    void deleteAccount(const string& accountNumber);
    void printAccounts() const;
    
    void addFunds(const string& identifier, double amount, bool byName = false);
    void subtractFunds(const string& identifier, double amount, bool byName = false);
    double getAccountBalance(const string& identifier, bool byName);
    
    AccountNode getAccountInfo(const string& identifier, bool byName);
    AccountNode* getHead() const;
    AccountNode* findAccountByName(const string& name);
    
private:
    AccountNode* head;
    uniqueID uniqueIDGenerator;
    
    AccountNode* findAccountByNumber(const string& accountNumber);
    
    void logTransaction(AccountNode* account, const string& transaction);
    friend struct AccountNode;
    friend class AccountLinkedList;
    
};

//Timesheet section

class ClientWork {
public:
    ClientWork(const  string& clientName, double hoursWorked, double hourlyRate);
    string getClientName() const;
    double getHoursWorked() const;
    double getHourlyRate() const;
    double getTotalPay() const;

private:
    string clientName;
    double hoursWorked;
    double hourlyRate;
};

class Timesheet {
public:
    Timesheet();
    void addWork(const  string& date, const ClientWork& work);
    void subtractWork(const  string& date, const ClientWork& work);
    double getDailyTotal(const  string& date) const;
    double getMostRecentDailyTotal() const;
    double getWeeklyTotal() const;
    double getMonthlyTotal() const;

private:
    multimap<string, ClientWork> workLog;
    set<string> dates;
    friend class AccountLinkedList;
};

class Employee {
public:
    Employee(const string& name, const string& securePin, double hourlyRate);
    string getName() const;
    string getSecurePin() const;
    double getHourlyRate() const;
    void addTimesheet(const string& date, const ClientWork& work);
    void subtractTimesheet(const string& date, const ClientWork& work);
    double getDailyTotal(const string& date) const;
    double getMostRecentDailyTotal() const;
    double getWeeklyTotal() const;
    double getMonthlyTotal() const;
    double getTotalPay() const;

private:
    string name;
    double hourlyRate;
    string securePin;
    Timesheet timesheet;
    friend class AccountLinkedList;
};

class EmployeeManager {
public:
    void createEmployee(const string& name, const string& securePin, double hourlyRate);
    void deleteEmployee(const string& name);
    Employee* getEmployee(const string& name);

private:
     unordered_map< string, Employee> employees;
    friend class AccountLinkedList;

};

class AccountLinkedList : public LinkedListAccounts {
public:
    void deductFundsForTimesheet(EmployeeManager& manager);
};


#endif // DONORFUNDS_HPP





