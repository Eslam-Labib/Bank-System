#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<chrono>
#include<thread>
#include<vector>
using namespace std;

const int MAX_CLIENTS = 100;
const int MAX_EMPLOYEES = 50;
const int MAX_ADMINS = 10;

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

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "Invalid input. Please enter a valid number.\n";
            clearInputBuffer();
        }
    }
}

double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "Invalid input. Please enter a valid number.\n";
            clearInputBuffer();
        }
    }
}

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void pauseAndClear() {
    cout << "Press Enter to continue...";
    getStringInput("");
    clearScreen();
}

class Validation {
public:
    static bool validateID(int id) {
        return id > 0;
    }
    static bool validateName(const string& name) {
        if (name.size() < 1 || name.size() > 20) return false;
        for (char c : name) {
            if (!isalpha(c) && c != ' ') return false;
        }
        return true;
    }
    static bool validatePassword(const string& password) {
        return password.size() >= 8 && password.size() <= 20;
    }
    static bool validateBalance(double balance) {
        return balance >= 1500;
    }
    static bool validateSalary(double salary) {
        return salary >= 5000;
    }
};

class Client {
private:
    int id;
    string name;
    string password;
    double balance;

public:
    Client() : id(0), name(""), password(""), balance(0) {}

    Client(int i, const string& n, const string& p, double b) {
        setId(i);
        setName(n);
        setPassword(p);
        setBalance(b);
    }

    void setId(int i) {
        if (Validation::validateID(i)) {
            id = i;
        }
        else {
            cout << "Invalid ID. Must be positive.\n";
        }
    }

    void setName(const string& n) {
        if (Validation::validateName(n)) {
            name = n;
        }
        else {
            cout << "Invalid name. Letters only, 1-20 chars.\n";
        }
    }

    void setPassword(const string& p) {
        if (Validation::validatePassword(p)) {
            password = p;
        }
        else {
            cout << "Invalid password. 8-20 chars.\n";
        }
    }

    void setBalance(double b) {
        if (Validation::validateBalance(b)) {
            balance = b;
        }
        else {
            cout << "Invalid balance. Must be >= 1500.\n";
        }
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getPassword() const { return password; }
    double getBalance() const { return balance; }

    void display() const {
        cout << "ID: " << id << " | Name: " << name << " | Balance: " << balance << endl;
    }

    void menu();
};

class Employee {
private:
    int id;
    string name;
    string password;
    double salary;

public:
    Employee() : id(0), name(""), password(""), salary(0) {}

    Employee(int i, const string& n, const string& p, double s) {
        setId(i);
        setName(n);
        setPassword(p);
        setSalary(s);
    }

    void setId(int i) {
        if (Validation::validateID(i)) {
            id = i;
        }
        else {
            cout << "Invalid ID. Must be positive.\n";
        }
    }

    void setName(const string& n) {
        if (Validation::validateName(n)) {
            name = n;
        }
        else {
            cout << "Invalid name. Letters only, 1-20 chars.\n";
        }
    }

    void setPassword(const string& p) {
        if (Validation::validatePassword(p)) {
            password = p;
        }
        else {
            cout << "Invalid password. 8-20 chars.\n";
        }
    }

    void setSalary(double s) {
        if (Validation::validateSalary(s)) {
            salary = s;
        }
        else {
            cout << "Invalid salary. Must be >= 5000.\n";
        }
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getPassword() const { return password; }
    double getSalary() const { return salary; }

    void menu();
    void addClient(Client& client);
    Client* searchClient(int cid);
    void listClient();
    void editClient(int cid, const string& n, const string& p, double b);
};

class Admin {
private:
    int id;
    string name;
    string password;
    double salary;

public:
    Admin() : id(0), name(""), password(""), salary(0) {}

    Admin(int i, const string& n, const string& p, double s) {
        setId(i);
        setName(n);
        setPassword(p);
        setSalary(s);
    }

    void setId(int i) {
        if (Validation::validateID(i)) {
            id = i;
        }
        else {
            cout << "Invalid ID. Must be positive.\n";
        }
    }

    void setName(const string& n) {
        if (Validation::validateName(n)) {
            name = n;
        }
        else {
            cout << "Invalid name. Letters only, 1-20 chars.\n";
        }
    }

    void setPassword(const string& p) {
        if (Validation::validatePassword(p)) {
            password = p;
        }
        else {
            cout << "Invalid password. 8-20 chars.\n";
        }
    }

