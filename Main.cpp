#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <chrono>
#include <thread>
using namespace std;

int MAX_CLIENTS = 100;
int MAX_EMPLOYEES = 50;
int MAX_ADMINS = 10;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void goodbyeDelay() {
    cout << "Goodbye" << endl;
    this_thread::sleep_for(chrono::seconds(3));
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getIntInput(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "\033[31mInvalid input Please enter a valid number\033[0m\n";
            clearInputBuffer();
        }
    }
}

double getDoubleInput(string prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "\033[31mInvalid input Please enter a valid number\033[0m\n";
            clearInputBuffer();
        }
    }
}

string getStringInput(string prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void pauseAndClear() {
    cout << "Press Enter to continue ";
    getStringInput("");
    clearScreen();
}

class Validation {
public:
    static bool validateID(int id) {
        return id > 0;
    }
    static bool validateName(string name) {
        if (name.size() < 5 || name.size() > 20) return false;
        for (char c : name) {
            if (!isalpha(static_cast<unsigned char>(c)) && c != ' ') return false;
        }
        return true;
    }
    static bool validatePassword(string password) {
        return password.size() >= 8 && password.size() <= 20;
    }
    static bool validateBalance(double balance) {
        return balance >= 1500;
    }
    static bool validateSalary(double salary) {
        return salary >= 5000;
    }
};

// ====== Classes ======
// ====== Client Class ======
class Client {
private:
    int id;
    string name;
    string password;
    double balance;

public:
    Client() : id(0), name(""), password(""), balance(0) {}

    Client(int i, string n, string p, double b) {
        setId(i);
        setName(n);
        setPassword(p);
        setBalance(b);
    }

	// Setters with validation
    void setId(int i) {
        if (Validation::validateID(i)) {
            id = i;
        }
        else {
            cout << "\033[31mInvalid ID Must be positive\033[0m\n";
        }
    }

    void setName(string n) {
        if (Validation::validateName(n)) {
            name = n;
        }
        else {
            cout << "\033[31mInvalid name Letters only, 5-20 chars\033[0m\n";
        }
    }

    void setPassword(string p) {
        if (Validation::validatePassword(p)) {
            password = p;
        }
        else {
            cout << "\033[31mInvalid password 8-20 chars\033[0m\n";
        }
    }

    void setBalance(double b) {
        if (Validation::validateBalance(b)) {
            balance = b;
        }
        else {
            cout << "\033[31mInvalid balance Must be >= 1500\033[0m\n";
        }
    }

	// Getters
    int getId() { return id; }
    string getName() { return name; }
    string getPassword() { return password; }
    double getBalance() { return balance; }

	// Client Display
    void display() {
        cout << "ID: " << id << " | Name: " << name << " | Balance: " << balance << endl;
    }

    void menu();
};

// ====== Employee Class ======
class Employee {
private:
    int id;
    string name;
    string password;
    double salary;

public:
    Employee() : id(0), name(""), password(""), salary(0) {}

    Employee(int i, string n, string p, double s) {
        setId(i);
        setName(n);
        setPassword(p);
        setSalary(s);
    }

	// Setters with validation
    void setId(int i) {
        if (Validation::validateID(i)) {
            id = i;
        }
        else {
            cout << "\033[31mInvalid ID Must be positive\033[0m\n";
        }
    }

    void setName(string n) {
        if (Validation::validateName(n)) {
            name = n;
        }
        else {
            cout << "\033[31mInvalid name Letters only, 5-20 chars\033[0m\n";
        }
    }

    void setPassword(string p) {
        if (Validation::validatePassword(p)) {
            password = p;
        }
        else {
            cout << "\033[31mInvalid password 8-20 chars\033[0m\n";
        }
    }

    void setSalary(double s) {
        if (Validation::validateSalary(s)) {
            salary = s;
        }
        else {
            cout << "\033[31mInvalid salary Must be >= 5000\033[0m\n";
        }
    }

	// Getters
    int getId() { return id; }
    string getName() { return name; }
    string getPassword() { return password; }
    double getSalary() { return salary; }

	// Employee Functions
    void menu();
    void addClient(Client& client);
    Client* searchClient(int cid);
    void listClient();
    void editClient(int cid, string n, string p, double b);
};

// ====== Admin Class ======
class Admin {
private:
    int id;
    string name;
    string password;
    double salary;

public:
    Admin() : id(0), name(""), password(""), salary(0) {}

    Admin(int i, string n, string p, double s) {
        setId(i);
        setName(n);
        setPassword(p);
        setSalary(s);
    }

	// Setters with validation
    void setId(int i) {
        if (Validation::validateID(i)) {
            id = i;
        }
        else {
            cout << "\033[31mInvalid ID Must be positive\033[0m\n";
        }
    }

    void setName(string n) {
        if (Validation::validateName(n)) {
            name = n;
        }
        else {
            cout << "\033[31mInvalid name Letters only, 5-20 chars\033[0m\n";
        }
    }

    void setPassword(string p) {
        if (Validation::validatePassword(p)) {
            password = p;
        }
        else {
            cout << "\033[31mInvalid password 8-20 chars\033[0m\n";
        }
    }

    void setSalary(double s) {
        if (Validation::validateSalary(s)) {
            salary = s;
        }
        else {
            cout << "\033[31mInvalid salary Must be >= 5000\033[0m\n";
        }
    }

	// Getters
    int getId() { return id; }
    string getName() { return name; }
    string getPassword() { return password; }
    double getSalary() { return salary; }

	// Admin Functions
    void menu();
    void addClient(Client& client);
    Client* searchClient(int cid);
    void listClient();
    void editClient(int cid, string n, string p, double b);
    void addEmployee(Employee& employee);
    Employee* searchEmployee(int eid);
    void editEmployee(int eid, string n, string p, double s);
    void listEmployee();
};

Client clients[100];
int clientCount = 0;
Employee employees[50];
int employeeCount = 0;
Admin admins[10];
int adminCount = 0;

// ====== Files ======
void saveClients() {
    ofstream file("clients.txt");
    for (int i = 0; i < clientCount; i++) {
        file << clients[i].getId() << " "
            << clients[i].getName() << " "
            << clients[i].getPassword() << " "
            << clients[i].getBalance() << "\n";
    }
}

void loadClients() {
    ifstream file("clients.txt");
    clientCount = 0;
    int id;
    string name;
    string pass;
    double bal;
    while (file >> id >> name >> pass >> bal) {
        Client c;
        c.setId(id);
        c.setName(name);
        c.setPassword(pass);
        c.setBalance(bal);
        if (Validation::validateID(id) &&
            Validation::validateName(name) &&
            Validation::validatePassword(pass) &&
            Validation::validateBalance(bal) &&
            clientCount < MAX_CLIENTS) {
            clients[clientCount++] = c;
        }
    }
}

void saveEmployees() {
    ofstream file("employees.txt");
    for (int i = 0; i < employeeCount; i++) {
        file << employees[i].getId() << " "
            << employees[i].getName() << " "
            << employees[i].getPassword() << " "
            << employees[i].getSalary() << "\n";
    }
}

void loadEmployees() {
    ifstream file("employees.txt");
    employeeCount = 0;
    int id;
    string name;
    string pass;
    double sal;
    while (file >> id >> name >> pass >> sal) {
        Employee e;
        e.setId(id);
        e.setName(name);
        e.setPassword(pass);
        e.setSalary(sal);
        if (Validation::validateID(id) &&
            Validation::validateName(name) &&
            Validation::validatePassword(pass) &&
            Validation::validateSalary(sal) &&
            employeeCount < MAX_EMPLOYEES) {
            employees[employeeCount++] = e;
        }
    }
}

void saveAdmins() {
    ofstream file("admins.txt");
    for (int i = 0; i < adminCount; i++) {
        file << admins[i].getId() << " "
            << admins[i].getName() << " "
            << admins[i].getPassword() << " "
            << admins[i].getSalary() << "\n";
    }
}

void loadAdmins() {
    ifstream file("admins.txt");
    adminCount = 0;
    int id;
    string name;
    string pass;
    double sal;
    while (file >> id >> name >> pass >> sal) {
        Admin a;
        a.setId(id);
        a.setName(name);
        a.setPassword(pass);
        a.setSalary(sal);
        if (Validation::validateID(id) &&
            Validation::validateName(name) &&
            Validation::validatePassword(pass) &&
            Validation::validateSalary(sal) &&
            adminCount < MAX_ADMINS) {
            admins[adminCount++] = a;
        }
    }
}

// ====== Sub Menus ======
// ==== Client Menu ====
void Client::menu() {
    int choice;
    do {
        clearScreen();
        cout << "\033[33m ========================= \n"
            << " ======\033[92m Client Menu \033[33m====== \n" <<
            " ========================= \033[0m" << endl;
        cout << "1. Show Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "0. Exit\n";

        choice = getIntInput("Choose: ");
        clearScreen();

        switch (choice) {
        case 1:
            cout << "Balance: " << balance << endl;
            pauseAndClear();
            break;

        case 2: {
            cout << "Current Balance: " << balance << endl;
            double amount = getDoubleInput("Amount to deposit: ");
            if (amount > 0) {
                balance += amount;
                cout << "New Balance: " << balance << endl;
            }
            else {
                cout << "\033[31mInvalid amount\033[0m\n";
            }
            saveClients();
            pauseAndClear();
            break;
        }

        case 3: {
            cout << "Current Balance: " << balance << endl;
            double amount = getDoubleInput("Amount to withdraw: ");
            if (amount > 0 && amount <= balance) {
                balance -= amount;
                cout << "New Balance: " << balance << endl;
            }
            else {
                cout << "\033[31mInvalid amount or insufficient funds\033[0m\n";
            }
            saveClients();
            pauseAndClear();
            break;
        }

        case 4: {
            cout << "Current Balance: " << balance << endl;
            int target = getIntInput("Recipient Client ID: ");
            double amount = getDoubleInput("Amount to transfer: ");

            if (amount <= 0 || amount > balance) {
                cout << "\033[31mInvalid amount or insufficient funds\033[0m\n";
            }
            else {
                bool found = false;
                for (int i = 0; i < clientCount; i++) {
                    if (clients[i].getId() == target) {
                        clients[i].setBalance(clients[i].getBalance() + amount);
                        balance -= amount;
                        cout << "Transfer done Your New Balance: " << balance << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\033[31mRecipient not found\033[0m\n";
                }
            }
            saveClients();
            pauseAndClear();
            break;
        }

        case 0:
            goodbyeDelay();
            clearScreen();
            break;

        default:
            cout << "\033[31mInvalid choice\033[0m\n";
            pauseAndClear();
        }
    } while (choice != 0);
}

// Add Client
void Employee::addClient(Client& client) {
    if (clientCount >= MAX_CLIENTS) {
        cout << "\033[31mClient storage full\033[0m\n";
        return;
    }
    clients[clientCount++] = client;
    saveClients();
}

// Search Client by ID
Client* Employee::searchClient(int cid) {
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].getId() == cid) {
            return &clients[i];
        }
    }
    return nullptr;
}

// List all clients
void Employee::listClient() {
    if (clientCount == 0) {
        cout << "\033[31mNo clients\033[0m\n";
        return;
    }
    for (int i = 0; i < clientCount; i++) {
        clients[i].display();
    }
}

// Edit client details
void Employee::editClient(int cid, string n, string p, double b) {
    Client* c = searchClient(cid);
    if (!c) {
        cout << "\033[31mClient not found\033[0m\n";
        return;
    }
    c->setName(n);
    c->setPassword(p);
    c->setBalance(b);
    saveClients();
    cout << "Client updated\n";
}

// ==== Employee Menu ====
void Employee::menu() {
    int choice;
    do {
        clearScreen();
        cout << "\n==== Employee Menu ====\n";
        cout << "1. Add Client\n";
        cout << "2. Search Client by ID\n";
        cout << "3. List Clients\n";
        cout << "4. Edit Client\n";
        cout << "0. Exit\n";

        choice = getIntInput("Choose: ");
        clearScreen();

        switch (choice) {
        case 1: {
            int id = getIntInput("Client ID: ");
            string n = getStringInput("Name: ");
            string p = getStringInput("Password (must be between 8 - 20): ");
            double b = getDoubleInput("Balance: ");
            Client c;
            c.setId(id);
            c.setName(n);
            c.setPassword(p);
            c.setBalance(b);

            if (Validation::validateID(id) &&
                Validation::validateName(n) &&
                Validation::validatePassword(p) &&
                Validation::validateBalance(b)) {
                addClient(c);
                cout << "Client added\n";
            }
            else {
                cout << "\033[31mInvalid client data\033[0m\n";
            }
            pauseAndClear();
            break;
        }

        case 2: {
            int cid = getIntInput("Client ID: ");
            Client* c = searchClient(cid);
            if (c) c->display();
            else    cout << "\033[31mClient not found\033[0m\n";
            pauseAndClear();
            break;
        }

        case 3: {
            listClient();
            pauseAndClear();
            break;
        }

        case 4: {
            int cid = getIntInput("Client ID: ");
            string n = getStringInput("New Name: ");
            string p = getStringInput("New Password: ");
            double b = getDoubleInput("New Balance: ");
            editClient(cid, n, p, b);
            pauseAndClear();
            break;
        }

        case 0:
            goodbyeDelay();
            clearScreen();
            break;

        default:
            cout << "\033[31mInvalid choice\033[0m\n";
            pauseAndClear();
            break;
        }
    } while (choice != 0);
}

// Admin -> add client
void Admin::addClient(Client& client) {
    if (clientCount >= MAX_CLIENTS) {
        cout << "\033[31mClient storage full\033[0m\n";
        return;
    }
    clients[clientCount++] = client;
    saveClients();
}

// Search Client by ID
Client* Admin::searchClient(int cid) {
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].getId() == cid) {
            return &clients[i];
        }
    }
    return nullptr;
}

