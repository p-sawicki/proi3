#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <thread>
enum ClientType {individual, business};
enum ClientState {notBusy, busy, loanEval};
std::mt19937& gen(){
	static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937 generator(seed);
	return generator;
}
class BankBranch{
	std::vector<Account> clients;
	std::vector<Teller> tellers;
	InputTM itm;
	OutputTM otm;
	long long balance;

	public:
	BankBranch(const unsigned int &clientsAmount, const unsigned int &tellersAmount);
	long long getBalance() const;
	BankElement* getShortestQueue(bool includeOTM, bool includeITM) const;
	void simulate();
}
class Account{
    int id;
    ClientType type;
    ClientState state;
    long long balance;

    public:
    Account(int aid = -1) : id(aid), state(ClientState::notBusy){
	    std::uniform_int_distribution<unsigned int> typeDistribution(0, 1);
	    std::uniform_int_distribution<long long> balanceDistribution(0, 10000);
	    typeDistribution(gen()) ? type = ClientType::individual : type = ClientType::business;
	    balance = balanceDistribution(gen());
	    if(type == ClientType::business)
		    balance *= 1000;
    }
    int getID() const{
	    return id;
    }
    ClientState getState() const{
	    return state;
    }
    void setState(const ClientState &s){
	    state = s;
    }
    ClientType getType() const{
	    return type;
    }
    long long getBalance() const{
	    return balance;
    }
    void setBalance(const long long &b){
	    balance = b;
    }
};

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
    virtual void takeMoney(Account &client) = 0;
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

class Teller : public BankElement{
    public:
    Teller(int tid = -1) : BankElement(tid, "Teller ") {}
    virtual void getInfo(Account &client){
	add(client, 5);
    }
    virtual void changePIN(Account &client){
	    add(client, 6);
    }
    virtual void takeMoney(Account &client){
	    add(client, 7);
    }
    virtual void depositMoney(Account &client){
	    add(client, 7);
    }
    void takeLoan(Account &client){
	    add(client, 15, ClientState::loanEval);
    }
    void evalLoan(BankBranch *branch){
	    std::uniform_int_distribution<unsigned int> chancePositiveDecision(0, 2);
	    unsigned int decision = chancePositiveDecision(gen());
	    Account &client = std::get<0>(queue.front());
	    if(decision == 2 && client.getBalance() >= 0){
		    std::uniform_int_distribution<long long> loanAmountDistribution(1, 1000);
		    long long loan = loanAmountDistribution(gen()) * 1000;
		    client.setBalance(client.getBalance() + loan);
		    branch->setBalance(branch->getBalance() - loan);
		    std::cout << "Client " << client.getID() << " was approved for a loan of $" << loan << std::endl;
	    }
	    else
		    std::cout << "Client " << client.getID() << " was not approved for a loan\n";
    }
    virtual void simulate(BankBranch branch){
	    std::cout << timeRemaining << '\t';
	    if(timeRemaining)
		    --timeRemaining;
	    else
		    return;
	    if(!timeRemaining){
		    if(std::get<0>(queue.front()).getState() == ClientState::loanEval){
			    std::get<0>(queue.front()).setState(ClientState::busy);
			    timeRemaining = 10;
			    evalLoan(branch);
		    }
		    else{
			    std::get<0>(queue.front()).setState(ClientState::notBusy);
			    queue.pop();
			    if(!queue.empty()){
			    	timeRemaining = std::get<1>(queue.front());
		    		std::cout << "Client " << std::get<0>(queue.front()).getID() << " now in front of queue to " << name << id << std::endl;
			    }
		    }
	    }
    }
};

class ATM : public BankElement{
    public:
    ATM(int aid = -1) : BankElement(aid, "ATM ") {}
    virtual void getInfo(Account &client){
	    add(client, 3);
    }
    virtual void changePIN(Account &client){
	    add(client, 4);
    }
};

