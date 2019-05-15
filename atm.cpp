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

InputTM::InputTM(int iid) : ATM(iid){}
void InputTM::withdrawMoney(Account &client){
	std::cout << "can't do that here!\n"; //TODO: exception
}
void InputTM::depositMoney(Account &client){
	add(client, 5);
	deposit(client);
}

OutputTM::OutputTM(int oid) : ATM(oid){}
void OutputTM::withdrawMoney(Account &client){
	add(client, 5);
	withdraw(client);
}
void OutputTM::depositMoney(Account &client){
	std::cout << "can't do that here!\n"; //TODO: exception
}
