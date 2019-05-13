#include "bankelement.h"
BankElement::BankElement(int bid, std::string n) : id(bid), queue(), timeRemaining(0), name(n) {}
virtual void BankElement::getInfo(Account &client) = 0;
virtual void BankElement::changePIN(Account &client) = 0;
virtual void BankElement::withdrawMoney(Account &client) = 0;
virtual void BankElement::depositMoney(Account &client) = 0;
int BankElement::getID() const{
	return id;
}
size_t BankElement::getQueueSize() const{
	return queue.size();
}
virtual void BankElement::add(Account &client, const unsigned int &time, ClientState s = ClientState::busy){
	client.setState(s);
	queue.push({client, time});
	if(!timeRemaining)
		timeRemaining = time;
	std::cout << "Client " << client.getID() << " joins queue to " << name << id << std::endl;
}
virtual void BankElement::simulate(){
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
	client.setBalance(client.getBalance() + amount);
}
void BankElement::withdraw(Account &client){
	std::uniform_int_distribution<unsigned int> dis(1, client.getBalance() / 100);
	long long amount = dis(gen()) * 100;
	if(client.getType() == ClientType::business)
		amount *= 10;
	client.setBalance(client.getBalance() - amount);
}