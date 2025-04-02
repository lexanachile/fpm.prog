#ifndef BANKACCOUNTCARD_H
#define BANKACCOUNTCARD_H
#include <QString>
#include <QVector>
#include <QMap>
class Card;



class Account{
    int accountID;
    int balance;
    QString owner;
    int maxCards;
    int numOfCards;
public:
    Account(){
        accountID = 0;
        owner = "";
        balance = 0;
        maxCards = 3;
        numOfCards = 0;
    }
    Account(int id, QString person){
        accountID = id;
        owner = person;
        balance = 0;
        maxCards = 3;
        numOfCards = 0;
    };
    Account(const Account& acc){
        accountID = acc.accountID;
        balance = acc.balance;
        owner = acc.owner;
        maxCards = acc.maxCards;
        numOfCards = acc.numOfCards;
    }
    int getBalance(){
        return balance;
    };
    void deposit(const int& money){
        if(false) throw "Balance overflow";
        balance += money;
    };
    void cashout(const int& calledCash){
        if(calledCash > balance) throw "Not enough cash";
        balance -= calledCash;
    };
    int getAccountID(){
        return accountID;
    }
    bool canAddCard(){
        if(numOfCards < maxCards) return true;
                return false;
    }
    void addCard(){
        ++numOfCards;
    }
};

class Card{
    int cardID;
    int cardPIN;
    Account *connectedAccount;
public:
    Card(){
        cardID = 0;
        cardPIN = 0;
        connectedAccount = nullptr;
    }
    Card(int id, int pin, Account* acc){
        cardID = id;
        cardPIN = pin;
        connectedAccount = acc;
    };
    Card(const Card& c){
        cardID = c.cardID;
        cardPIN = c.cardPIN;
        connectedAccount = c.connectedAccount;
    }
    Account* getAccess(const int& cardpin){
        if(cardpin == cardPIN) return connectedAccount;
        else return nullptr;
    };
    int getAccountID(){
        return connectedAccount->getAccountID();
    }
    int getID(){
        return cardID;
    }
};

class Bank{
    QString bankName;
    int bankBalance;
    QMap <int, Card> cards;
    QMap <int, Account> accounts;
    Account* currentAccount;
public:
    Bank(QString bankName){
        bankBalance = 0;
        currentAccount = nullptr;
    };
    ~Bank(){
        cards.clear();
        accounts.clear();
    }
    bool OpenSession(const int& cardid, const int& cardpin){
        //Card * currentCard = &cards[cardid];
        currentAccount = cards[cardid].getAccess(cardpin);
        if(currentAccount == nullptr) return 0;
        return true;
    };
    void closeSession(){
        currentAccount = nullptr;
    };
    void deposit(const int& money){
        if(currentAccount == nullptr) throw "Session is not opend";
        try {
            currentAccount->deposit(money);
            bankBalance += money;
        } catch (const char* str) {
            throw str;
        }
    };
    void cashout(const int calledCash){
        if(currentAccount == nullptr) throw "Session is not opend";
        try {
            currentAccount->cashout(calledCash);
            bankBalance -= calledCash;
        } catch (const char* str) {
            throw str;
        }
    };
    void transfer(const int& money, const int& cardID){
        if(currentAccount == nullptr) throw "Session is not opend";
        int newAccID = cards[cardID].getAccountID();
        Account* transferTo = &accounts[newAccID];
        try {
            currentAccount->cashout(money);
            transferTo->deposit(money);
        } catch (const char* str) {
            throw str;
        }
    };
    int getBalance(){
        if(currentAccount == nullptr) throw "Session is not opend";
        return currentAccount->getBalance();
    };
    int getAccountID(){
        if(currentAccount == nullptr) throw "Session is not opend";
        return currentAccount->getAccountID();
    };

    int openAccount(const QString& owner){
        int AccountID;
        for (int var = 1; var < 200; ++var) {
            if (!accounts.contains(var)) {  // если такого ключа нет в QMap
                AccountID = var;
                break;
            }
        }
        accounts.insert(AccountID, Account(AccountID, owner));
        return AccountID;
    };
    int addCard(const int& accid){
        Account* acc = &accounts[accid];
        if(!acc->canAddCard()) throw "Max number of cards";
        int cardid = 0;
        for (int var = 10; var < 2000000; ++var) {
            auto it = cards.find(var);
            if (it == cards.end()) {
                cardid = var;
                break;
            }
        }
        Card card(cardid, 1111, acc);
        acc->addCard();
        cards.insert(cardid, card);
        return cardid;
    }
};



#endif // BANKACCOUNTCARD_H
