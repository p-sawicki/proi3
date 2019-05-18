#include "bankbranch.h"
BankElement* BankBranch::getShortestQueue(bool includeOTM, bool includeITM, bool isBusiness){
	BankElement* ans = tellers[0];
	unsigned int shortest = tellers[0]->getQueueSize();
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
		if(!tellers[i]->getQueueSize())
			return tellers[i];
		if(i && tellers[i]->getQueueSize() < shortest){
			shortest = tellers[i]->getQueueSize();
			ans = tellers[i];
		}
	}
	return ans;	
}
BankElement* BankBranch::getShortestQueue(bool includeOTM, bool includeITM){
    return getShortestQueue(includeOTM, includeITM, false);
}
BankBranch::BankBranch(const unsigned int &clientsAmount, const unsigned int &tellersAmount, const unsigned int &duration)
    	: itm(InputTM(tellersAmount)), otm(OutputTM(tellersAmount + 1)), clients(std::vector<Account>(0)),
	tellers(std::vector<BankElement*>(0)), balance(10'000'000), simulationLength(duration){
    	unsigned int max = clientsAmount > tellersAmount ? clientsAmount : tellersAmount;
   	for(unsigned int i = 0; i < max; ++i){
    	if(!(tellersAmount / 10) && tellersAmount >= 2)
		    businessOnlyTellerAmount = 1;
    	else
		    businessOnlyTellerAmount = tellersAmount / 10;
       		if(i < clientsAmount)
            	clients.push_back(Account(i));
            if(i < tellersAmount){
                if(i < tellersAmount - businessOnlyTellerAmount){
                    BankElement* standardTeller = new Teller<ClientType::individual>(i);
                    tellers.push_back(standardTeller);
                }
                else{
                    BankElement* businessTeller = new Teller<ClientType::business>(i);
                    tellers.push_back(businessTeller);
                }
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
	std::uniform_int_distribution<unsigned int> chanceClientComes(1, 100);
	std::uniform_int_distribution<unsigned int> clientIDDistribution(0, clients.size() - 1);
	std::uniform_int_distribution<unsigned int> clientActionDistribution(0, 4);
	file() << "Starting state:\nID\tAccount balance\n";
	for(unsigned int i = 0; i < clients.size(); ++i)
		file() << clients[i].getID() << "\t" << clients[i].getBalance() << std::endl;
	for(unsigned int i = 0; i < simulationLength; ++i){
		file() << "[" << i + 1 << "] ";
		otm.simulate(balance);
		itm.simulate(balance);
		for(unsigned int i = 0; i < tellers.size(); ++i)
			tellers[i]->simulate(balance);
		unsigned int clientID = clientIDDistribution(gen());
		Account &chosen = clients[clientID];
		if((chanceClientComes(gen()) > 100) || chosen.getState() != ClientState::notBusy){
			std::cout << "No new client\n";
			file() << "No new client\n";
			continue;
		}
		unsigned int clientAction = clientActionDistribution(gen());
		bool isBusiness = chosen.getType() == ClientType::business;
		try{
			if(clientAction == 0)
				getShortestQueue(1, 1, isBusiness)->getInfo(chosen);
			else if(clientAction == 1)
				getShortestQueue(1, 1, isBusiness)->changePIN(chosen);
			else if(clientAction == 2)
				getShortestQueue(1, 0, isBusiness)->withdrawMoney(chosen);
			else if(clientAction == 3)
				getShortestQueue(0, 1, isBusiness)->depositMoney(chosen);
            else{
                if(chosen.getType() == ClientType::individual)
                    dynamic_cast<Teller<ClientType::individual>*>(getShortestQueue(0, 0, isBusiness))->takeLoan(chosen);
                else
                    dynamic_cast<Teller<ClientType::business>*>(getShortestQueue(0, 0, isBusiness))->takeLoan(chosen);
            } 
		}
		catch(std::logic_error err){
			continue;
		}
		if(balance < 0){
			std::string errMessage("ERR1 - Bank branch is bankrupt.\n");
			std::runtime_error err(errMessage);
			throw err;
		}
        file() << "Branch balance: " << balance << ".\n";
        file() << "State of queues: \nName\tID\tClient ID\tTime Remaining\tQueue Size\n";
        logQueueInfo(&otm);
        logQueueInfo(&itm);
        for(unsigned int i = 0; i < tellers.size(); ++i)
            logQueueInfo(tellers[i]);
		std::cout << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	file().close();
	return true;
}
BankBranch::~BankBranch(){
    for(unsigned int i = 0; i < tellers.size(); ++i)
        delete tellers[i];
}