// List all clients
void Admin::listClient() {
    if (clientCount == 0) {
        cout << "\033[31mNo clients\033[0m\n";
        return;
    }
    for (int i = 0; i < clientCount; i++) {
        clients[i].display();
    }
}

// Edit client details
void Admin::editClient(int cid, string n, string p, double b) {
    Client* c = searchClient(cid);
    if (!c) {
        cout << "\033[31mClient not found\033[0m\n";
        return;
    }
    c->setName(n);
    c->setPassword(p);
    c->setBalance(b);
    saveClients();
    cout << "Client updated\n";
}

// Admin -> add employee
void Admin::addEmployee(Employee& employee) {
    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "\033[31mEmployee storage full\033[0m\n";
        return;
    }
    employees[employeeCount++] = employee;
    saveEmployees();
}

// Search Employee by ID
Employee* Admin::searchEmployee(int eid) {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].getId() == eid) {
            return &employees[i];
        }
    }
    return nullptr;
}

// Edit employee details
void Admin::editEmployee(int eid, string n, string p, double s) {
    Employee* e = searchEmployee(eid);
    if (!e) {
        cout << "\033[31mEmployee not found\033[0m\n";
        return;
    }
    e->setName(n);
    e->setPassword(p);
    e->setSalary(s);
    saveEmployees();
    cout << "Employee updated\n";
}

