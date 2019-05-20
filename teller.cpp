//author: Piotr Sawicki
#include "teller.h"
void Teller::evalLoan(long long &branchBalance){
	std::uniform_int_distribution<unsigned int> chancePositiveDecision(0, 2);
	unsigned int decision = chancePositiveDecision(gen());
	Account &client = std::get<0>(queue.front());
	if(decision == 2 && client.getBalance() >= 0){
		const long long maxLoanAmount = 1'000;
		const long long loanAmountMultiplier = 1'000;
	    std::uniform_int_distribution<long long> loanAmountDistribution(1, maxLoanAmount);
	    long long loan = loanAmountDistribution(gen()) * loanAmountMultiplier;
		client += loan;
    	branchBalance -= loan;
		std::stringstream message;
    	message << "Client " << client.getID() << " was approved for a loan of $" << loan << ".";
    	logBoth(message.str());
    	newBalance(client);
    }
    else{
    	std::stringstream message;
    	message << "Client " << client.getID() << " was not approved for a loan.\n";
    	logBoth(message.str());
    }
}
Teller::Teller(int tid) : BankElement(tid, "Teller "){}
void Teller::getInfo(Account &client){
	const unsigned int timeToGetInfoTeller = 5;
	add(client, timeToGetInfoTeller);
	getInfoMessage(client);
}
void Teller::changePIN(Account &client){
	const unsigned int timeToChangePINTeller = 6;
	add(client, timeToChangePINTeller);
	changePINMessage(client);
}
void Teller::withdrawMoney(Account &client, long long &branchBalance){
	const unsigned int timeToWithdrawMoneyTeller = 7;
	add(client, timeToWithdrawMoneyTeller);
	withdraw(client, branchBalance);
}
void Teller::depositMoney(Account &client, long long &branchBalance){
	const unsigned int timeToDepositMoneyTeller = 7;
	add(client, timeToDepositMoneyTeller);
    deposit(client, branchBalance);
}
void Teller::takeLoan(Account &client){
	const unsigned int timeToEvaluateLoan = 15;
	add(client, timeToEvaluateLoan, ClientState::loanEval);
	std::stringstream message;
	message << "Client " << client.getID() << " wants to take out a loan.\n";
	logBoth(message.str());
}
void Teller::simulate(long long &branchBalance){
	if(timeRemaining)
    	--timeRemaining;
    else
    	return;
    if(!timeRemaining){
    	if(std::get<0>(queue.front()).getState() == ClientState::loanEval){
    		std::get<0>(queue.front()).setState(ClientState::busy);
    		const unsigned int timeToSignLoan = 10;
    		timeRemaining = timeToSignLoan;
    		evalLoan(branchBalance);
    	}
    	else{
    		std::get<0>(queue.front()).setState(ClientState::notBusy);
    		queue.pop();
    		if(!queue.empty()){
    		    timeRemaining = std::get<1>(queue.front());
				std::stringstream message;
    	    	message << "Client " << std::get<0>(queue.front()).getID() << " is now in front of queue to " << name << id << "\n";
				console().write(message.str());
    		}
    	}
    }
}