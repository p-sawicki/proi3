//author: Piotr Sawicki
#include "account.h"
Account::Account(int aid) : id(aid), state(ClientState::notBusy){
	std::uniform_int_distribution<unsigned int> typeDistribution(0, 9);
	const long long maxStartingBalanceIndividual = 10'000;
	const long long businessStartingBalanceMultiplier = 1'000;
	std::uniform_int_distribution<long long> balanceDistribution(0, maxStartingBalanceIndividual);
	typeDistribution(gen()) < 9 ? type = ClientType::individual : type = ClientType::business;
	balance = balanceDistribution(gen());
	if(type == ClientType::business)
		balance *= businessStartingBalanceMultiplier;
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
Account& Account::operator+=(const long long &b){
	balance += b;
	return *this;
}
Account& Account::operator-=(const long long &b){
	balance -= b;
	return *this;
}