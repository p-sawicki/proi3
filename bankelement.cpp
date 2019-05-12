#include "bankelement.h"
class BankElement{
	protected:
    int id;
    std::queue<std::tuple<Account&, unsigned int>> queue;
    unsigned int timeRemaining;
    std::string name;

    public:
    BankElement(int bid, std::string n) : id(bid), queue(), timeRemaining(0), name(n) {}
    virtual void getInfo(Account &client) = 0;
    virtual void changePIN(Account &client) = 0;
    virtual void withdrawMoney(Account &client) = 0;
    virtual void depositMoney(Account &client) = 0;
    int getID() const{
	    return id;
    }
    void showQueue() const{
	    std::cout << std::get<0>(queue.front()).getID() << "\t" << std::get<1>(queue.front()) << std::endl;
	    std::cout << "remaining: " << timeRemaining << std::endl;
    }
    size_t getQueueSize() const{
	    return queue.size();
    }
    virtual void add(Account &client, const unsigned int &time, ClientState s = ClientState::busy){
	    client.setState(s);
	    queue.push({client, time});
	    if(!timeRemaining)
		    timeRemaining = time;
	    std::cout << "Client " << client.getID() << " joins queue to " << name << id << std::endl;
    }
    virtual void simulate(){
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
    void deposit(Account &client){
	    std::uniform_int_distribution<unsigned int> dis(1, 100);
	    long long amount = dis(gen()) * 100;
	    if(client.getType() == ClientType::business)
		    amount *= 10;
	    client.setBalance(client.getBalance() + amount);
    }
    void withdraw(Account &client){
	    std::uniform_int_distribution<unsigned int> dis(1, client.getBalance() / 100);
	    long long amount = dis(gen()) * 100;
	    if(client.getType() == ClientType::business)
		    amount *= 10;
	    client.setBalance(client.getBalance() - amount);
    }
};