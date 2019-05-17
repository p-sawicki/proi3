#include "bankelement.h"
BankElement::BankElement(int bid, std::string n) : id(bid), queue(), timeRemaining(0), name(n) {}
void BankElement::newBalance(Account &client){
	std::stringstream message;
	message << " Their updated balance: $" << client.getBalance() << ".\n";
	std::cout << message.str();
	file() << message.str();
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
void BankElement::add(Account &client, const unsigned int &time, ClientState s){
	client.setState(s);
	queue.push({client, time});
	if(!timeRemaining)
		timeRemaining = time;
	std::stringstream message;
	message << "Client " << client.getID() << " joins queue to " << name << id << "\n";
	std::cout << message.str();
	file() << message.str();
}
void BankElement::simulate(long long &balance){
	if(timeRemaining)
		--timeRemaining;
	else
		return;
	if(!timeRemaining){
		std::get<0>(queue.front()).setState(ClientState::notBusy);
		queue.pop();
		if(!queue.empty()){
			timeRemaining = std::get<1>(queue.front());
	  		std::cout << "Client " << std::get<0>(queue.front()).getID() << " now in front of queue to " << name << id << std::endl; 
		}
	}
}
void BankElement::deposit(Account &client){
	std::uniform_int_distribution<unsigned int> dis(1, 100);
	long long amount = dis(gen()) * 100;
	if(client.getType() == ClientType::business)
		amount *= 10;
	client += amount;
	std::stringstream message;
	message << "Client " << client.getID() << " deposits $" << amount << " into their account.";
	std::cout << message.str();
	file() << message.str();
	newBalance(client);
}
void BankElement::withdraw(Account &client){
	std::uniform_int_distribution<unsigned int> dis(1, client.getBalance() / 100);
	long long amount = dis(gen()) * 100;
	client -= amount;
	std::stringstream message;
	message << "Client " << client.getID() << " withdraws $" << amount << " from their account.";
	std::cout << message.str();
	file() << message.str();
	newBalance(client);
}
void BankElement::getInfoMessage(Account &client){
	std::stringstream message;
	message << "Client " << client.getID() << " wants to access their account info.\n";
	std::cout << message.str();
	file() << message.str();
}
void BankElement::changePINMessage(Account &client){
	std::stringstream message;
	message << "Client " << client.getID() << " wants to change their PIN.\n";
	std::cout << message.str();
	file() << message.str();
}
BankElement::~BankElement(){}
