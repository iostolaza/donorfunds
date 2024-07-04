//
//  displaymenu.hpp
//  donorfunds
//
//  Created by Francisco Ostolaza on 6/28/24.
//

#ifndef displaymenu_hpp
#define displaymenu_hpp

#include "donorfunds.hpp"
  
#include <iostream>
#include <string>

using namespace std;

// Main menu functions
void displayMainMenu();
void displaySignInMenu();
void displayTaskMenu();
void displayTimesheetTaskMenu();
void displayAccountTaskMenu();
void displayReportMenu();

// Employee management functions
void manageTimesheet(Employee* employee);
void addEmployeeHours(Employee* employee);
void subtractEmployeeHours(Employee* employee);
void showEmployeeHours(Employee* employee);
void showEmployeeTotalPay(Employee* employee);
void addEmployee(EmployeeManager& manager);
void signInEmployee(EmployeeManager& manager);

// Account management functions
void manageAccounts(LinkedListAccounts* accounts);
void createAccountMenu(LinkedListAccounts* accounts);
void deleteAccountMenu(LinkedListAccounts* accounts);
void addAccountFunds(LinkedListAccounts* accounts);
void subtractAccountFunds(LinkedListAccounts* accounts);
void showAccountBalance(LinkedListAccounts* accounts);


// Report functions
void createReport();


#endif /* displaymenu_hpp */

