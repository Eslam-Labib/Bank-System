#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
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

class Validation {
public:
    static bool validateID(int id) {
        return id > 0;
    }

    static bool validateName(const string& name) {
        if (name.size() < 5 || name.size() > 20) return false;
        for (char c : name) {
            if (!isalpha(c)) return false;
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
    Client() {
        id = 0;
        name = "";
        password = "";
        balance = 0;
    }

    Client(int i, const string& n, const string& p, double b) {
        id = 0;
        balance = 0;
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
            cout << "Invalid name. Letters only, 5-20 chars.\n";
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

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getPassword() const {
        return password;
    }

    double getBalance() const {
        return balance;
    }

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
    Employee() {
        id = 0;
        name = "";
        password = "";
        salary = 0;
    }

    Employee(int i, const string& n, const string& p, double s) {
        id = 0;
        salary = 0;
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
            cout << "Invalid name. Letters only, 5-20 chars.\n";
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

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getPassword() const {
        return password;
    }

    double getSalary() const {
        return salary;
    }

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
    Admin() {
        id = 0;
        name = "";
        password = "";
        salary = 0;
    }

    Admin(int i, const string& n, const string& p, double s) {
        id = 0;
        salary = 0;
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
            cout << "Invalid name. Letters only, 5-20 chars.\n";
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

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getPassword() const {
        return password;
    }

    double getSalary() const {
        return salary;
    }

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
        cout << "\n==== Client Menu ====\n";
        cout << "1. Show Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        clearScreen();

        if (choice == 1) {
            cout << "Balance: " << balance << endl;
        }
        else if (choice == 2) {
            cout << "Current Balance: " << balance << endl;
            double amount;
            cout << "Amount to deposit: ";
            cin >> amount;
            if (amount > 0) {
                balance += amount;
                cout << "New Balance: " << balance << endl;
            }
            else {
                cout << "Invalid amount.\n";
            }
        }
        else if (choice == 3) {
            cout << "Current Balance: " << balance << endl;
            double amount;
            cout << "Amount to withdraw: ";
            cin >> amount;
            if (amount > 0 && amount <= balance) {
                balance -= amount;
                cout << "New Balance: " << balance << endl;
            }
            else {
                cout << "Invalid amount or insufficient funds.\n";
            }
        }
        else if (choice == 4) {
            cout << "Current Balance: " << balance << endl;
            int target;
            double amount;
            cout << "Recipient Client ID: ";
            cin >> target;
            cout << "Amount to transfer: ";
            cin >> amount;
            if (amount <= 0 || amount > balance) {
                cout << "Invalid amount or insufficient funds.\n";
            }
            else {
                bool found = false;
                for (int i = 0; i < clientCount; i++) {
                    if (clients[i].getId() == target) {
                        double nb = clients[i].getBalance() + amount;
                        clients[i].setBalance(nb);
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
        }
        else if (choice == 0) {
            cout << "Goodbye.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
        saveClients();
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
        cout << "\n==== Employee Menu ====\n";
        cout << "1. Add Client\n";
        cout << "2. Search Client by ID\n";
        cout << "3. List Clients\n";
        cout << "4. Edit Client\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        clearScreen();

        if (choice == 1) {
            int id;
            string n;
            string p;
            double b;
            cout << "Client ID: ";
            cin >> id;
            cout << "Name: ";
            cin >> n;
            cout << "Password: ";
            cin >> p;
            cout << "Balance: ";
            cin >> b;
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
        }
        else if (choice == 2) {
            int cid;
            cout << "Client ID: ";
            cin >> cid;
            Client* c = searchClient(cid);
            if (c) {
                c->display();
            }
            else {
                cout << "Client not found.\n";
            }
        }
        else if (choice == 3) {
            listClient();
        }
        else if (choice == 4) {
            int cid;
            string n;
            string p;
            double b;
            cout << "Client ID: ";
            cin >> cid;
            cout << "New Name: ";
            cin >> n;
            cout << "New Password: ";
            cin >> p;
            cout << "New Balance: ";
            cin >> b;
            editClient(cid, n, p, b);
        }
        else if (choice == 0) {
            cout << "Goodbye.\n";
        }
        else {
            cout << "Invalid choice.\n";
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
        cout << "Choose: ";
        cin >> choice;

        clearScreen();

        if (choice == 1) {

            int id;
            string n;
            string p;
            double s;

            cout << "Employee ID: ";
            cin >> id;
            cout << "Name: ";
            cin >> n;
            cout << "Password: ";
            cin >> p;
            cout << "Salary: ";
            cin >> s;

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
        }
        else if (choice == 2) {
            int eid;
            cout << "Employee ID: ";
            cin >> eid;
            Employee* e = searchEmployee(eid);
            if (e) {
                cout << "ID: " << e->getId()
                    << " | Name: " << e->getName()
                    << " | Salary: " << e->getSalary() << endl;
            }
            else {
                cout << "Employee not found.\n";
            }
        }
        else if (choice == 3) {

            int eid;
            string n;
            string p;
            double s;

            cout << "Employee ID: ";
            cin >> eid;
            cout << "New Name: ";
            cin >> n;
            cout << "New Password: ";
            cin >> p;
            cout << "New Salary: ";
            cin >> s;

            editEmployee(eid, n, p, s);
        }
        else if (choice == 4) {
            listEmployee();
        }
        else if (choice == 5) {

            int id;
            string n;
            string p;
            double b;

            cout << "Client ID: ";
            cin >> id;
            cout << "Name: ";
            cin >> n;
            cout << "Password: ";
            cin >> p;
            cout << "Balance: ";
            cin >> b;

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
        }
        else if (choice == 6) {
            int cid;
            cout << "Client ID: ";
            cin >> cid;
            Client* c = searchClient(cid);
            if (c) {
                c->display();
            }
            else {
                cout << "Client not found.\n";
            }
        }
        else if (choice == 7) {
            int cid;
            string n;
            string p;
            double b;
            cout << "Client ID: ";
            cin >> cid;
            cout << "New Name: ";
            cin >> n;
            cout << "New Password: ";
            cin >> p;
            cout << "New Balance: ";
            cin >> b;
            editClient(cid, n, p, b);
        }
        else if (choice == 8) {
            listClient();
        }
        else if (choice == 0) {
            cout << "Goodbye.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void clientMainMenu() {
    int choice;
    do {
        cout << "\n==== Client Main ====\n";
        cout << "1. Add Client\n";
        cout << "2. Already a Client\n";
        cout << "3. Edit Client Info\n";
        cout << "0. Back\n";
        cout << "Choose: ";
        cin >> choice;

        clearScreen();

        if (choice == 1) {
            if (clientCount >= MAX_CLIENTS) {
                cout << "Cannot add more clients.\n";
                continue;
            }

            int id;
            string n;
            string p;
            double b;

            cout << "Client ID: ";
            cin >> id;
            cout << "Name: ";
            cin >> n;
            cout << "Password: ";
            cin >> p;
            cout << "Balance: ";
            cin >> b;

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
        }
        else if (choice == 2) {
            int id;
            string pass;
            cout << "Client ID: ";
            cin >> id;
            cout << "Password: ";
            cin >> pass;
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
            }
        }
        else if (choice == 3) {
            int id;
            cout << "Client ID: ";
            cin >> id;
            bool found = false;
            for (int i = 0; i < clientCount; i++) {
                if (clients[i].getId() == id) {

                    string n;
                    string p;
                    double b;

                    cout << "New Name: ";
                    cin >> n;
                    cout << "New Password: ";
                    cin >> p;
                    cout << "New Balance: ";
                    cin >> b;
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
        }
        else if (choice == 0) {
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void employeeMainMenu() {
    int choice;
    do {
        cout << "\n==== Employee Main ====\n";
        cout << "1. Add Employee\n";
        cout << "2. Already an Employee\n";
        cout << "3. Edit Employee Info\n";
        cout << "0. Back\n";
        cout << "Choose: ";
        cin >> choice;

        clearScreen();

        if (choice == 1) {
            if (employeeCount >= MAX_EMPLOYEES) {
                cout << "Cannot add more employees.\n";
                continue;
            }

            int id;
            string n;
            string p;
            double s;

            cout << "Employee ID: ";
            cin >> id;
            cout << "Name: ";
            cin >> n;
            cout << "Password: ";
            cin >> p;
            cout << "Salary: ";
            cin >> s;

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
        }
        else if (choice == 2) {
            int id;
            string pass;
            cout << "Employee ID: ";
            cin >> id;
            cout << "Password: ";
            cin >> pass;
            bool found = false;
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i].getId() == id && employees[i].getPassword() == pass) {
                    employees[i].menu();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Invalid credentials.\n";
            }
        }
        else if (choice == 3) {
            int id;
            cout << "Employee ID: ";
            cin >> id;
            bool found = false;
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i].getId() == id) {
                    string n;
                    string p;
                    double s;
                    cout << "New Name: ";
                    cin >> n;
                    cout << "New Password: ";
                    cin >> p;
                    cout << "New Salary: ";
                    cin >> s;
                    employees[i].setName(n);
                    employees[i].setPassword(p);
                    employees[i].setSalary(s);
                    saveEmployees();
                    cout << "Employee updated.\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Employee not found.\n";
            }
        }
        else if (choice == 0) {
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void adminMainMenu() {
    if (adminCount == 0) {
        Admin a;
        a.setId(1);
        a.setName("AdminA");
        a.setPassword("adminpass");
        a.setSalary(5000);
        admins[adminCount++] = a;
        saveAdmins();
    }

    int id;
    string pass;
    cout << "Admin ID: ";
    cin >> id;
    cout << "Password: ";
    cin >> pass;

    bool ok = false;
    int idx = -1;
    for (int i = 0; i < adminCount; i++) {
        if (admins[i].getId() == id && admins[i].getPassword() == pass) {
            ok = true;
            idx = i;
            break;
        }
    }
    if (!ok) {
        cout << "Invalid credentials\n";
        return;
    }

    admins[idx].menu();
}

void mainMenu() {
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

        if (choice == 1) {
            clientMainMenu();
        }
        else if (choice == 2) {
            employeeMainMenu();
        }
        else if (choice == 3) {
            adminMainMenu();
        }
        else if (choice == 0) {
            saveClients();
            saveEmployees();
            saveAdmins();
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

int main() {
    mainMenu();
    return 0;
}
