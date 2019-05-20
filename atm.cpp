//author: Piotr Sawicki
#include "atm.h"
ATM::ATM(int aid) : BankElement(aid, "ATM ") {}
void ATM::getInfo(Account &client){
	const unsigned int timeToGetInfoATM = 3;
	add(client, timeToGetInfoATM);
	std::stringstream message;
	message << "Client " << client.getID() << " wants to access their account info.\n";
	logBoth(message.str());
}
void ATM::changePIN(Account &client){
	const unsigned int timeToChangePINATM = 4;
	add(client, timeToChangePINATM);
	std::stringstream message;
	message << "Client " << client.getID() << " wants to change their PIN.\n";
	logBoth(message.str());
}
std::string ATM::errorMessageLog() const{
	std::string errMessage("ERR3 - Invalid function call. Continuing...\n");
	logBoth(errMessage);
	return errMessage;
}
void ATM::simulate(long long &balance){
	if(timeRemaining)
		--timeRemaining;
	else
		return;
	if(!timeRemaining){
		std::get<0>(queue.front()).setState(ClientState::notBusy);
		queue.pop();
		if(!queue.empty()){
			timeRemaining = std::get<1>(queue.front());
			std::stringstream message;
	  		message << "Client " << std::get<0>(queue.front()).getID() << " now in front of queue to " << name << id << "\n";
			console().write(message.str()); 
		}
	}
}
InputTM::InputTM(int iid) : ATM(iid){}
void InputTM::withdrawMoney(Account &client, long long &branchBalance){
	std::logic_error exc(errorMessageLog());
	throw exc;
}
void InputTM::depositMoney(Account &client, long long &branchBalance){
	const unsigned int timeToDepositMoneyATM = 5;
	add(client, timeToDepositMoneyATM);
	deposit(client, branchBalance);
}

OutputTM::OutputTM(int oid) : ATM(oid){}
void OutputTM::withdrawMoney(Account &client, long long &branchBalance){
	const unsigned int timeToWithdrawMoneyATM = 5;
	add(client, timeToWithdrawMoneyATM);
	withdraw(client, branchBalance);
}
void OutputTM::depositMoney(Account &client, long long &branchBalance){
	std::logic_error exc(errorMessageLog());
	throw exc;
}