    void setSalary(double s) {
        if (Validation::validateSalary(s)) {
            salary = s;
        }
        else {
            cout << "Invalid salary. Must be >= 5000.\n";
        }
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getPassword() const { return password; }
    double getSalary() const { return salary; }

    void menu();
    void addClient(Client& client);
    Client* searchClient(int cid);
    void listClient();
    void editClient(int cid, const string& n, const string& p, double b);
    void addEmployee(Employee& employee);
    Employee* searchEmployee(int eid);
    void editEmployee(int eid, const string& n, const string& p, double s);
    void listEmployee();
};

Client clients[MAX_CLIENTS];
int clientCount = 0;
Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;
Admin admins[MAX_ADMINS];
int adminCount = 0;

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

void Client::menu() {
    int choice;
    do {
        clearScreen();
        cout << "\n==== Client Menu ====\n";
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
                cout << "Invalid amount.\n";
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
                cout << "Invalid amount or insufficient funds.\n";
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
                cout << "Invalid amount or insufficient funds.\n";
            }
            else {
                bool found = false;
                for (int i = 0; i < clientCount; i++) {
                    if (clients[i].getId() == target) {
                        clients[i].setBalance(clients[i].getBalance() + amount);
                        balance -= amount;
                        cout << "Transfer done. Your New Balance: " << balance << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Recipient not found.\n";
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
            cout << "Invalid choice.\n";
            pauseAndClear();
        }
    } while (choice != 0);
}

void Employee::addClient(Client& client) {
    if (clientCount >= MAX_CLIENTS) {
        cout << "Client storage full.\n";
        return;
    }
    clients[clientCount++] = client;
    saveClients();
}

Client* Employee::searchClient(int cid) {
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].getId() == cid) {
            return &clients[i];
        }
    }
    return nullptr;
}

void Employee::listClient() {
    if (clientCount == 0) {
        cout << "No clients.\n";
        return;
    }
    for (int i = 0; i < clientCount; i++) {
        clients[i].display();
    }
}

void Employee::editClient(int cid, const string& n, const string& p, double b) {
    Client* c = searchClient(cid);
    if (!c) {
        cout << "Client not found.\n";
        return;
    }
    c->setName(n);
    c->setPassword(p);
    c->setBalance(b);
    saveClients();
    cout << "Client updated.\n";
}

void Employee::menu() {
    int choice;
    do {
        clearScreen();  // clear before showing the menu
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
                cout << "Client added.\n";
            }
            else {
                cout << "Invalid client data.\n";
            }
            pauseAndClear();
            break;
        }

        case 2: {
            int cid = getIntInput("Client ID: ");
            Client* c = searchClient(cid);
            if (c) c->display();
            else   cout << "Client not found.\n";
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
            cout << "Invalid choice.\n";
            pauseAndClear();
            break;
        }
    } while (choice != 0);
}

void Admin::addClient(Client& client) {
    if (clientCount >= MAX_CLIENTS) {
        cout << "Client storage full.\n";
        return;
    }
    clients[clientCount++] = client;
    saveClients();
}

Client* Admin::searchClient(int cid) {
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].getId() == cid) {
            return &clients[i];
        }
    }
    return nullptr;
}

void Admin::listClient() {
    if (clientCount == 0) {
        cout << "No clients.\n";
        return;
    }
    for (int i = 0; i < clientCount; i++) {
        clients[i].display();
    }
}

void Admin::editClient(int cid, const string& n, const string& p, double b) {
    Client* c = searchClient(cid);
    if (!c) {
        cout << "Client not found.\n";
        return;
    }
    c->setName(n);
    c->setPassword(p);
    c->setBalance(b);
    saveClients();
    cout << "Client updated.\n";
}

void Admin::addEmployee(Employee& employee) {
    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "Employee storage full.\n";
        return;
    }
    employees[employeeCount++] = employee;
    saveEmployees();
}

Employee* Admin::searchEmployee(int eid) {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].getId() == eid) {
            return &employees[i];
        }
    }
    return nullptr;
}

void Admin::editEmployee(int eid, const string& n, const string& p, double s) {
    Employee* e = searchEmployee(eid);
    if (!e) {
        cout << "Employee not found.\n";
        return;
    }
    e->setName(n);
    e->setPassword(p);
    e->setSalary(s);
    saveEmployees();
    cout << "Employee updated.\n";
}