class InputTM : public ATM{
    public:
    InputTM(int iid = -1) : ATM(iid){}
    virtual void takeMoney(Account &client){
	    std::cout << "can't do that here!\n"; //TODO: exception
    }
    virtual void depositMoney(Account &client){
	    add(client, 5);
	    deposit(client);
    }
};

class OutputTM : public ATM{
    public:
    OutputTM(int oid = -1) : ATM(oid){}
    virtual void takeMoney(Account &client){
	    add(client, 5);
	    withdraw(client);
    }
    virtual void depositMoney(Account &client){
	    std::cout << "can't do that here!\n"; //TODO: exception
    }
};

class BankBranch{
    std::vector<Account> clients;
    std::vector<Teller> tellers;
    InputTM itm;
    OutputTM otm;
    long long balance;

	public:
    BankBranch(const unsigned int &clientsAmount, const unsigned int &tellersAmount)
    : itm(InputTM(tellersAmount)), otm(OutputTM(tellersAmount + 1)), clients(std::vector<Account>(0)),
		    tellers(std::vector<Teller>(0)), balance(10'000'000){
        unsigned int max = clientsAmount > tellersAmount ? clientsAmount : tellersAmount;
        int i = 0;
        for(; i < max; ++i){
            if(i < clientsAmount)
                clients.push_back(Account(i));
            if(i < tellersAmount)
                tellers.push_back(Teller(i));
        }
    }
    long long getBalance() const{
	    return balance;
    }
    BankElement* getShortestQueue(bool includeOTM, bool includeITM) const{
	BankElement* ans = &tellers[0];
	unsigned int shortest = tellers[0].getQueueSize();
	if(includeOTM){
		if(!otm.getQueueSize())
			return &otm;
		if(otm.getQueueSize() < shortest){
			shortest = otm.getQueueSize();
			ans = &otm;
		}
	}
	if(includeITM){
		if(!itm.getQueueSize())
			return &itm;
		if(itm.getQueueSize() < shortest){
			shortest = itm.getQueueSize();
			ans = &itm;
		}
	}
	for(int i = 0; i < tellers.size(); ++i){
		if(!tellers[i].getQueueSize())
			return &tellers[i];
		if(i && tellers[i].getQueueSize() < shortest){
			shortest = tellers[i].getQueueSize();
			ans = &tellers[i];
		}
	}
	return ans;	
    }
    void simulate(){
	std::uniform_int_distribution<unsigned int> chanceClientComes(1, 100);
	std::uniform_int_distribution<unsigned int> clientIDDistribution(0, clients.size() - 1);
	std::uniform_int_distribution<unsigned int> clientActionDistribution(0, 4);
	while(true){
		otm.simulate();
		itm.simulate();
		for(int i = 0; i < tellers.size(); ++i)
			tellers[i].simulate(this);
		std::cout << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		unsigned int clientID = clientIDDistribution(gen());
		Account &chosen = clients[clientID];
		if((chanceClientComes(gen()) > 100) || chosen.getState() != ClientState::notBusy){
			std::cout << "No client\n";
			continue;
		}
		std::cout << "Client " << clientID << " comes in";
		unsigned int clientAction = clientActionDistribution(gen());
		if(clientAction == 0){
			std::cout << " to get info\n";
			getShortestQueue(1, 1)->getInfo(chosen);
		}
		else if(clientAction == 1){
			std::cout << " to change PIN\n";
			getShortestQueue(1, 1)->changePIN(chosen);
		}
		else if(clientAction == 2){
			std::cout << " to take money out\n";
			getShortestQueue(1, 0)->takeMoney(chosen);
		}
		else if(clientAction == 3){
			std::cout << " to deposit money\n";
			getShortestQueue(0, 1)->depositMoney(chosen);
		}
		else{ 
			std::cout << " to take out a loan\n";
			dynamic_cast<Teller*>(getShortestQueue(0, 0))->takeLoan(chosen);
		}
	}
    }
};
int main(){
    BankBranch bb(100, 5);
    bb.simulate();
}
