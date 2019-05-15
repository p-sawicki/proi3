#include "teller.h"
Teller::Teller(int tid) : BankElement(tid, "Teller ") {}
void Teller::getInfo(Account &client){
	add(client, 5);
	getInfoMessage(client);
}
void Teller::changePIN(Account &client){
	add(client, 6);
	changePINMessage(client);
}
void Teller::withdrawMoney(Account &client){
	add(client, 7);
	withdraw(client);
}
void Teller::depositMoney(Account &client){
	add(client, 7);
	deposit(client);
}
void Teller::takeLoan(Account &client){
	add(client, 15, ClientState::loanEval);
	std::stringstream message;
	message << "Client " << client.getID() << " wants to take out a loan.\n";
	std::cout << message.str();
	file() << message.str();
}
void Teller::evalLoan(long long &branchBalance){
	std::uniform_int_distribution<unsigned int> chancePositiveDecision(0, 2);
	unsigned int decision = chancePositiveDecision(gen());
	Account &client = std::get<0>(queue.front());
	if(decision == 2 && client.getBalance() >= 0){
		std::uniform_int_distribution<long long> loanAmountDistribution(1, 1000);
		long long loan = loanAmountDistribution(gen()) * 1000;
		client += loan;
		branchBalance -= loan;
		std::stringstream message;
		message << "Client " << client.getID() << " was approved for a loan of $" << loan << ".";
		std::cout << message.str();
		file() << message.str();
		newBalance(client);
	}
	else{
		std::stringstream message;
		message << "Client " << client.getID() << " was not approved for a loan.\n";
		std::cout << message.str();
		file() << message.str();
	}
}
void Teller::simulate(long long &branchBalance){
	if(timeRemaining)
		--timeRemaining;
	else
		return;
	if(!timeRemaining){
		if(std::get<0>(queue.front()).getState() == ClientState::loanEval){
			std::get<0>(queue.front()).setState(ClientState::busy);
			timeRemaining = 10;
			evalLoan(branchBalance);
		}
		else{
			std::get<0>(queue.front()).setState(ClientState::notBusy);
			queue.pop();
			if(!queue.empty()){
			    timeRemaining = std::get<1>(queue.front());
		    	std::cout << "Client " << std::get<0>(queue.front()).getID() << " is now in front of queue to " << name << id << std::endl;
			}
		}
	}
}
