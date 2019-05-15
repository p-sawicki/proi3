#ifndef BANKBRANCH_H
#define BANKBRANCH_H
#include "teller.h"
#include "atm.h"
#include "account.h"
template<unsigned int duration>
class BankBranch{
	std::vector<Account> clients;
	std::vector<Teller> tellers;
	InputTM itm;
	OutputTM otm;
	long long balance;
	unsigned int businessOnlyTellerAmount;
	BankElement* getShortestQueue(bool includeOTM, bool includeITM, bool isBusiness){
		BankElement* ans = &tellers[0];
		unsigned int shortest = tellers[0].getQueueSize();
		if(includeOTM){
			if(!otm.getQueueSize())
			return &otm;
			if(otm.getQueueSize() < shortest){
				shortest = otm.getQueueSize();
				ans = &otm;
			}
		}
		if(includeITM){
			if(!itm.getQueueSize())
				return &itm;
			if(itm.getQueueSize() < shortest){
				shortest = itm.getQueueSize();
				ans = &itm;
			}
		}
		unsigned int start;
		isBusiness ? start = tellers.size() - 1 : start = tellers.size() - businessOnlyTellerAmount - 1;
		for(int i = start; i >= 0; --i){
			if(!tellers[i].getQueueSize())
				return &tellers[i];
			if(i && tellers[i].getQueueSize() < shortest){
				shortest = tellers[i].getQueueSize();
				ans = &tellers[i];
			}
		}
		return ans;	
	}

	public:
	BankBranch(const unsigned int &clientsAmount, const unsigned int &tellersAmount)
    		: itm(InputTM(tellersAmount)), otm(OutputTM(tellersAmount + 1)), clients(std::vector<Account>(0)),
		tellers(std::vector<Teller>(0)), balance(10'000'000){
    		unsigned int max = clientsAmount > tellersAmount ? clientsAmount : tellersAmount;
    	int i = 0;
   	for(; i < max; ++i){
       		if(i < clientsAmount)
            		clients.push_back(Account(i));
         	if(i < tellersAmount)
            		tellers.push_back(Teller(i));
    	}
    	if(!(tellersAmount / 10) && tellersAmount >= 2)
		businessOnlyTellerAmount = 1;
    	else
		businessOnlyTellerAmount = tellersAmount / 10;
	}
	void simulate(){
		std::uniform_int_distribution<unsigned int> chanceClientComes(1, 100);
		std::uniform_int_distribution<unsigned int> clientIDDistribution(0, clients.size() - 1);
		std::uniform_int_distribution<unsigned int> clientActionDistribution(0, 4);
		for(unsigned int i = 0; i < duration; ++i){
			otm.simulate();
			itm.simulate();
			for(int i = 0; i < tellers.size(); ++i)
				tellers[i].simulate(balance);
			std::cout << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			unsigned int clientID = clientIDDistribution(gen());
			Account &chosen = clients[clientID];
			if((chanceClientComes(gen()) > 100) || chosen.getState() != ClientState::notBusy){
				std::cout << "No client\n";
				continue;
			}
			unsigned int clientAction = clientActionDistribution(gen());
			bool isBusiness = chosen.getType() == ClientType::business;
			if(clientAction == 0)
				getShortestQueue(1, 1, isBusiness)->getInfo(chosen);
			else if(clientAction == 1)
				getShortestQueue(1, 1, isBusiness)->changePIN(chosen);
			else if(clientAction == 2)
				getShortestQueue(1, 0, isBusiness)->withdrawMoney(chosen);
			else if(clientAction == 3)
				getShortestQueue(0, 1, isBusiness)->depositMoney(chosen);
			else 
				dynamic_cast<Teller*>(getShortestQueue(0, 0, isBusiness))->takeLoan(chosen);
		}
	}
};
#endif
