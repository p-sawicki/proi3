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
    virtual void withdrawMoney(Account &client, long long &branchBalance) = 0;
    virtual void depositMoney(Account &client, long long &branchBalance) = 0;
    virtual void simulate(long long &balance) = 0; //advances state of element as if 1 minute has passed.
    int getID() const;
    size_t getQueueSize() const;
    std::string getName() const;
    int getQueueFront() const;
    unsigned int getTimeRemaining() const;
    virtual ClientType getType() const;
    void add(Account &client, const unsigned int &time, ClientState s);
    void add(Account &client, const unsigned int &time);
    void deposit(Account &client, long long &branchBalance);
    void withdraw(Account &client, long long &branchBalance);
    virtual ~BankElement();
};
#endif
