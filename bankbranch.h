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

	public:
	BankBranch(const unsigned int &clientsAmount, const unsigned int &tellersAmount);
	long long getBalance() const;
	BankElement* getShortestQueue(bool includeOTM, bool includeITM, bool isBusiness);
	void simulate();
};
#endif
