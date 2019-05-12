#ifndef ATM_H
#define ATM_H
#include "bankelement.h"
class ATM : public BankElement{
    public:
    ATM(int aid = -1);
    virtual void getInfo(Account &client);
    virtual void changePIN(Account &client);
}
class InputTM : public ATM{
    public:
    InputTM(int iid = -1);
    virtual void withdrawMoney(Account &client);
    virtual void depositMoney(Account &client);
}
class OutputTM : public ATM{
    public:
    OutputTM(int oid = -1);
    virtual void withdrawMoney(Account &client);
    virtual void depositMoney(Account &client);
}
#endif