// List all employees
void Admin::listEmployee() {
    if (employeeCount == 0) {
        cout << "\033[31mNo employees\033[0m\n";
        return;
    }
    for (int i = 0; i < employeeCount; i++) {
        cout << "ID: " << employees[i].getId()
            << " | Name: " << employees[i].getName()
            << " | Salary: " << employees[i].getSalary() << endl;
    }
}

// ==== Admin Menu ====
void Admin::menu() {
    int choice;
    do {
        clearScreen();
        cout << "\n==== Admin Menu ====\n";
        cout << "1. Add Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. Edit Employee\n";
        cout << "4. List Employees\n";
        cout << "5. Add Client\n";
        cout << "6. Search Client\n";
        cout << "7. Edit Client\n";
        cout << "8. List Clients\n";
        cout << "0. Exit\n";

        choice = getIntInput("Choose: ");
        clearScreen();

        switch (choice) {
        case 1: {
            int id = getIntInput("Employee ID: ");
            string n = getStringInput("Name: ");
            string p = getStringInput("Password: ");
            double s = getDoubleInput("Salary: ");

            Employee e;
            e.setId(id);
            e.setName(n);
            e.setPassword(p);
            e.setSalary(s);

            if (Validation::validateID(id) &&
                Validation::validateName(n) &&
                Validation::validatePassword(p) &&
                Validation::validateSalary(s)) {
                addEmployee(e);
                cout << "Employee added\n";
            }
            else {
                cout << "\033[31mInvalid employee data\033[0m\n";
            }
            pauseAndClear();
            break;
        }

        case 2: {
            int eid = getIntInput("Employee ID: ");
            Employee* e = searchEmployee(eid);
            if (e) {
                cout << "ID: " << e->getId()
                    << " | Name: " << e->getName()
                    << " | Salary: " << e->getSalary() << endl;
            }
            else {
                cout << "\033[31mEmployee not found\033[0m\n";
            }
            pauseAndClear();
            break;
        }

        case 3: {
            int eid = getIntInput("Employee ID: ");
            string n = getStringInput("New Name: ");
            string p = getStringInput("New Password: ");
            double s = getDoubleInput("New Salary: ");
            editEmployee(eid, n, p, s);
            pauseAndClear();
            break;
        }

        case 4:
            listEmployee();
            pauseAndClear();
            break;

        case 5: {
            int id = getIntInput("Client ID: ");
            string n = getStringInput("Name: ");
            string p = getStringInput("Password: ");
            double b = getDoubleInput("Balance: ");

            Client c;
            c.setId(id);
            c.setName(n);
            c.setPassword(p);
            c.setBalance(b);

            if (Validation::validateID(id) &&
                Validation::validateName(n) &&
                Validation::validatePassword(p) &&
                Validation::validateBalance(b)) {
                addClient(c);
                cout << "Client added\n";
            }
            else {
                cout << "\033[31mInvalid client data\033[0m\n";
            }
            pauseAndClear();
            break;
        }

        case 6: {
            int cid = getIntInput("Client ID: ");
            Client* c = searchClient(cid);
            if (c) c->display();
            else    cout << "\033[31mClient not found\033[0m\n";
            pauseAndClear();
            break;
        }

        case 7: {
            int cid = getIntInput("Client ID: ");
            string n = getStringInput("New Name: ");
            string p = getStringInput("New Password: ");
            double b = getDoubleInput("New Balance: ");
            editClient(cid, n, p, b);
            pauseAndClear();
            break;
        }

        case 8:
            listClient();
            pauseAndClear();
            break;

        case 0:
            goodbyeDelay();
            clearScreen();
            break;

        default:
            cout << "\033[31mInvalid choice\033[0m" <<endl;
            pauseAndClear();
        }
    } while (choice != 0);
}

