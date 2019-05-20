//author: Piotr Sawicki
#include "bankbranch.h"
#define STARTING_BRANCH_BALANCE 10'000'000
BankElement* BankBranch::getShortestQueue(bool includeOTM, bool includeITM, bool isBusiness){
	BankElement* ans = NULL;
	unsigned int shortest = UINT_MAX; 
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
	for(unsigned int i = 0; i < tellers.size() - (!isBusiness) * businessOnlyTellerAmount; ++i){
		if(!tellers[i].getQueueSize())
			return &tellers[i];
		if(tellers[i].getQueueSize() < shortest){
			shortest = tellers[i].getQueueSize();
			ans = &tellers[i];
		}
	}
	return ans;	
}
BankBranch::BankBranch(const unsigned int &clientsAmount, const unsigned int &tellersAmount, const unsigned int &duration)
        : itm(InputTM(tellersAmount)), otm(OutputTM(tellersAmount + 1)), clients(std::vector<Account>(0)), 
        tellers(std::vector<Teller>(0)), balance(STARTING_BRANCH_BALANCE), simulationLength(duration){
    unsigned int max = clientsAmount > tellersAmount ? clientsAmount : tellersAmount;
    for(unsigned int i = 0; i < max; ++i){
        if(!(tellersAmount / 10) && tellersAmount > 1)
            businessOnlyTellerAmount = 1;
        else
            businessOnlyTellerAmount = tellersAmount / 10;
        if(i < clientsAmount){
            clients.push_back(Account(i));
            balance += clients[i].getBalance();
        }
        if(i < tellersAmount){
            tellers.push_back(Teller(i));
        }
    }
}
void BankBranch::setBalance(const long long &b){
	balance = b;
}
long long BankBranch::getBalance() const{
	return balance;
}
bool BankBranch::simulate(){
    if(!clients.size())
        return true;
    const unsigned int lastActionIdentifier = 4;
	std::uniform_int_distribution<unsigned int> clientIDDistribution(0, clients.size() - 1);
	std::uniform_int_distribution<unsigned int> clientActionDistribution(0, lastActionIdentifier);
	if(tellers.size() == 0)
		clientActionDistribution = std::uniform_int_distribution<unsigned int>(0, lastActionIdentifier - 1);
	file().write("Starting state:\nID\tAccount balance\n");
	for(unsigned int i = 0; i < clients.size(); ++i){
		std::stringstream message;
		message << clients[i].getID();
        if(clients[i].getType() == ClientType::business)
            message << "[B]";
        message << "\t" << clients[i].getBalance() << std::endl;
		file().write(message.str());
    }
	for(unsigned int i = 0; i < simulationLength; ++i){
		std::stringstream timeStamp;
		timeStamp << "[" << i + 1 << "] ";
		file().write(timeStamp.str());
		otm.simulate(balance);
		itm.simulate(balance);
		for(unsigned int i = 0; i < tellers.size(); ++i)
			tellers[i].simulate(balance);
		unsigned int clientID = clientIDDistribution(gen());
		Account &chosen = clients[clientID];
		if(chosen.getState() != ClientState::notBusy){
			logBoth("No new client\n");
			console().write("\n");
			std::this_thread::sleep_for(std::chrono::seconds(1));
			continue;
		}
		unsigned int clientAction = clientActionDistribution(gen());
		bool isBusiness = chosen.getType() == ClientType::business;
		try{
			if(clientAction == 0)
				getShortestQueue(true, true, isBusiness)->getInfo(chosen);
			else if(clientAction == 1)
				getShortestQueue(true, true, isBusiness)->changePIN(chosen);
			else if(clientAction == 2)
				getShortestQueue(true, false, isBusiness)->withdrawMoney(chosen, balance);
			else if(clientAction == 3)
				getShortestQueue(false, true, isBusiness)->depositMoney(chosen, balance);
			else
                dynamic_cast<Teller*>(getShortestQueue(false, false, isBusiness))->takeLoan(chosen);
		}
		catch(std::logic_error err){
			continue;
		}
		if(balance < 0){
			std::string errMessage("ERR1 - Bank branch is bankrupt.\n");
			std::runtime_error err(errMessage);
			throw err;
		}
		std::stringstream message;
        message << "Branch balance: " << balance << ".\n";
        message << "State of queues: \nName\tID\tClient ID\tTime Remaining\tQueue Size\n";
        file().write(message.str());
		logQueueInfo(&otm);
        logQueueInfo(&itm);
        for(unsigned int i = 0; i < tellers.size(); ++i)
            logQueueInfo(&tellers[i]);
		std::cout << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	file().getStream().close();
	return true;
}
