#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;
class Validation {
public:
    static bool checkName(string name) {
        return name.length() >= 5 && name.length() <= 20;
    }
    static bool checkPassword(string password) {
        return password.length() >= 8 && password.length() <= 20;
    }
    static bool checkBalance(double balance) {
        return balance <= 1500;
    }
};
class pirson {
protected:
    string name;
    string password;
    int id;
public:
    pirson() {
        this->id = 0;
    }
    pirson(string name,string password,int id) {
        this->name = name;
        this->password = password;
        this->id = id;
    }

};
class client : public pirson {
private:
    double balance;
public:
    client() {
        balance = 0;
    }
    client(string name, string password, int id,double balance) {
        setName(name);
        setPassword(password);
        setId(id);
        setBalance(balance);
    }
    void setName(string name) {
            this->name = name;
    }
    void setPassword(string password) {
            this->password = password;
    }
    void setId(int id) {
        this->id = id;
    }
    void setBalance(double balance) {
            this->balance = balance;
    }
    string getName() {
        return this->name;
    }
    string getPassword() {
        return this->password;
    }
    int getId() {
        return this->id;
    }
    double getBalance() {
        return this->balance;
    }
    void deposit(double amount) {
         balance += amount;
    }
    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        }
        else {
            cout << "Insufficient balance.\n";
        }
    }
    void  transferTo(double amount, client &c) {
        if (amount <= balance) {
            withdraw(amount);
            c.deposit(amount);
        }
    }
    void display() {
        cout << "name     = ";
        if (Validation::checkName(name)) {
            cout << name << endl;
        }
        else {
            cout << "Invalid Name: " << name << endl;
        }

        cout << "id       = " << id << endl;

        cout << "password = ";
        if (Validation::checkPassword(password)) {
            cout << password << endl;
        }
        else {
            cout << "Invalid Password: " << password << endl;
        }

        cout << "balance  = ";
        if (Validation::checkBalance(balance)) {
            cout << balance << endl;
        }
        else {
            cout << "Invalid Balance: " << balance << endl;
        }
    }
};










int main() {  
    
    cout << endl << endl << endl;
    cout << "                        *       *  *******  *          ******     ****       * *    * *  ******* " << endl;
    cout << "                        *       *  **       *         *         *      *     *  *  *  *  **      " << endl;
    cout << "                        *   *   *  *******  *        *         *        *    *   *    *  ******* " << endl;
    cout << "                        *  * *  *  **       *         *         *      *     *        *  **      " << endl;
    cout << "                        * *   * *  *******  *******    ******     ****       *        *  ******* " << endl;
    cout << endl << endl << endl;
    cout << "                                                    ********    ****    " << endl;
    cout << "                                                       **     *      *  " << endl;
    cout << "                                                       **    *        * " << endl;
    cout << "                                                       **     *      *  " << endl;
    cout << "                                                       **       ****    " << endl;
    cout << endl << endl << endl;
    cout << "                                              *****    *****    *   *    ****** " << endl;
    cout << "                                              *    *   *   *    **  *   *       " << endl;
    cout<<  "                                              *****    *****    * * *  *        " << endl;
    cout<<  "                                              *    *   *   *    *  **   *       " << endl;
    cout<<  "                                              *****    *   *    *   *    ****** " << endl;
    Sleep(3000);
    system("cls");
    client c1("mohamed", "777", 333, 2300), c2;
    c2.setName("ahmd");
    c2.setId(333);
    c2.setPassword("5555");
    c2.setBalance(1700);
    c1.transferTo(500, c2);
    c1.display();
    c2.display();
}
