#ifndef ATM_H
#define ATM_H
#include "bankelement.h"
class ATM : public BankElement{
	protected:
	std::string errorMessageLog() const;
    public:
    ATM(int aid = -1);
    virtual void getInfo(Account &client);
    virtual void changePIN(Account &client);
    virtual void simulate(long long &balance);
};
class InputTM : public ATM{
    public:
    InputTM(int iid = -1);
    virtual void withdrawMoney(Account &client, long long &branchBalance);
    virtual void depositMoney(Account &client, long long &branchBalance);
};
class OutputTM : public ATM{
    public:
    OutputTM(int oid = -1);
    virtual void withdrawMoney(Account &client, long long &branchBalance);
    virtual void depositMoney(Account &client, long long &branchBalance);
};
#endif
