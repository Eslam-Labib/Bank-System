#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CLIENTS = 100;
const int MAX_EMPLOYEES = 50;
const int MAX_LOANS = 100;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

class Loan {
public:
    int loanId;
    int clientId;
    double amount;
    double interestRate;
    int termMonths;
    bool approved;

    Loan() {
        loanId = 0;
        clientId = 0;
        amount = 0;
        interestRate = 0;
        termMonths = 0;
        approved = false;
    }

    double calculateTotalRepayment() {
        return amount + (amount * interestRate * termMonths / 12.0);
    }

    void approve() { approved = true; }
    void reject() { approved = false; }

    void display() {
        cout << "\033[33mLoan ID:\033[0m " << loanId
             << "\n\033[33mClient ID:\033[0m " << clientId
             << "\n\033[33mAmount:\033[0m " << amount << " $"
             << "\n\033[33mInterest Rate:\033[0m " << interestRate * 100 << "%"
             << "\n\033[33mTerm:\033[0m " << termMonths << " months"
             << "\n\033[33mTotal Repayment:\033[0m " << calculateTotalRepayment() << " $"
             << "\n\033[33mStatus:\033[0m " << (approved ? "\033[92mApproved\033[0m" : "\033[31mPending\033[0m") << "\n";
    }
};


class Client {
public:
    int id;
    string name;
    string password;
    double balance;

    Client() {
        id = 0;
        name = "";
        password = "";
        balance = 0;
    }

    void setName(string n) { name = n; }
    void setPassword(string p) { password = p; }
    void setBalance(double b) { balance = b; }
    void deposit(double amount) { balance += amount; }
    void withdraw(double amount) { if (balance >= amount) balance -= amount; }

    void display() {
        cout << "\033[33mID: " << id << "\nName: " << name << "\nBalance: " << balance << "\033[0m\033[92m $\033[0m" << "\n\033[0m";
    }
};

class Employee {
public:
    int id;
    string name;
    int age;
    double salary;
    string password;

    Employee() {
        id = 0;
        name = "";
        age = 0;
        salary = 0;
        password = "";
    }

    void display() {
        cout << "\033[33mID: " << id << "\nName: " << name << "\nAge: " << age << "\nSalary: " << salary << "\033[92m $\033[0m" << "\n\033[0m";
    }
};

class Admin {
public:
    int id;
    string name;
    string password;

    Admin() {
        id = 0;
        name = "";
        password = "";
    }

    void display() {
        cout << "ID: " << id << "\nName: " << name << "\n";
    }
};

Client clients[MAX_CLIENTS];
Employee employees[MAX_EMPLOYEES];
Admin admin;
Loan loans[MAX_LOANS];

int clientCount = 0;
int employeeCount = 0;
int loanCount = 0;

void saveClients() {
    ofstream file("clients.txt");
    for (int i = 0; i < clientCount; i++) {
        file << clients[i].id << " " << clients[i].name << " " << clients[i].password << " " << clients[i].balance << "\n";
    }
}

void loadClients() {
    ifstream file("clients.txt");
    clientCount = 0;
    while (file >> clients[clientCount].id >> clients[clientCount].name >> clients[clientCount].password >> clients[clientCount].balance) {
        clientCount++;
    }
}

void saveEmployees() {
    ofstream file("employees.txt");
    for (int i = 0; i < employeeCount; i++) {
        file << employees[i].id << " " << employees[i].name << " " << employees[i].password << " "
            << employees[i].age << " " << employees[i].salary << "\n";
    }
}

void loadEmployees() {
    ifstream file("employees.txt");
    employeeCount = 0;
    while (file >> employees[employeeCount].id >> employees[employeeCount].name >> employees[employeeCount].password >> employees[employeeCount].age >> employees[employeeCount].salary) {
        employeeCount++;
    }
}

void saveLoans() {
    ofstream file("loans.txt");
    for (int i = 0; i < loanCount; i++) {
        file << loans[i].loanId << " "
             << loans[i].clientId << " "
             << loans[i].amount << " "
             << loans[i].interestRate << " "
             << loans[i].termMonths << " "
             << loans[i].approved << "\n";
    }
}

void loadLoans() {
    ifstream file("loans.txt");
    loanCount = 0;
    while (file >> loans[loanCount].loanId
                >> loans[loanCount].clientId
                >> loans[loanCount].amount
                >> loans[loanCount].interestRate
                >> loans[loanCount].termMonths
                >> loans[loanCount].approved) {
        loanCount++;
    }
}


