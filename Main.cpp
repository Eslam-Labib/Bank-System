#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CLIENTS = 100;
const int MAX_EMPLOYEES = 50;

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
        cout << "ID: " << id << "\nName: " << name << "\nBalance: " << balance << "\n";
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
        cout << "ID: " << id << "\nName: " << name << "\nAge: " << age << "\nSalary: " << salary << "\n";
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

int clientCount = 0;
int employeeCount = 0;

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

void clientMenu(Client& c) {
    int choice;
    do {
        clearScreen();
        cout << "Client Menu:" << endl;
        cout << "1.Deposit" << endl;
        cout << "2.Withdraw" << endl;
        cout << "3.Show Balance" << endl;
        cout << "4.Invest" << endl;
        cout << "5.Loans" << endl;
        cout << "6.Bank Benefits" << endl;
        cout << "0.Exit" << endl;
        cout << "Choice: ";

        cin >> choice;

        clearScreen();
        if (choice == 1) {
            double amt; cout << "Amount: "; cin >> amt; c.deposit(amt);
            cout << "Deposit successful.\n";
        }
        else if (choice == 2) {
            double amt; cout << "Amount: "; cin >> amt; c.withdraw(amt);
            cout << "Withdrawal processed.\n";
        }
        else if (choice == 3) {
            c.display();
        }
        else if (choice == 4) {
            cout << "Investment feature coming soon.\n";
        }
        else if (choice == 5) {
            cout << "Loan feature coming soon.\n";
        }
        else if (choice == 6) {
            cout << "Bank benefits feature coming soon.\n";
        }
        else if (choice != 0) {
            cout << "Wrong Choice, try another one.\n";
        }
        pauseScreen();
    } while (choice != 0);
}

void employeeMenu() {
    int choice;
    do {
        clearScreen();
        cout << "Employee Menu:\n";
        cout << "1. View Client List\n";
        cout << "2. Add Employee\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            int clientNum;
            do {
                clearScreen();
                cout << "Client List:\n";
                for (int i = 0; i < clientCount; i++) {
                    cout << i + 1 << ". " << clients[i].name << " (ID: " << clients[i].id << ")\n";
                }
                cout << "\nEnter client number to view info (0 to return): ";
                cin >> clientNum;

                if (clientNum > 0 && clientNum <= clientCount) {
                    clearScreen();
                    cout << "Client Information:\n";
                    clients[clientNum - 1].display();
                    cout << "Password: " << clients[clientNum - 1].password << "\n";
                    pauseScreen();
                }
                else if (clientNum != 0) {
                    cout << "Invalid client number!\n";
                    pauseScreen();
                }

            } while (clientNum != 0);
        }
        else if (choice == 2) {
            if (employeeCount < MAX_EMPLOYEES) {
                Employee& e = employees[employeeCount];
                e.id = employeeCount + 1;
                clearScreen();
                cout << "Enter new employee name: ";
                cin.ignore();
                getline(cin, e.name);
                cout << "Enter employee password: ";
                getline(cin, e.password);
                cout << "Enter employee age: ";
                cin >> e.age;
                cout << "Enter employee salary: ";
                cin >> e.salary;
                employeeCount++;
                saveEmployees();
                cout << "Employee added successfully.\n";
            }
            else {
                cout << "Employee list is full.\n";
            }
            pauseScreen();
        }
        else if (choice != 0) {
            cout << "Invalid choice!\n";
            pauseScreen();
        }
    } while (choice != 0);
}

void manageEmployeesMenu() {
    int choice;
    do {
        clearScreen();
        cout << "Manage Employees Menu:\n";
        cout << "1. View Employees\n";
        cout << "2. Edit Employee\n";
        cout << "3. Remove Employee\n";
        cout << "0. Return\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            if (employeeCount == 0) {
                cout << "No employees found.\n";
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
            cout << "Enter employee number to edit: ";
            cin >> empNum;
            if (empNum > 0 && empNum <= employeeCount) {
                Employee& e = employees[empNum - 1];
                clearScreen();
                cout << "Editing Employee #" << empNum << ":\n";
                cout << "Current name: " << e.name << "\nEnter new name (or '.' to keep current): ";
                cin.ignore();
                string input;
                getline(cin, input);
                if (input != ".") e.name = input;

                cout << "Current password: " << e.password << "\nEnter new password (or '.' to keep current): ";
                getline(cin, input);
                if (input != ".") e.password = input;

                cout << "Current age: " << e.age << "\nEnter new age (or 0 to keep current): ";
                int newAge;
                cin >> newAge;
                if (newAge > 0) e.age = newAge;

                cout << "Current salary: " << e.salary << "\nEnter new salary (or 0 to keep current): ";
                double newSalary;
                cin >> newSalary;
                if (newSalary > 0) e.salary = newSalary;

                saveEmployees();
                cout << "Employee updated successfully.\n";
                pauseScreen();
            }
            else {
                cout << "Invalid employee number.\n";
                pauseScreen();
            }
        }
        else if (choice == 3) {
            int empNum;
            cout << "Enter employee number to remove: ";
            cin >> empNum;
            if (empNum > 0 && empNum <= employeeCount) {
                for (int i = empNum - 1; i < employeeCount - 1; i++) {
                    employees[i] = employees[i + 1];
                    employees[i].id = i + 1;
                }
                employeeCount--;
                saveEmployees();
                cout << "Employee removed successfully.\n";
                pauseScreen();
            }
            else {
                cout << "Invalid employee number.\n";
                pauseScreen();
            }
        }
        else if (choice != 0) {
            cout << "Wrong Choice, try another one.\n";
            pauseScreen();
        }
    } while (choice != 0);
}

