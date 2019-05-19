#ifndef TELLER_H
#define TELLER_H
#include "bankelement.h"
class Teller : public BankElement{
    void evalLoan(long long &branchBalance);
    public:
    Teller(int tid = -1);
    virtual void getInfo(Account &client);
    virtual void changePIN(Account &client);
    virtual void withdrawMoney(Account &client, long long &branchBalance);
    virtual void depositMoney(Account &client, long long &branchBalance);
    void takeLoan(Account &client);
    virtual void simulate(long long &branchBalance);
};
#endif