void clientMenu(Client& c) {
    int choice;
    do {
        clearScreen();
        cout << "\033[92m === Client Menu: ===\033[0m" << endl;
        cout << "\033[96m1.\033[33mDeposit\033[0m" << endl;
        cout << "\033[96m2.\033[33mWithdraw\033[0m" << endl;
        cout << "\033[96m3.\033[33mShow Balance\033[0m" << endl;
        cout << "\033[96m4.\033[33mInvest\033[0m" << endl;
        cout << "\033[96m5.\033[33mLoans\033[0m" << endl;
        cout << "\033[96m6.\033[33mBank Benefits\033[0m" << endl;
        cout << "\033[31m0.Exit\033[0m" << endl;
        cout << "\033[33mChoice: \033[0m";

        cin >> choice;

        clearScreen();
        if (choice == 1) {
            double amt; cout << "\033[33mAmount to Deposite: \033[0m"; cin >> amt; c.deposit(amt);
            cout << "\033[92mDeposit successful\033[0m\n";
        }
        else if (choice == 2) {
            double amt; cout << "Amount: "; cin >> amt; c.withdraw(amt);
            cout << "\033[92mWithdrawal processed\033[0m\n";
        }
        else if (choice == 3) {
            c.display();
        }
        else if (choice == 4) {
            cout << "\033[33mInvestment feature coming soon\033[0m\n";
        }
        else if (choice == 5) {
    int loanChoice;
    cout << "\033[96m1.\033[33m Request Loan\n\033[0m";
    cout << "\033[96m2.\033[33m View My Loans\n\033[0m";
    cout << "\033[96m0.\033[31m Back\n\033[0m";
    cout << "Choice: ";
    cin >> loanChoice;

    if (loanChoice == 1) {
        if (loanCount < MAX_LOANS) {
            Loan& l = loans[loanCount];
            l.loanId = loanCount + 1;
            l.clientId = c.id;
            cout << "Enter loan amount: ";
            cin >> l.amount;
            cout << "Enter interest rate (e.g. 0.05 for 5%): ";
            cin >> l.interestRate;
            cout << "Enter term (months): ";
            cin >> l.termMonths;
            l.approved = false;
            loanCount++;
            saveLoans();
            cout << "\033[92mLoan request submitted successfully!\033[0m\n";
        } else {
            cout << "\033[31mLoan list is full\033[0m\n";
        }
    }
    else if (loanChoice == 2) {
        bool found = false;
        for (int i = 0; i < loanCount; i++) {
            if (loans[i].clientId == c.id) {
                loans[i].display();
                cout << "-----------------\n";
                found = true;
            }
        }
        if (!found) {
            cout << "\033[31mNo loans found\033[0m\n";
        }
    }
}

        else if (choice == 6) {
            cout << "\033[33mBank benefits feature coming soon\n\033[0m";
        }
        else if (choice != 0) {
            cout << "\033[31mWrong Choice, try another one\033[0m\n";
        }
        pauseScreen();
    } while (choice != 0);
}

void employeeMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\033[92m === Employee Menu: === \n\033[0m";
        cout << "\033[96m1. \033[33mView Client List\n\033[0m";
        cout << "\033[96m2. \033[33mAdd Employee\n\033[0m";
        cout << "\033[96m3. \033[33mManage Loan Requests\n\033[0m";
        cout << "\033[96m0. \033[31mExit\n\033[0m";
        cout << "\033[33mChoice: \033[0m";
        cin >> choice;

        if (choice == 1) {
            int clientNum;
            do {
                clearScreen();
                cout << "\033[92m === Client List: ===\n\033[0m";
                for (int i = 0; i < clientCount; i++) {
                    cout << i + 1 << ". " << clients[i].name << " (ID: " << clients[i].id << ")\n";
                }
                cout << "\n\033[33mEnter client number to view info (0 to return): \033[0m";
                cin >> clientNum;

                if (clientNum > 0 && clientNum <= clientCount) {
                    clearScreen();
                    cout << "\033[92m === Client Information: === \n\033[0m";
                    clients[clientNum - 1].display();
                    cout << "\033[33mPassword: " << clients[clientNum - 1].password << "\n\033[0m";
                    pauseScreen();
                }
                else if (clientNum != 0) {
                    cout << "\033[31mInvalid client number\033[0m\n";
                    pauseScreen();
                }

            } while (clientNum != 0);
        }
        else if (choice == 2) {
            if (employeeCount < MAX_EMPLOYEES) {
                Employee& e = employees[employeeCount];
                e.id = employeeCount + 1;
                clearScreen();
                cout << "\033[33mEnter new employee name: \033[0m";
                cin.ignore();
                getline(cin, e.name);
                cout << "\033[33mEnter employee password: \033[0m";
                getline(cin, e.password);
                cout << "\033[33mEnter employee age: \033[0m";
                cin >> e.age;
                cout << "\033[33mEnter employee salary: \033[0m";
                cin >> e.salary;
                employeeCount++;
                saveEmployees();
                cout << "\033[92mEmployee added successfully\033[0m\n";
            }
            else {
                cout << "\033[31mEmployee list is full\033[0m\n";
            }
            pauseScreen();
        }
        else if (choice == 3) {
    int loanNum;
    clearScreen();
    cout << "\033[92mPending Loans:\033[0m\n";
    for (int i = 0; i < loanCount; i++) {
        if (!loans[i].approved) {
            cout << i + 1 << ". ";
            loans[i].display();
            cout << "-----------------\n";
        }
    }
    cout << "Enter loan number to approve/reject (0 to back): ";
    cin >> loanNum;
    if (loanNum > 0 && loanNum <= loanCount) {
        int decision;
        cout << "1. Approve\n2. Reject\nChoice: ";
        cin >> decision;
        if (decision == 1) loans[loanNum - 1].approve();
        else if (decision == 2) loans[loanNum - 1].reject();
        saveLoans();
        cout << "\033[92mLoan status updated\033[0m\n";
    }
    pauseScreen();
}

        else if (choice != 0) {
            cout << "\033[31mInvalid choice\033[0m\n";
            pauseScreen();
        }
    } while (choice != 0);
}

void manageEmployeesMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\033[92m === Manage Employees Menu: ===\033[0m\n";
        cout << "\033[96m1.\033[33m View Employees\n";
        cout << "\033[96m2.\033[33m Edit Employee\n";
        cout << "\033[96m3.\033[33m Remove Employee\n";
        cout << "\033[96m0.\033[33m Return\n\033[0m";
        cout << "\033[33mChoice: \033[0m";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            if (employeeCount == 0) {
                cout << "\033[31mNo employees found\033[0m\n";
            }
            else {
                for (int i = 0; i < employeeCount; i++) {
                    cout << i + 1 << ". ";
                    employees[i].display();
                    cout << "----------------------\n";
                }
            }
            pauseScreen();
        }
        else if (choice == 2) {
            int empNum;
            cout << "\033[33mEnter employee number to edit: \033[0m";
            cin >> empNum;
            if (empNum > 0 && empNum <= employeeCount) {
                Employee& e = employees[empNum - 1];
                clearScreen();
                cout << "\033[33mEditing Employee #" << empNum << ":\n\033[0m";
                cout << "\033[33mCurrent name: \033[0m" << e.name << "\n\033[33mEnter new name (or '.' to keep current): \033[0m";
                cin.ignore();
                string input;
                getline(cin, input);
                if (input != ".") e.name = input;

                cout << "\033[33mCurrent password: \033[0m" << e.password << "\n\033[33mEnter new password (or '.' to keep current): \033[0m";
                getline(cin, input);
                if (input != ".") e.password = input;

                cout << "\033[33mCurrent age: \033[0m" << e.age << "\033[33m\nEnter new age (or 0 to keep current): \033[0m";
                int newAge;
                cin >> newAge;
                if (newAge > 0) e.age = newAge;

                cout << "\033[33mCurrent salary: \033[0m" << e.salary << "\033[33m\nEnter new salary (or 0 to keep current):\033[0m ";
                double newSalary;
                cin >> newSalary;
                if (newSalary > 0) e.salary = newSalary;

                saveEmployees();
                cout << "\033[92mEmployee updated successfully\033[0m\n";
                pauseScreen();
            }
            else {
                cout << "\033[31mInvalid employee number\033[0m\n";
                pauseScreen();
            }
        }
        else if (choice == 3) {
            int empNum;
            cout << "\033[33mEnter employee number to remove: \033[0m";
            cin >> empNum;
            if (empNum > 0 && empNum <= employeeCount) {
                for (int i = empNum - 1; i < employeeCount - 1; i++) {
                    employees[i] = employees[i + 1];
                    employees[i].id = i + 1;
                }
                employeeCount--;
                saveEmployees();
                cout << "\033[92mEmployee removed successfully\033[0m\n";
                pauseScreen();
            }
            else {
                cout << "\033[31mInvalid employee number\033[0m\n";
                pauseScreen();
            }
        }
        else if (choice != 0) {
            cout << "\033[31mWrong Choice, try another one\033[0m\n";
            pauseScreen();
        }
    } while (choice != 0);
}

void adminMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\033[92m === Admin Menu: === \033[0m" << endl;
        cout << "\033[96m1. \033[33mView Client List\n\033[0m";
        cout << "\033[96m2. \033[33mManage Employees\n\033[0m";
        cout << "\033[96m0. \033[31mExit\n\033[0m";
        cout << "\033[33mChoice: \033[0m";

        cin >> choice;

        clearScreen();
        if (choice == 1) {
            int clientNum;
            do {
                clearScreen();
                cout << "\033[92mClient List:\033[0m\n";
                for (int i = 0; i < clientCount; i++) {
                    cout << i + 1 << ". " << clients[i].name << " (ID: " << clients[i].id << ")\n";
                }
                cout << "\n\033[33mEnter client number to view info (0 to return)\033[0m: ";
                cin >> clientNum;

                if (clientNum > 0 && clientNum <= clientCount) {
                    clearScreen();
                    cout << "\033[92mClient Information:\033[0m\n";
                    clients[clientNum - 1].display();
                    cout << "\033[33mPassword: \033[0m" << clients[clientNum - 1].password << "\n";
                    pauseScreen();
                }
                else if (clientNum != 0) {
                    cout << "\033[31mInvalid client number\033[0m\n";
                    pauseScreen();
                }
            } while (clientNum != 0);
        }
        else if (choice == 2) {
            manageEmployeesMenu();
        }
        else if (choice != 0) {
            cout << "\033[31mWrong Choice, try another one\033[0m\n";
            pauseScreen();
        }
    } while (choice != 0);
}

void mainMenu() {
    loadClients();
    loadEmployees();
    loadClients();
loadEmployees();
loadLoans();


    int choice;
    bool exitFlag = false;
    do {
        clearScreen();
        cout << "\033[92m===== \033[96mWelcome to The Bank\033[0m\033[92m =====\033[0m" << endl;
        cout << "\033[92m========== \033[96mMain Menu:\033[0m \033[92m=========\033[0m" << endl;
        cout << "\033[92m===============================\033[0m" << endl;
        cout << "\033[32m\033[96m1.\033[33m Add Client\n"
            << "\033[96m2.\033[0m\033[33m Add Employee\n"
            << "\033[96m3.\033[0m\033[33m Login as Client\n"
            << "\033[96m4.\033[0m\033[33m Login as Employee\n"
            << "\033[96m5.\033[0m\033[33m Login as Admin\n"
            << "\033[96m0.\033[0m\033[31m Exit\n"
            << "\033[33mChoice: \033[0m";
        cin >> choice;

        clearScreen();
        switch (choice) {
        case 1:
            if (clientCount < MAX_CLIENTS) {
                clients[clientCount].id = clientCount + 1;
                cout << "\033[33mName\033[0m: "; cin >> clients[clientCount].name;
                cout << "\033[33mPassword: \033[0m"; cin >> clients[clientCount].password;
                cout << "\033[33mBalance: \033[0m"; cin >> clients[clientCount].balance;
                clientCount++;
                saveClients();
                cout << "\033[92mClient added successfully\033[0m\n";
            }
            else {
                cout << "\033[31mClient list full\033[0m\n";
            }
            pauseScreen();
            break;

        case 2: {
            if (employeeCount < MAX_EMPLOYEES) {
                Employee& e = employees[employeeCount];
                e.id = employeeCount + 1;
                cout << "\033[33mEnter new employee name: \033[0m";
                cin.ignore();
                getline(cin, e.name);
                cout << "\033[33mEnter employee password: \033[0m";
                getline(cin, e.password);
                cout << "\033[33mEnter employee age: \033[0m";
                cin >> e.age;
                cout << "\033[33mEnter employee salary: \033[0m";
                cin >> e.salary;
                employeeCount++;
                saveEmployees();
                cout << "\033[92mEmployee added successfully\033[0m\n";
            }
            else {
                cout << "\033[31mEmployee list is full\033[0m\n";
            }
            pauseScreen();
            break;
        }

        case 3: {
            string pass; int id;
            cout << "\033[33mID: \033[0m"; cin >> id;
            cout << "\033[33mPassword: \033[0m"; cin >> pass;
            bool found = false;
            for (int i = 0; i < clientCount; i++) {
                if (clients[i].id == id && clients[i].password == pass) {
                    found = true;
                    clientMenu(clients[i]);
                    saveClients();
                    break;
                }
            }
            if (!found) {
                cout << "\033[31mInvalid ID or password\033[0m\n";
                pauseScreen();
            }
            break;
        }

        case 4: {
            string pass;
            cout << "\033[33mEmployee password: \033[0m";
            cin >> pass;
            if (pass == "emp123") {
                employeeMenu();
            }
            else {
                cout << "\033[31mWrong password\033[0m\n";
                pauseScreen();
            }
            break;
        }

        case 5: {
            string pass;
            cout << "\033[33mAdmin password: \033[0m";
            cin >> pass;
            if (pass == "admin123") {
                adminMenu();
            }
            else {
                cout << "\033[31mWrong password\033[0m\n";
                pauseScreen();
            }
            break;
        }

        case 0:
            exitFlag = true;
            break;

        default:
            cout << "\033[31mWrong Choice, try another one\033[0m\n";
            pauseScreen();
            break;
        }
    } while (!exitFlag);

    saveClients();
    saveEmployees();
saveLoans();

}

int main() {
    mainMenu();
    return 0;
}
