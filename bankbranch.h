//author: Piotr Sawicki
#ifndef BANKBRANCH_H
#define BANKBRANCH_H
#include "teller.h"
#include "atm.h"
#include "account.h"
class BankBranch{
	InputTM itm;
	OutputTM otm;
	std::vector<Account> clients;
	std::vector<Teller> tellers;
	long long balance;
	unsigned int simulationLength;
	unsigned int businessOnlyTellerAmount;
	BankElement* getShortestQueue(bool includeOTM, bool includeITM, bool isBusiness);
    template<class T>
    void logQueueInfo(T *element){
        std::stringstream message;
        message << element->getName() << "\t" << element->getID() << "\t" << element->getQueueFront() << "\t\t" << element->getTimeRemaining() << "\t\t" << element->getQueueSize() << "\n";
        file().write(message.str());
    }

	public:
	BankBranch(const unsigned int &clientsAmount, const unsigned &tellersAmount, const unsigned int &duration);
	void setBalance(const long long &b);
	long long getBalance() const;
	bool simulate();
};
#endif