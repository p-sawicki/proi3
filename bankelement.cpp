#include "bankelement.h"
BankElement::BankElement(int bid, std::string n) : id(bid), queue(), timeRemaining(0), name(n) {}
void BankElement::newBalance(Account &client){
	std::cout << "Their updated balance: $" << client.getBalance() << ".\n";
}
int BankElement::getID() const{
	return id;
}
size_t BankElement::getQueueSize() const{
	return queue.size();
}
void BankElement::add(Account &client, const unsigned int &time, ClientState s){
	client.setState(s);
	queue.push({client, time});
	if(!timeRemaining)
		timeRemaining = time;
	std::cout << "Client " << client.getID() << " joins queue to " << name << id << std::endl;
}
void BankElement::simulate(){
	std::cout << timeRemaining << '\t';
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
	std::cout << "Client " << client.getID() << " deposits $" << amount << " into their account.";
	newBalance(client);
}
void BankElement::withdraw(Account &client){
	std::uniform_int_distribution<unsigned int> dis(1, client.getBalance() / 100);
	long long amount = dis(gen()) * 100;
	client -= amount;
	std::cout << "Client " << client.getID() << " withdraws $" << amount << " from their account.";
	newBalance(client);
}
