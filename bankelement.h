#ifndef BANKELEMENT_H
#define BANKELEMENT_H
#include "account.h"
class BankElement{
    protected:
    int id;
    std::queue<std::tuple<Account&, unsigned int>> queue;
    unsigned int timeRemaining;
    std::string name;
    void newBalance(Account &client);
    void getInfoMessage(Account &client);
    void changePINMessage(Account &client);

    public:
    BankElement(int bid, std::string n);
    virtual void getInfo(Account &client) = 0;
    virtual void changePIN(Account &client) = 0;
    virtual void withdrawMoney(Account &client) = 0;
    virtual void depositMoney(Account &client) = 0;
    int getID() const;
    size_t getQueueSize() const;
    virtual void add(Account &client, const unsigned int &time, ClientState s = ClientState::busy);
    virtual void simulate();
    void deposit(Account &client);
    void withdraw(Account &client);
};
#endif