void adminMenu() {
    int choice;
    do {
        clearScreen();
        cout << "Admin Menu:" << endl;
        cout << "1. View Client List\n";
        cout << "2. Manage Employees\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        cin >> choice;

        clearScreen();
        if (choice == 1) {
            int clientNum;
            do {
                clearScreen();
                cout << "Client List:\n";
                for (int i = 0; i < clientCount; i++) {
                    cout << i + 1 << ". " << clients[i].name << " (ID: " << clients[i].id << ")\n";
                }
                cout << "\nEnter client number to view info (0 to return): ";
                cin >> clientNum;

                if (clientNum > 0 && clientNum <= clientCount) {
                    clearScreen();
                    cout << "Client Information:\n";
                    clients[clientNum - 1].display();
                    cout << "Password: " << clients[clientNum - 1].password << "\n";
                    pauseScreen();
                }
                else if (clientNum != 0) {
                    cout << "Invalid client number!\n";
                    pauseScreen();
                }
            } while (clientNum != 0);
        }
        else if (choice == 2) {
            manageEmployeesMenu();
        }
        else if (choice != 0) {
            cout << "Wrong Choice, try another one.\n";
            pauseScreen();
        }
    } while (choice != 0);
}

void mainMenu() {
    loadClients();
    loadEmployees();

    int choice;
    bool exitFlag = false;
    do {
        clearScreen();
        cout << "\nMain Menu:\n"
            << "1. Add Client\n"
            << "2. Add Employee\n"
            << "3. Login as Client\n"
            << "4. Login as Employee\n"
            << "5. Login as Admin\n"
            << "0. Exit\n"
            << "Choice: ";
        cin >> choice;

        clearScreen();
        switch (choice) {
        case 1:
            if (clientCount < MAX_CLIENTS) {
                clients[clientCount].id = clientCount + 1;
                cout << "Name: "; cin >> clients[clientCount].name;
                cout << "Password: "; cin >> clients[clientCount].password;
                cout << "Balance: "; cin >> clients[clientCount].balance;
                clientCount++;
                saveClients();
                cout << "Client added successfully.\n";
            }
            else {
                cout << "Client list full.\n";
            }
            pauseScreen();
            break;

        case 2: {
            if (employeeCount < MAX_EMPLOYEES) {
                Employee& e = employees[employeeCount];
                e.id = employeeCount + 1;
                cout << "Enter new employee name: ";
                cin.ignore();
                getline(cin, e.name);
                cout << "Enter employee password: ";
                getline(cin, e.password);
                cout << "Enter employee age: ";
                cin >> e.age;
                cout << "Enter employee salary: ";
                cin >> e.salary;
                employeeCount++;
                saveEmployees();
                cout << "Employee added successfully.\n";
            }
            else {
                cout << "Employee list is full.\n";
            }
            pauseScreen();
            break;
        }

        case 3: {
            string pass; int id;
            cout << "ID: "; cin >> id;
            cout << "Password: "; cin >> pass;
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
                cout << "Invalid ID or password!\n";
                pauseScreen();
            }
            break;
        }

        case 4: {
            string pass;
            cout << "Employee password: ";
            cin >> pass;
            if (pass == "emp123") {
                employeeMenu();
            }
            else {
                cout << "Wrong password!\n";
                pauseScreen();
            }
            break;
        }

        case 5: {
            string pass;
            cout << "Admin password: ";
            cin >> pass;
            if (pass == "admin123") {
                adminMenu();
            }
            else {
                cout << "Wrong password!\n";
                pauseScreen();
            }
            break;
        }

        case 0:
            exitFlag = true;
            break;

        default:
            cout << "Wrong Choice, try another one.\n";
            pauseScreen();
            break;
        }
    } while (!exitFlag);

    saveClients();
    saveEmployees();
}

int main() {
    mainMenu();
    return 0;
}
