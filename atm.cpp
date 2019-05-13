#include "atm.h"
ATM::ATM(int aid = -1) : BankElement(aid, "ATM ") {}
virtual void ATM::getInfo(Account &client){
	add(client, 3);
}
virtual void ATM::changePIN(Account &client){
	add(client, 4);
}

InputTM::InputTM(int iid = -1) : ATM(iid){}
virtual void InputTM::withdrawMoney(Account &client){
	std::cout << "can't do that here!\n"; //TODO: exception
}
virtual void InputTM::depositMoney(Account &client){
	add(client, 5);
	deposit(client);
}

OutputTM::OutputTM(int oid = -1) : ATM(oid){}
virtual void OutputTM::withdrawMoney(Account &client){
	add(client, 5);
	withdraw(client);
}
virtual void OutputTM::depositMoney(Account &client){
	std::cout << "can't do that here!\n"; //TODO: exception
}