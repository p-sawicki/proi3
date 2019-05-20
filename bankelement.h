//author: Piotr Sawicki
#ifndef BANKELEMENT_H
#define BANKELEMENT_H
#include "account.h"
#include "bankelementinterface.h"
class BankElement : public BankElementInterface{
    protected:
    int id;
    std::queue<std::tuple<Account&, unsigned int>> queue;
    unsigned int timeRemaining;
    std::string name;
    void newBalance(Account &client);
    void getInfoMessage(Account &client);
    void changePINMessage(Account &client);
    void add(Account &client, const unsigned int &time, ClientState s);
    void add(Account &client, const unsigned int &time);
    void deposit(Account &client, long long &branchBalance);
    void withdraw(Account &client, long long &branchBalance);

    public:
    BankElement(int bid, std::string n);
    int getID() const;
    size_t getQueueSize() const;
    std::string getName() const;
    int getQueueFront() const;
    unsigned int getTimeRemaining() const;
};
#endif
