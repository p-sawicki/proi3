#include "bankbranch.h"
BankBranch::BankBranch(const unsigned int &clientsAmount, const unsigned int &tellersAmount)
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
long long BankBranch::getBalance() const{
	return balance;
}
BankElement* BankBranch::getShortestQueue(bool includeOTM, bool includeITM, bool isBusiness){
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
	for(int i = 0; i < tellers.size(); ++i){
		if(!isBusiness && i >= tellers.size() - businessOnlyTellerAmount)
			break;
		if(!tellers[i].getQueueSize())
			return &tellers[i];
		if(i && tellers[i].getQueueSize() < shortest){
			shortest = tellers[i].getQueueSize();
			ans = &tellers[i];
		}
	}
	return ans;	
}
void BankBranch::simulate(){
	std::uniform_int_distribution<unsigned int> chanceClientComes(1, 100);
	std::uniform_int_distribution<unsigned int> clientIDDistribution(0, clients.size() - 1);
	std::uniform_int_distribution<unsigned int> clientActionDistribution(0, 4);
	while(true){
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
		std::cout << "Client " << clientID << " comes in";
		unsigned int clientAction = clientActionDistribution(gen());
		bool isBusiness = chosen.getType() == ClientType::business;
		if(clientAction == 0){
			std::cout << " to get info\n";
			getShortestQueue(1, 1, isBusiness)->getInfo(chosen);
		}
		else if(clientAction == 1){
			std::cout << " to change PIN\n";
			getShortestQueue(1, 1, isBusiness)->changePIN(chosen);
		}
		else if(clientAction == 2){
			std::cout << " to withdraw money out\n";
			getShortestQueue(1, 0, isBusiness)->withdrawMoney(chosen);
		}
		else if(clientAction == 3){
			std::cout << " to deposit money\n";
			getShortestQueue(0, 1, isBusiness)->depositMoney(chosen);
		}
		else{ 
			std::cout << " to take out a loan\n";
			dynamic_cast<Teller*>(getShortestQueue(0, 0, isBusiness))->takeLoan(chosen);
		}
	}
    }
