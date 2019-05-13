#include "teller.h"
Teller::Teller(int tid = -1) : BankElement(tid, "Teller ") {}
virtual void Teller::getInfo(Account &client){
	add(client, 5);
}
virtual void Teller::changePIN(Account &client){
	add(client, 6);
}
virtual void Teller::withdrawMoney(Account &client){
	add(client, 7);
}
virtual void Teller::depositMoney(Account &client){
	add(client, 7);
}
void Teller::takeLoan(Account &client){
	add(client, 15, ClientState::loanEval);
}
void Teller::evalLoan(BankBranch *branch){
	std::uniform_int_distribution<unsigned int> chancePositiveDecision(0, 2);
	unsigned int decision = chancePositiveDecision(gen());
	Account &client = std::get<0>(queue.front());
	if(decision == 2 && client.getBalance() >= 0){
		std::uniform_int_distribution<long long> loanAmountDistribution(1, 1000);
		long long loan = loanAmountDistribution(gen()) * 1000;
		client.setBalance(client.getBalance() + loan);
		branch->setBalance(branch->getBalance() - loan);
		std::cout << "Client " << client.getID() << " was approved for a loan of $" << loan << std::endl;
	}
	else
		std::cout << "Client " << client.getID() << " was not approved for a loan\n";
}
virtual void Teller::simulate(BankBranch *branch){
	std::cout << timeRemaining << '\t';
	if(timeRemaining)
		--timeRemaining;
	else
		return;
	if(!timeRemaining){
		if(std::get<0>(queue.front()).getState() == ClientState::loanEval){
			std::get<0>(queue.front()).setState(ClientState::busy);
			timeRemaining = 10;
			evalLoan(branch);
		}
		else{
			std::get<0>(queue.front()).setState(ClientState::notBusy);
			queue.pop();
			if(!queue.empty()){
			    timeRemaining = std::get<1>(queue.front());
		    	std::cout << "Client " << std::get<0>(queue.front()).getID() << " now in front of queue to " << name << id << std::endl;
			}
		}
	}
}