#include <iostream>
#include <windows.h>

class BankAccount {
private:
    int accountNumber;
    double balance;
    static double interestRate;
    static int totalAccounts;

public:
    BankAccount(int number, double bal) : accountNumber(number), balance(bal) {
        totalAccounts++;
    }

    ~BankAccount() {
        totalAccounts--;
    }

    void applyInterest() {
        balance += balance * interestRate / 100;
    }

    static void setInterestRate(double rate) {
        if (rate >= 0) {
            interestRate = rate;
        } else {
            std::cerr << "Ставка не может быть отрицательной!";
        }
    }

    static double getInterestRate() {
        return interestRate;
    }

    void printInfo() {
        std::cout << "Аккаунт №" << accountNumber << std::endl << "Баланс: " << balance << " руб." << "\n\n";
    }

    static int getTotalAccounts() {
        return totalAccounts;
    }

    void transfer(double amount, BankAccount& targetAccount) {
        if (this->balance - amount >= 0) {
            this->balance -= amount;
            targetAccount.setBalance(targetAccount.getBalance() + amount);
        } else {
            std::cerr << "Недостаточно средств!";
        }
    }

    void closeAccount() {
        balance = 0;
        totalAccounts--;
    }

    double getBalance() {
        return balance;
    }

    void setBalance(double value) {
        this->balance = value;
    }
};

double BankAccount::interestRate = 0;
int BankAccount::totalAccounts = 0;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    BankAccount accList[] = {
        BankAccount(1, 200),
        BankAccount(2, 500),
        BankAccount(3, 1500)
    };

    for (BankAccount& acc: accList) {
        acc.printInfo();
    }

    BankAccount::setInterestRate(10);

    for (BankAccount& acc: accList) {
        acc.applyInterest();
    }

    for (BankAccount& acc: accList) {
        acc.printInfo();
    }

    double sum = 0;

    for (BankAccount& acc: accList) {
        sum += acc.getBalance();
    }

    std::cout << "Суммарный баланс всех счетов: " << sum << std::endl << "Процентная ставка: " << BankAccount::getInterestRate() << "%" << std::endl;
}