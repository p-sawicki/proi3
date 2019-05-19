#include "bankelement.h"
BankElement::BankElement(int bid, std::string n) : id(bid), queue(), timeRemaining(0), name(n) {}
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
    if(!queue.empty())
        return std::get<0>(queue.front()).getID();
    else
        return -1;
}
unsigned int BankElement::getTimeRemaining() const{
    return timeRemaining;
}
ClientType BankElement::getType() const{
    return ClientType::individual;
}
void BankElement::add(Account &client, const unsigned int &time, ClientState s){
	client.setState(s);
    unsigned int timeToAdd = time;
    if(client.getType() == ClientType::business)
        timeToAdd += 5;
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
	std::uniform_int_distribution<unsigned int> dis(1, 100);
	long long amount = dis(gen()) * 100;
	if(client.getType() == ClientType::business)
		amount *= 10;
	client += amount;
    branchBalance += amount;
	std::stringstream message;
	message << "Client " << client.getID() << " deposits $" << amount << " into their account.";
	logBoth(message.str());
	newBalance(client);
}
void BankElement::withdraw(Account &client, long long &branchBalance){
	std::uniform_int_distribution<unsigned int> dis(1, client.getBalance() / 100);
	long long amount = dis(gen()) * 100;
	client -= amount;
    branchBalance -= amount;
	std::stringstream message;
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
BankElement::~BankElement(){}
