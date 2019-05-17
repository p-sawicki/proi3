#ifndef BANKBRANCH_H
#define BANKBRANCH_H
#include "teller.h"
#include "atm.h"
#include "account.h"
class BankBranch{
	std::vector<Account> clients;
	std::vector<Teller> tellers;
	InputTM itm;
	OutputTM otm;
	long long balance;
	unsigned int businessOnlyTellerAmount;
	unsigned int simulationLength;
	BankElement* getShortestQueue(bool includeOTM, bool includeITM, bool isBusiness);

	public:
	BankBranch(const unsigned int &clientsAmount, const unsigned &tellersAmount, const unsigned int &duration);
	void setBalance(const long long &b);
	long long getBalance() const;
	bool simulate();
};
#endif
