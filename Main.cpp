#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_CLIENTS = 100;
const int MAX_EMPLOYEES = 50;
const int MAX_ADMINS = 10;

// ===== Screen Clear Function =====
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ===== GLOBAL ARRAYS - DECLARED FIRST =====
class Client; // Forward declaration
class Employee;
class Admin;

Client* clients;
int clientCount = 0;
Employee* employees;
int employeeCount = 0;
Admin* admins;
int adminCount = 0;

// ===== FILE FUNCTIONS DECLARATIONS =====
void saveClients();
void saveEmployees();
void saveAdmins();

// ===== Client Class =====
class Client {
public:
    int id;
    string name;
    string password;
    double balance;

    Client() { id = 0; balance = 0; }

    void menu() {
        int choice;
        do {
            cout << "\n--- Client Actions Menu ---\n";
            cout << "1. View Balance\n";
            cout << "2. Deposit\n";
            cout << "3. Withdraw\n";
            cout << "4. Transfer Money\n";
            cout << "0. Logout\n";
            cout << "Choose: ";
            cin >> choice;

            clearScreen();

            switch (choice) {
            case 1:
                cout << "Balance: $" << balance << endl;
                break;
            case 2: {
                double amount;
                cout << "Enter amount to deposit: $";
                cin >> amount;
                if (amount > 0) {
                    balance += amount;
                    cout << "New balance: $" << balance << endl;
                }
                else {
                    cout << "Invalid amount!\n";
                }
                break;
            }
            case 3: {
                double amount;
                cout << "Enter amount to withdraw: $";
                cin >> amount;
                if (amount > 0 && amount <= balance) {
                    balance -= amount;
                    cout << "New balance: $" << balance << endl;
                }
                else {
                    cout << "Invalid amount or insufficient funds!\n";
                }
                break;
            }
            case 4: {
                int targetID;
                double amount;
                cout << "Enter recipient Client ID: ";
                cin >> targetID;
                cout << "Enter amount to transfer: $";
                cin >> amount;

                if (amount <= 0 || amount > balance) {
                    cout << "Invalid amount or insufficient funds!\n";
                    break;
                }

                bool found = false;
                for (int i = 0; i < clientCount; i++) {
                    if (clients[i].id == targetID) {
                        clients[i].balance += amount;
                        balance -= amount;
                        cout << "Transferred $" << amount << " to " << clients[i].name << " successfully.\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Recipient not found.\n";
                break;
            }
            case 0:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
            }
        } while (choice != 0);
    }

    void display() const {
        cout << "ID: " << id << " | Name: " << name << " | Balance: $" << balance << endl;
    }
};

// ===== Employee Class =====
class Employee {
public:
    int id;
    string name;
    string password;
    double salary;

    Employee() { id = 0; salary = 0; }

    void menu() {
        int choice;
        do {
            cout << "\n--- Employee Actions Menu ---\n";
            cout << "1. Search Client by ID\n";
            cout << "2. Add Client\n";
            cout << "3. List Clients\n";
            cout << "4. Edit Client\n";
            cout << "0. Logout\n";
            cout << "Choose: ";
            cin >> choice;

            clearScreen();

            switch (choice) {
            case 1: {
                int cid;
                cout << "Enter Client ID: ";
                cin >> cid;
                bool found = false;
                for (int i = 0; i < clientCount; i++) {
                    if (clients[i].id == cid) {
                        clients[i].display();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Client not found.\n";
                break;
            }
            case 2: {
                if (clientCount >= MAX_CLIENTS) {
                    cout << "Cannot add more clients.\n";
                    break;
                }
                Client c;
                cout << "Enter Client ID: "; cin >> c.id;
                cout << "Enter Name: "; cin >> c.name;
                cout << "Enter Password: "; cin >> c.password;
                cout << "Enter Balance: $"; cin >> c.balance;
                clients[clientCount++] = c;
                saveClients();
                cout << "Client added successfully!\n";
                break;
            }
            case 3: {
                if (clientCount == 0) {
                    cout << "No clients found.\n";
                }
                else {
                    cout << "\n--- All Clients ---\n";
                    for (int i = 0; i < clientCount; i++) {
                        clients[i].display();
                    }
                }
                break;
            }
            case 4: {
                int cid;
                cout << "Enter Client ID to edit: ";
                cin >> cid;
                bool found = false;
                for (int i = 0; i < clientCount; i++) {
                    if (clients[i].id == cid) {
                        cout << "Editing Client: " << clients[i].name << "\n";
                        cout << "New Name: "; cin >> clients[i].name;
                        cout << "New Password: "; cin >> clients[i].password;
                        cout << "New Balance: $"; cin >> clients[i].balance;
                        saveClients();
                        cout << "Client updated!\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Client not found.\n";
                break;
            }
            case 0:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
            }
        } while (choice != 0);
    }
};

// ===== Admin Class =====
class Admin {
public:
    int id;
    string name;
    string password;
    double salary;

    Admin() { id = 0; salary = 0; }

    void menu() {
        int choice;
        do {
            cout << "\n--- Admin Menu ---\n";
            cout << "1. View Info\n";
            cout << "2. View All Employees\n";
            cout << "3. View All Clients\n";
            cout << "0. Logout\n";
            cout << "Choose: ";
            cin >> choice;

            clearScreen();

            switch (choice) {
            case 1:
                cout << "Admin ID: " << id << " | Name: " << name << " | Salary: $" << salary << endl;
                break;
            case 2:
                if (employeeCount == 0) {
                    cout << "No employees found.\n";
                }
                else {
                    cout << "\n--- All Employees ---\n";
                    for (int i = 0; i < employeeCount; i++) {
                        cout << "ID: " << employees[i].id << " | Name: " << employees[i].name << " | Salary: $" << employees[i].salary << endl;
                    }
                }
                break;
            case 3:
                if (clientCount == 0) {
                    cout << "No clients found.\n";
                }
                else {
                    cout << "\n--- All Clients ---\n";
                    for (int i = 0; i < clientCount; i++) {
                        clients[i].display();
                    }
                }
                break;
            case 0:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
            }
        } while (choice != 0);
    }
};

// ===== INITIALIZE ARRAYS =====
Client clientsArray[MAX_CLIENTS];
Employee employeesArray[MAX_EMPLOYEES];
Admin adminsArray[MAX_ADMINS];

// ===== FILE FUNCTIONS =====
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
        file << employees[i].id << " " << employees[i].name << " " << employees[i].password << " " << employees[i].salary << "\n";
    }
}

void loadEmployees() {
    ifstream file("employees.txt");
    employeeCount = 0;
    while (file >> employees[employeeCount].id >> employees[employeeCount].name >> employees[employeeCount].password >> employees[employeeCount].salary) {
        employeeCount++;
    }
}

void saveAdmins() {
    ofstream file("admins.txt");
    for (int i = 0; i < adminCount; i++) {
        file << admins[i].id << " " << admins[i].name << " " << admins[i].password << " " << admins[i].salary << "\n";
    }
}

void loadAdmins() {
    ifstream file("admins.txt");
    adminCount = 0;
    while (file >> admins[adminCount].id >> admins[adminCount].name >> admins[adminCount].password >> admins[adminCount].salary) {
        adminCount++;
    }
}

// ===== CLIENT MAIN MENU =====
void clientMainMenu() {
    int choice;
    do {
        cout << "\n--- Client Main Menu ---\n";
        cout << "1. Add Client\n";
        cout << "2. Already a Client\n";
        cout << "3. Edit Client\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choose: ";
        cin >> choice;

        clearScreen();

        switch (choice) {
        case 1: {
            if (clientCount >= MAX_CLIENTS) {
                cout << "Cannot add more clients.\n";
                break;
            }
            Client c;
            cout << "Enter Client ID: "; cin >> c.id;
            cout << "Enter Name: "; cin >> c.name;
            cout << "Enter Password: "; cin >> c.password;
            cout << "Enter Balance: $"; cin >> c.balance;
            clients[clientCount++] = c;
            saveClients();
            cout << "Client added successfully! Returning to main menu...\n";
            return;
        }
        case 2: {
            int id; string pass;
            cout << "Enter Client ID: "; cin >> id;
            cout << "Enter Password: "; cin >> pass;
            bool found = false;
            for (int i = 0; i < clientCount; i++) {
                if (clients[i].id == id && clients[i].password == pass) {
                    cout << "Welcome " << clients[i].name << "!\n";
                    clients[i].menu();
                    saveClients();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Invalid ID or Password.\n";
            break;
        }
        case 3: {
            int id;
            cout << "Enter Client ID to edit: "; cin >> id;
            bool found = false;
            for (int i = 0; i < clientCount; i++) {
                if (clients[i].id == id) {
                    cout << "Editing Client: " << clients[i].name << "\n";
                    cout << "New Name: "; cin >> clients[i].name;
                    cout << "New Password: "; cin >> clients[i].password;
                    cout << "New Balance: $"; cin >> clients[i].balance;
                    saveClients();
                    cout << "Client updated!\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Client not found.\n";
            break;
        }
        case 0:
            cout << "Returning to Main Menu...\n";
            clearScreen();
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

void employeeMainMenu() {
    int choice;
    do {
        cout << "\n--- Employee Main Menu ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Already an Employee\n";
        cout << "3. Edit Employee\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choose: ";
        cin >> choice;

        clearScreen();

        switch (choice) {
        case 1: {
            if (employeeCount >= MAX_EMPLOYEES) {
                cout << "Cannot add more employees.\n";
                break;
            }
            Employee e;
            cout << "Enter Employee ID: "; cin >> e.id;
            cout << "Enter Name: "; cin >> e.name;
            cout << "Enter Password: "; cin >> e.password;
            cout << "Enter Salary: $"; cin >> e.salary;
            employees[employeeCount++] = e;
            saveEmployees();
            cout << "Employee added successfully!\n";

            break;
        }
        case 2: {
            if (employeeCount == 0) {
                cout << "No employees found.\n";
                break;
            }
            cout << "Employees List:\n";
            for (int i = 0; i < employeeCount; i++) {
                cout << "ID: " << employees[i].id << " | Name: " << employees[i].name << "\n";
            }

            int id; string pass;
            cout << "Enter Employee ID: "; cin >> id;
            cout << "Enter Password: "; cin >> pass;
            bool found = false;
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i].id == id && employees[i].password == pass) {
                    cout << "Welcome Employee " << employees[i].name << "!\n";
                    employees[i].menu();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Invalid ID or Password.\n";
            break;
        }
        case 3: {
            int id;
            cout << "Enter Employee ID to edit: ";
            cin >> id;
            bool found = false;
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i].id == id) {
                    cout << "Editing Employee: " << employees[i].name << "\n";
                    cout << "New Name: "; cin >> employees[i].name;
                    cout << "New Password: "; cin >> employees[i].password;
                    cout << "New Salary: $"; cin >> employees[i].salary;
                    saveEmployees();
                    cout << "Employee updated!\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Employee not found.\n";
            break;
        }
        case 0:
            cout << "Returning to Main Menu...\n";
            clearScreen();
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

// ===== MAIN MENU =====
void mainMenu() {
    // Point global pointers to the actual arrays
    clients = clientsArray;
    employees = employeesArray;
    admins = adminsArray;

    loadClients();
    loadEmployees();
    loadAdmins();

    int choice;
    do {
        cout << "\n===== Main Menu =====\n";
        cout << "1. Login as Client\n";
        cout << "2. Login as Employee\n";
        cout << "3. Login as Admin\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        clearScreen();

        switch (choice) {
        case 1:
            clientMainMenu();
            break;
        case 2:
            employeeMainMenu();
            break;
        case 3:
        {
            if (adminCount == 0) {
                cout << "No admins found. Creating default admin...\n";
                Admin defaultAdmin;
                defaultAdmin.id = 1;
                defaultAdmin.name = "admin";
                defaultAdmin.password = "admin";
                defaultAdmin.salary = 5000;
                admins[adminCount++] = defaultAdmin;
                saveAdmins();
                cout << "Default admin created: ID=1, Password=admin\n";
            }

            int id; string pass;
            cout << "Enter Admin ID: "; cin >> id;
            cout << "Enter Password: "; cin >> pass;
            bool found = false;
            for (int i = 0; i < adminCount; i++) {
                if (admins[i].id == id && admins[i].password == pass) {
                    cout << "Welcome Admin " << admins[i].name << "!\n";
                    admins[i].menu();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Invalid ID or Password.\n";
            break;
        }
        case 0:
            cout << "Exiting program...\n";
            saveClients();
            saveEmployees();
            saveAdmins();
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

int main() {
    mainMenu();
    return 0;
}