void Admin::listEmployee() {
    if (employeeCount == 0) {
        cout << "No employees.\n";
        return;
    }
    for (int i = 0; i < employeeCount; i++) {
        cout << "ID: " << employees[i].getId()
            << " | Name: " << employees[i].getName()
            << " | Salary: " << employees[i].getSalary() << endl;
    }
}

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
                cout << "Employee added.\n";
            }
            else {
                cout << "Invalid employee data.\n";
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
                cout << "Employee not found.\n";
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
                cout << "Client added.\n";
            }
            else {
                cout << "Invalid client data.\n";
            }
            pauseAndClear();
            break;
        }

        case 6: {
            int cid = getIntInput("Client ID: ");
            Client* c = searchClient(cid);
            if (c) c->display();
            else   cout << "Client not found.\n";
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
            cout << "Invalid choice.\n";
            pauseAndClear();
        }
    } while (choice != 0);
}

void clientMainMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\n==== Client Main ====\n";
        cout << "1. Add Client\n";
        cout << "2. Already a Client\n";
        cout << "3. Edit Client Info\n";
        cout << "0. Back\n";

        choice = getIntInput("Choose: ");
        clearScreen();

        switch (choice) {
        case 1: {
            if (clientCount >= MAX_CLIENTS) {
                cout << "Cannot add more clients.\n";
                pauseAndClear();
                break;
            }
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
                clients[clientCount++] = c;
                saveClients();
                cout << "Client added.\n";
            }
            else {
                cout << "Invalid client data.\n";
            }
            pauseAndClear();
            break;
        }

        case 2: {
            int id = getIntInput("Client ID: ");
            string pass = getStringInput("Password: ");

            bool found = false;
            for (int i = 0; i < clientCount; i++) {
                if (clients[i].getId() == id && clients[i].getPassword() == pass) {
                    clients[i].menu();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Invalid credentials.\n";
                pauseAndClear();
            }
            // if found, Client::menu handles its own clears
            break;
        }

        case 3: {
            int id = getIntInput("Client ID: ");
            bool found = false;
            for (int i = 0; i < clientCount; i++) {
                if (clients[i].getId() == id) {
                    string n = getStringInput("New Name: ");
                    string p = getStringInput("New Password: ");
                    double b = getDoubleInput("New Balance: ");

                    clients[i].setName(n);
                    clients[i].setPassword(p);
                    clients[i].setBalance(b);
                    saveClients();
                    cout << "Client updated.\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Client not found.\n";
            }
            pauseAndClear();
            break;
        }

        case 0:
            // back to main; clear happens in main loop too
            break;

        default:
            cout << "Invalid choice.\n";
            pauseAndClear();
        }
    } while (choice != 0);
}

void employeeMainMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\n==== Employee Main ====\n";
        cout << "1. Add Employee\n";
        cout << "2. Already an Employee\n";
        cout << "3. Edit Employee Info\n";
        cout << "0. Back\n";

        choice = getIntInput("Choose: ");
        clearScreen();

        switch (choice) {
        case 1: {
            if (employeeCount >= MAX_EMPLOYEES) {
                cout << "Cannot add more employees.\n";
                pauseAndClear();
                break;
            }
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
                employees[employeeCount++] = e;
                saveEmployees();
                cout << "Employee added.\n";
            }
            else {
                cout << "Invalid employee data.\n";
            }
            pauseAndClear();
            break;
        }

        case 2: {
            int id = getIntInput("Employee ID: ");
            string name = getStringInput("Employee name: ");
            string pass = getStringInput("Password (must be between 8 - 20): ");

            bool found = false;
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i].getId() == id && employees[i].getPassword() == pass) {
                    employees[i].menu();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Invalid Infos\n";
                pauseAndClear();
            }
            break;
        }

        case 3: {
            int id = getIntInput("Employee ID: ");
            bool found = false;
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i].getId() == id) {
                    string n = getStringInput("New Name: ");
                    string p = getStringInput("New Password: ");
                    double s = getDoubleInput("New Salary: ");

                    employees[i].setName(n);
                    employees[i].setPassword(p);
                    employees[i].setSalary(s);
                    saveEmployees();
                    cout << "Employee updated\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Employee not found\n";
            }
            pauseAndClear();
            break;
        }

        case 0:
            break;

        default:
            cout << "Invalid choice\n";
            pauseAndClear();
        }
    } while (choice != 0);
}

void adminMainMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\n==== Admin Main Menu ====\n";
        cout << "1. Login as Admin\n";
        cout << "2. Add a New Admin\n";
        cout << "0. Exit\n";

        choice = getIntInput("Choose: ");
        clearScreen();

        switch (choice) {
        case 1: {
            int id;
            string password;
            cout << "Enter Admin ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Password: ";
            getline(cin, password);

            int loggedInAdminIndex = -1;
            for (int i = 0; i < adminCount; i++) {
                if (admins[i].getId() == id && admins[i].getPassword() == password) {
                    loggedInAdminIndex = i;
                    break;
                }
            }

            if (loggedInAdminIndex == -1) {
                cout << "Invalid credentials.\n";
                pauseAndClear();
                break;
            }

            cout << "Login successful!\n";

            int panelChoice;
            do {
                clearScreen();
                cout << "\n==== Admin Control Panel ====\n";
                cout << "1. List Clients\n";
                cout << "2. List Employees\n";
                cout << "3. List Admins\n";
                cout << "0. Logout\n";

                panelChoice = getIntInput("Choose: ");
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
                        cout << "No admins.\n";
                        pauseAndClear();
                        break;
                    }

                    for (int i = 0; i < adminCount; i++) {
                        cout << (i + 1) << ". ID: " << admins[i].getId()
                            << " | Name: " << admins[i].getName()
                            << " | Salary: " << admins[i].getSalary() << endl;
                    }

                    int adminChoice;
                    cout << "\nChoose admin number to edit/delete (0 to cancel): ";
                    adminChoice = getIntInput("");
                    if (adminChoice > 0 && adminChoice <= adminCount) {
                        int action;
                        cout << "1. Edit\n2. Delete\nChoose action: ";
                        action = getIntInput("");

                        if (action == 1) {
                            string newName, newPassword;
                            double newSalary;
                            do { newName = getStringInput("New Name: "); } while (!Validation::validateName(newName));
                            do { newPassword = getStringInput("New Password: "); } while (!Validation::validatePassword(newPassword));
                            newSalary = getDoubleInput("New Salary: ");
                            if (!Validation::validateSalary(newSalary)) newSalary = 5000;

                            admins[adminChoice - 1].setName(newName);
                            admins[adminChoice - 1].setPassword(newPassword);
                            admins[adminChoice - 1].setSalary(newSalary);

                            saveAdmins();
                            cout << "Admin updated successfully.\n";
                        }
                        else if (action == 2) {
                            for (int i = adminChoice - 1; i < adminCount - 1; i++) {
                                admins[i] = admins[i + 1];
                            }
                            adminCount--;
                            saveAdmins();
                            cout << "Admin deleted successfully.\n";
                        }
                        else {
                            cout << "Invalid action.\n";
                        }
                        pauseAndClear();
                    }
                    break;

                case 0:
                    cout << "Logging out...\n";
                    pauseAndClear();
                    break;

                default:
                    cout << "Invalid choice.\n";
                    pauseAndClear();
                }

            } while (panelChoice != 0);
            break;
        }

        case 2: {
            if (adminCount >= MAX_ADMINS) {
                cout << "Admin storage full.\n";
                pauseAndClear();
                break;
            }

            int id;
            string name, password;

            do { id = getIntInput("Enter new Admin ID: "); } while (!Validation::validateID(id));
            do { name = getStringInput("Enter Admin Name: "); } while (!Validation::validateName(name));
            do { password = getStringInput("Enter Password (8-20 chars): "); } while (!Validation::validatePassword(password));

            admins[adminCount++] = Admin(id, name, password, 5000);
            saveAdmins();
            cout << "New admin added successfully!\n";
            pauseAndClear();
            break;
        }

        case 0:
            break;
        default:
            cout << "Invalid choice.\n";
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
        cout << "\n===== Main Menu =====\n";
        cout << "1. Login as Client\n";
        cout << "2. Login as Employee\n";
        cout << "3. Login as Admin\n";
        cout << "0. Exit\n";

        choice = getIntInput("Choose: ");
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
            cout << "Invalid choice.\n";
            pauseAndClear();
        }
    } while (choice != 0);
}

int main() {
    mainMenu();
    return 0;
}
