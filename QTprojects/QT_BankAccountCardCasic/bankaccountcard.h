#ifndef BANKACCOUNTCARD_H
#define BANKACCOUNTCARD_H
#include <QString>
#include <QVector>
#include <QMap>




class Account{
    int accountID;
    int balance;
public:
    Account();
    int getBalance();
};

class Card{
    int cardID;
    int cardPIN;
    Account *connectedAccount;
public:
    Card();
    Account* getAccess();
};

class Bank{
    QString bankName;
    int bankBalance;
    QMap <int, Card> cards;
    QMap <int, Account> accounts;
public:
    Bank();
    bool OpenSession(int cardid, int cardpin);
    void closeSession();
    void deposit();
    void cashout();
    void transfer();
    int getBalance();
    int getAccountID();
};



#endif // BANKACCOUNTCARD_H
