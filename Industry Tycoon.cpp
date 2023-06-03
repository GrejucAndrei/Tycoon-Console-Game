#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <thread>

using namespace std;

string input;
string option;
int upgradeOption;
int balance = 500;
int nrOfMachines = 0;

void clearConsole();
string getInput();
void showBalance();

void startGame();
void startGameInput();

void shop();
void shopInput();
void buyMachine();
void buyUpgrade();

void machineLine();
void machineLineInput();

void makeMoney();

struct Machine {

    int number; //e.g machine nr.1
    int level;

    Machine() {
        number = 0;
        level = 0;
    }
    Machine(int number_, int level_) {
        number = number_;
        level = level_;
    }
    void setNumber(int number_) {
        number = number_;
    }
    void setLevel(int level_) {
        level = level_;
    }
    int getNumber() {
        return number;
    }
    int getLevel() {
        return level;
    }
    void printData() {
        cout << "Machine(" << number << ") | Level(" << level << ")\n";
    }
};

vector<Machine> machines;

int main()
{
    HANDLE colorHandler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(colorHandler, 12);
    thread backGroundMoney(makeMoney);
    thread mainGame(startGame);

    backGroundMoney.join();
    mainGame.join();
    return 0;
}
void clearConsole() {
    system("cls");
}

string getInput() {
    cout << "\nInput : ";
    getline(cin, input);
    return input;
}

void showBalance() {
    cout << "Balance : " << balance << "$\n" << endl;
}

void startGame() {
    clearConsole();
    cout << "======= INDUSTRY TYCOON =======" << endl;
    cout << "\nMachine Line[1] | Shop [2] \n" << endl;
    showBalance();
    cout << "======= INDUSTRY TYCOON =======\n" << endl;
    startGameInput();
}

void startGameInput() {
    do {
        option = getInput();
        if (option == "1") {
            machineLine();
        }
        else if (option == "2") {
            shop();
        }
        else {
            cout << "Invalid Input.\n";
        }
    } while (!(option == "1" || option == "2"));
}

void shop() {
    HANDLE colorHandler = GetStdHandle(STD_OUTPUT_HANDLE);
    clearConsole();
    cout << "===================== Shop =====================\n" << endl;
    SetConsoleTextAttribute(colorHandler, 6);
    cout << "Buy Machine 100$[1] | Machine Line[2]\n" << endl;
    SetConsoleTextAttribute(colorHandler, 12);
    showBalance();
    cout << "===================== Shop =====================\n" << endl;
    shopInput();
}

void shopInput() {
    do {
        option = getInput();
        if (balance < 100 && option == "1") {
            cout << "You don't have enough money." << endl;
        }
        else if (option == "1" && balance >= 100) {
            buyMachine();
        }
        else if (option == "2") {
            machineLine();
            break;
        }
        else {
            cout << "Invalid Input. \n";
        }
    } while (!(option == "3"));
}
void buyMachine() {
    nrOfMachines++;
    balance = balance - 100;
    cout << "Machine(" << nrOfMachines << ") has been purchased." << endl;
    Machine temp(nrOfMachines, 0);
    machines.push_back(temp);
}
void machineLine() {
    clearConsole();
    cout << "================== Machine ==================\n" << endl;

    for (int i = 0; i < machines.size(); i++) {
        cout << "Machine(" << machines[i].getNumber() << ") - Level(" << machines[i].getLevel() << ")";
        if (i + 1 < machines.size()) { // for printing 2 machines on the same line
            cout << " | Machine(" << machines[i + 1].getNumber() << ") | Level(" << machines[i + 1].getLevel() << ")\n";
            i++;
        }
    }
    cout << "\n\nShop[1] | Upgrade Machine[2] | " << "Balance(" << balance<< "$)" << endl;
    cout << "=================== Line ====================" << endl;
    machineLineInput();

}
void machineLineInput() {
    while (!(option == "1")) {
        option = getInput();
        if (option == "1") {
            shop();
        }
        else if (option == "2") {
            break;
        }
        else {

        }
    }
    buyUpgrade();
}

void buyUpgrade() {
    cout << "\nMachine number : ";
    cin >> upgradeOption;
    if (upgradeOption <= machines.size() && balance >= machines[upgradeOption-1].getLevel() * 100) {
        machines[upgradeOption - 1].setLevel(machines[upgradeOption - 1].getLevel() + 1);
        balance = balance - machines[upgradeOption - 1].getLevel() * 100;

        cout << "Machine " << machines[upgradeOption - 1].getNumber() << " has been upgraded to level : " << machines[upgradeOption - 1].getLevel() << endl;

        this_thread::sleep_for(chrono::seconds(3));
        machineLine();
    }
    else if (balance < machines[upgradeOption - 1].getLevel() * 100) {
        cout << "Insufficient funds";
        this_thread::sleep_for(chrono::seconds(2));
        machineLine();
    }
    else {
        machineLine();
    }
}

void makeMoney() {
    while (true) {
        if (machines.size() > 0) {
            for (int i = 0; i < machines.size(); i++) {
                if (machines[i].getLevel() == 0) {
                    balance += 1;
                }
                else {
                    balance += 2 * machines[i].getLevel();
                }
            }
            this_thread::sleep_for(chrono::seconds(3));
        }
    }
}
