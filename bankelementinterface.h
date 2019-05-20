#ifndef BANKELEMENTINTERFACE_H
#define BANKELEMENTINTERFACE_H
#include "basics.h"
class BankElementInterface{
	protected:
		BankElementInterface(){};
	public:
    virtual void getInfo(Account &client) = 0;
    virtual void changePIN(Account &client) = 0;
    virtual void withdrawMoney(Account &client, long long &branchBalance) = 0;
    virtual void depositMoney(Account &client, long long &branchBalance) = 0;
    virtual void simulate(long long &balance) = 0; //advances state of element as if 1 minute has passed.
    virtual int getID() const = 0;
    virtual size_t getQueueSize() const = 0;
    virtual std::string getName() const = 0;
    virtual int getQueueFront() const = 0;
    virtual unsigned int getTimeRemaining() const = 0;
    virtual ~BankElementInterface(){}
};
#endif
