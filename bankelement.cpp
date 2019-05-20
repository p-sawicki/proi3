//author: Piotr Sawicki
#include "bankelement.h"
BankElement::BankElement(int bid, std::string n) : BankElementInterface(), id(bid), queue(), timeRemaining(0), name(n){}
void BankElement::newBalance(Account &client){
	std::stringstream message;
	message << " Their updated balance: $" << client.getBalance() << ".\n";
	logBoth(message.str());
}
int BankElement::getID() const{
	return id;
}
size_t BankElement::getQueueSize() const{
	return queue.size();
}
std::string BankElement::getName() const{
    return name;
}
int BankElement::getQueueFront() const{
	const int nobodyInQueueFlag = -1;
    if(!queue.empty())
        return std::get<0>(queue.front()).getID();
    else
        return nobodyInQueueFlag;
}
unsigned int BankElement::getTimeRemaining() const{
    return timeRemaining;
}
void BankElement::add(Account &client, const unsigned int &time, ClientState s){
	client.setState(s);
    unsigned int timeToAdd = time;
    const unsigned int additionalTimeBusinessClient = 5;
    if(client.getType() == ClientType::business)
        timeToAdd += additionalTimeBusinessClient;
	queue.push({client, timeToAdd});
	if(!timeRemaining)
		timeRemaining = timeToAdd;
	std::stringstream message;
	message << "Client " << client.getID() << " joins queue to " << name << id << "\n";
	logBoth(message.str());
}
void BankElement::add(Account &client, const unsigned int &time){
    add(client, time, ClientState::busy);
}
void BankElement::deposit(Account &client, long long &branchBalance){
	const unsigned int maxAmountToDeposit = 100;
	const unsigned int standardDepositMultiplier = 100;
	const unsigned int additionalBusinessDepositMultiplier = 10;
	std::uniform_int_distribution<unsigned int> dis(1, maxAmountToDeposit);
	long long amount = dis(gen()) * standardDepositMultiplier;
	if(client.getType() == ClientType::business)
		amount *= additionalBusinessDepositMultiplier;
	client += amount;
    branchBalance += amount;
	std::stringstream message;
	message << "Client " << client.getID() << " deposits $" << amount << " into their account.";
	logBoth(message.str());
	newBalance(client);
}
void BankElement::withdraw(Account &client, long long &branchBalance){
	std::stringstream message;
	const unsigned int minimumToWithdraw = 100;
	if(client.getBalance() < minimumToWithdraw){
		message << "Client " << client.getID() << " does not have enough money to withdraw.\n";
		logBoth(message.str());
		return;
	}	
	std::uniform_int_distribution<unsigned int> dis(1, client.getBalance() / minimumToWithdraw); // division and multiplication by 100 to get prettier values (ending in -00)
	long long amount = dis(gen()) * minimumToWithdraw;
	client -= amount;
    branchBalance -= amount;
	message << "Client " << client.getID() << " withdraws $" << amount << " from their account.";
	logBoth(message.str());
	newBalance(client);
}
void BankElement::getInfoMessage(Account &client){
	std::stringstream message;
	message << "Client " << client.getID() << " wants to access their account info.\n";
	logBoth(message.str());
}
void BankElement::changePINMessage(Account &client){
	std::stringstream message;
	message << "Client " << client.getID() << " wants to change their PIN.\n";
	logBoth(message.str());
}
