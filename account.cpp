#include "account.h"
Account::Account(int aid) : id(aid), state(ClientState::notBusy){
	std::uniform_int_distribution<unsigned int> typeDistribution(0, 1);
	std::uniform_int_distribution<long long> balanceDistribution(0, 10000);
	typeDistribution(gen()) ? type = ClientType::individual : type = ClientType::business;
	balance = balanceDistribution(gen());
	if(type == ClientType::business)
		balance *= 1000;
}
int Account::getID() const{
	return id;
}
ClientState Account::getState() const{
	return state;
}
void Account::setState(const ClientState &s){
	state = s;
}
ClientType Account::getType() const{
	return type;
}
long long Account::getBalance() const{
	return balance;
}
void Account::setBalance(const long long &b){
	balance = b;
}
