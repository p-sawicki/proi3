#include "atm.h"
ATM::ATM(int aid) : BankElement(aid, "ATM ") {}
void ATM::getInfo(Account &client){
	add(client, 3);
	std::stringstream message;
	message << "Client " << client.getID() << " wants to access their account info.\n";
	std::cout << message.str();
	file() << message.str();
}
void ATM::changePIN(Account &client){
	add(client, 4);
	std::stringstream message;
	message << "Client " << client.getID() << " wants to change their PIN.\n";
	std::cout << message.str();
	file() << message.str();
}
std::string ATM::errorMessageLog() const{
	std::string errMessage("Error 0x1 - Invalid function call. Continuing...\n");
	std::cout << errMessage;
	file() << errMessage;
	return errMessage;
}
InputTM::InputTM(int iid) : ATM(iid){}
void InputTM::withdrawMoney(Account &client, long long &branchBalance){
	std::logic_error exc(errorMessageLog());
	throw exc;
}
void InputTM::depositMoney(Account &client, long long &branchBalance){
	add(client, 5);
	deposit(client, branchBalance);
}

OutputTM::OutputTM(int oid) : ATM(oid){}
void OutputTM::withdrawMoney(Account &client, long long &branchBalance){
	add(client, 5);
	withdraw(client, branchBalance);
}
void OutputTM::depositMoney(Account &client, long long &branchBalance){
	std::logic_error exc(errorMessageLog());
	throw exc;
}