// ====== Main Menus ======
void clientMainMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\033[32m ========================= \n"
            << " ======\033[96m Client Menu \033[32m====== \n" <<
            " ========================= \033[0m" << endl;
        cout << "\033[32m1. \033[33mAdd Client\033[0m" << endl;
        cout << "\033[32m2. \033[33mAlready a Client\033[0m" << endl;
        cout << "\033[32m3. \033[33mEdit Client Info\033[0m" << endl;
        cout << "\033[32m0. \033[33mBack\033[0m" << endl;

        choice = getIntInput("Choose: ");
        clearScreen();

        switch (choice) {
        case 1: {
            if (clientCount >= MAX_CLIENTS) {
                cout << "\033[31mCannot add more clients\033[0m" << endl;
                pauseAndClear();
                break;
            }
            int id = getIntInput("\033[33mClient ID: \033[0m");
            string n = getStringInput("\033[33mName: \033[0m");
            string p = getStringInput("\033[33mPassword (must be between 8 - 20): \033[0m");
            double b = getDoubleInput("\033[33mBalance: \033[0m");

            Client c;
            c.setId(id);
            c.setName(n);
            c.setPassword(p);
            c.setBalance(b);

            if (Validation::validateID(id) &&
                Validation::validateName(n) &&
                Validation::validatePassword(p) &&
                Validation::validateBalance(b)) {
                clients[clientCount++] = c;
                saveClients();
                cout << "\033[92mClient added\033[0m" << endl;
            }
            else {
                cout << "\033[31mInvalid client data\033[0m" << endl;
            }
            pauseAndClear();
            break;
        }

        case 2: {
            int id = getIntInput("\033[33mClient ID: \033[0m");
            string pass = getStringInput("\033[33mPassword: \033[0m");

            bool found = false;
            for (int i = 0; i < clientCount; i++) {
                if (clients[i].getId() == id && clients[i].getPassword() == pass) {
                    clients[i].menu();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\033[31mInvalid credentials\033[0m" << endl;
                pauseAndClear();
            }
            break;
        }

        case 3: {
            int id = getIntInput("\033[33mClient ID: \033[0m");
            bool found = false;
            for (int i = 0; i < clientCount; i++) {
                if (clients[i].getId() == id) {
                    string n = getStringInput("\033[33mNew Name: \033[0m");
                    string p = getStringInput("\033[33mNew Password (must be between 8 - 20): \033[0m");
                    double b = getDoubleInput("\033[33mNew Balance: \033[0m");

                    clients[i].setName(n);
                    clients[i].setPassword(p);
                    clients[i].setBalance(b);
                    saveClients();
                    cout << "\033[92mClient updated\033[0m" << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\033[31mClient not found\033[0m" << endl;
            }
            pauseAndClear();
            break;
        }
        case 0:
            break;

        default:
            cout << "\033[31mInvalid choice\033[0m" << endl;
            pauseAndClear();
        }
    } while (choice != 0);
}

void employeeMainMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\033[32m ========================= \n"
            << " =====\033[96m Employee Menu \033[32m===== \n" <<
            " ========================= \033[0m" << endl;
        cout << "\033[32m1. \033[33mAdd Employee\033[0m" << endl;
        cout << "\033[32m2. \033[33mAlready an Employee\033[0m" << endl;
        cout << "\033[32m3. \033[33mEdit Employee Info\033[0m" << endl;
        cout << "\033[32m0. \033[33mBack\033[0m" << endl;

        choice = getIntInput("\033[33mChoose: \033[0m");
        clearScreen();

        switch (choice) {
        case 1: {
            if (employeeCount >= MAX_EMPLOYEES) {
                cout << "\033[31mCannot add more employees\033[0m" << endl;
                pauseAndClear();
                break;
            }
            int id = getIntInput("\033[33mEmployee ID: \033[0m");
            string n = getStringInput("\033[33mName: \033[0m");
            string p = getStringInput("\033[33mPassword (must be between 8 - 20): \033[0m");
            double s = getDoubleInput("\033[33mSalary: \033[0m");

            Employee e;
            e.setId(id);
            e.setName(n);
            e.setPassword(p);
            e.setSalary(s);

            if (Validation::validateID(id) &&
                Validation::validateName(n) &&
                Validation::validatePassword(p) &&
                Validation::validateSalary(s)) {
                employees[employeeCount++] = e;
                saveEmployees();
                cout << "\033[92mEmployee added\033[0m" << endl;
            }
            else {
                cout << "\033[31mInvalid employee data\033[0m" << endl;
            }
            pauseAndClear();
            break;
        }

        case 2: {
            int id = getIntInput("\033[33mEmployee ID: \033[0m");
            string pass = getStringInput("\033[33mPassword: \033[0m");

            bool found = false;
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i].getId() == id && employees[i].getPassword() == pass) {
                    employees[i].menu();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\033[31mInvalid Infos\033[0m" << endl;
                pauseAndClear();
            }
            break;
        }

        case 3: {
            int id = getIntInput("\033[33mEmployee ID: \033[0m");
            bool found = false;
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i].getId() == id) {
                    string n = getStringInput("\033[33mNew Name: \033[0m");
                    string p = getStringInput("\033[33mNew Password (must be between 8 - 20): \033[0m");
                    double s = getDoubleInput("\033[33mNew Salary: \033[0m");

                    employees[i].setName(n);
                    employees[i].setPassword(p);
                    employees[i].setSalary(s);
                    saveEmployees();
                    cout << "\033[92mEmployee updated\033[0m" << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\033[31mEmployee not found\033[0m" << endl;
            }
            pauseAndClear();
            break;
        }

        case 0:
            break;

        default:
            cout << "\033[31mInvalid choice\033[0m" << endl;
            pauseAndClear();
        }
    } while (choice != 0);
}

void adminMainMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\033[32m ========================= \n"
            << " ======\033[96m Admin Menu \033[32m======= \n" <<
            " ========================= \033[0m" << endl;
        cout << "\033[92m1. \033[33mLogin as Admin\033[0m" << endl;
        cout << "\033[92m2. \033[33mAdd a New Admin\033[0m" << endl;
        cout << "\033[92m0. \033[31mExit\033[0m" << endl;

        choice = getIntInput("\033[33mChoose: \033[0m");
        clearScreen();

        switch (choice) {
        case 1: {
            int id;
            string password;
            cout << "\033[33mEnter Admin ID: \033[0m";
            cin >> id;
            cin.ignore();
            cout << "\033[33mEnter Password: \033[0m";
            getline(cin, password);

            int loggedInAdminIndex = -1;
            for (int i = 0; i < adminCount; i++) {
                if (admins[i].getId() == id && admins[i].getPassword() == password) {
                    loggedInAdminIndex = i;
                    break;
                }
            }

            if (loggedInAdminIndex == -1) {
                cout << "\033[31mInvalid credentials\033[0m" << endl;
                pauseAndClear();
                break;
            }

            cout << "Login successful\n";

            int panelChoice;
            do {
                clearScreen();
                cout << "\033[32m ========================= \n"
                    << " ======\033[96m Admin Menu \033[32m======= \n" <<
                    " ========================= \033[0m" << endl;
                cout << "\033[92m1. \033[33mList Clients\033[0m" << endl;
                cout << "\033[92m2. \033[33mList Employees\033[0m" << endl;
                cout << "\033[92m3. \033[33mList Admins\033[0m" << endl;
                cout << "\033[92m0. \033[31mLogout\033[0m" << endl;

                panelChoice = getIntInput("\033[33mChoose: \033[0m");
                clearScreen();

                switch (panelChoice) {
                case 1:
                    admins[loggedInAdminIndex].listClient();
                    pauseAndClear();
                    break;

                case 2:
                    admins[loggedInAdminIndex].listEmployee();
                    pauseAndClear();
                    break;

                case 3:
                    if (adminCount == 0) {
                        cout << "\033[31mNo admins\033[0m" << endl;
                        pauseAndClear();
                        break;
                    }

                    for (int i = 0; i < adminCount; i++) {
                        cout << (i + 1) << ". ID: " << admins[i].getId()
                            << " | Name: " << admins[i].getName()
                            << " | Salary: " << admins[i].getSalary() << endl;
                    }

                    int adminChoice;
                    cout << "\033[33mChoose admin number to edit/delete (0 to cancel): \033[0m";
                    adminChoice = getIntInput("");
                    if (adminChoice > 0 && adminChoice <= adminCount) {
                        int action;
                        cout << "\033[33m1. Edit\n2. Delete\nChoose action: \033[0m";
                        action = getIntInput("");

                        if (action == 1) {
                            string newName, newPassword;
                            double newSalary;
                            do { newName = getStringInput("\033[33mNew Name: \033[0m"); } while (!Validation::validateName(newName));
                            do { newPassword = getStringInput("\033[33mNew Password (must be between 8 - 20): \033[0m"); } while (!Validation::validatePassword(newPassword));
                            newSalary = getDoubleInput("\033[33mNew Salary: \033[0m");
                            if (!Validation::validateSalary(newSalary)) newSalary = 5000;

                            admins[adminChoice - 1].setName(newName);
                            admins[adminChoice - 1].setPassword(newPassword);
                            admins[adminChoice - 1].setSalary(newSalary);

                            saveAdmins();
                            cout << "\033[92mAdmin updated successfully\033[0m" << endl;
                        }
                        else if (action == 2) {
                            for (int i = adminChoice - 1; i < adminCount - 1; i++) {
                                admins[i] = admins[i + 1];
                            }
                            adminCount--;
                            saveAdmins();
                            cout << "\033[92mAdmin deleted successfully\033[0m" << endl;
                        }
                        else {
                            cout << "\033[31mInvalid action\033[0m" << endl;
                        }
                        pauseAndClear();
                    }
                    break;

                case 0:
                    cout << "Logging out\n";
                    pauseAndClear();
                    break;

                default:
                    cout << "\033[31mInvalid choice\033[0m" << endl;
                    pauseAndClear();
                }

            } while (panelChoice != 0);
            break;
        }

        case 2: {
            if (adminCount >= MAX_ADMINS) {
                cout << "\033[31mAdmin storage full\033[0m" << endl;
                pauseAndClear();
                break;
            }

            int id;
            string name, password;

            do { id = getIntInput("\033[33mEnter new Admin ID: \033[0m"); } while (!Validation::validateID(id));
            do { name = getStringInput("\033[33mEnter Admin Name: \033[0m"); } while (!Validation::validateName(name));
            do { password = getStringInput("\033[33mEnter Password (must be between 8 - 20): \033[0m"); } while (!Validation::validatePassword(password));

            admins[adminCount++] = Admin(id, name, password, 5000);
            saveAdmins();
            cout << "\033[92mNew admin added successfully\033[0m" << endl;
            pauseAndClear();
            break;
        }

        case 0:
            break;
        default:
            cout << "\033[31mInvalid choice\033[0m" << endl;
            pauseAndClear();
        }

    } while (choice != 0);
}

void mainMenu() {
    loadClients();
    loadEmployees();
    loadAdmins();

    int choice;
    do {
        clearScreen();
        cout << "\033[32m ========================= \n"
            << " =======\033[96m Main Menu \033[32m======= \n" <<
            " ========================= \033[0m" << endl;;
        cout << "\033[92m1. \033[33mLogin as Client\033[0m" << endl;
        cout << "\033[92m2. \033[33mLogin as Employee\033[0m" << endl;
        cout << "\033[92m3. \033[33mLogin as Admin\033[0m" << endl;
        cout << "\033[92m0. \033[31mExit\033[33m" << endl;

        choice = getIntInput("\033[33mChoose: \033[0m");
        clearScreen();

        switch (choice) {
        case 1:
            clientMainMenu();
            break;
        case 2:
            employeeMainMenu();
            break;
        case 3:
            adminMainMenu();
            break;
        case 0:
            saveClients();
            saveEmployees();
            saveAdmins();
            goodbyeDelay();
            clearScreen();
            break;
        default:
            cout << "\033[31mInvalid choice\033[0m" << endl;
            pauseAndClear();
        }
    } while (choice != 0);
}

int main() {
    mainMenu();
    return 0;
}
