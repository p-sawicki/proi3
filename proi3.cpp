#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <string>
enum ClientType {individual, business};
enum ClientState {notBusy, busy, loanEval};
class Account{
    int id;
    ClientType type;
    ClientState state;
    long long balance;

    public:
    Account(int aid = -1) : id(aid), state(ClientState::notBusy){
        type = ClientType::individual; //TODO: randomize
        balance = 0; //TODO: randomize
    }
    int getID() const{
	    return id;
    }
    void setState(const ClientState &s){
	    state = s;
    }
};

class BankElement{
	protected:
    int id;
    std::queue<std::tuple<Account, unsigned int>> queue;
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
    void add(Account &client, const unsigned int &time, const std::string &nname, ClientState s = ClientState::busy){
	    queue.push({client, time});
	    if(!timeRemaining)
		    timeRemaining = time;
	    client.setState(s);
	    std::cout << "Client " << client.getID() << " joins queue to " << nname << id << std::endl;
    }
};

class Teller : public BankElement{
    public:
    Teller(int tid = -1) : BankElement(tid, "Teller ") {}
    virtual void getInfo(Account &client){
	add(client, 5, name);
    }
    virtual void changePIN(Account &client){
	    add(client, 6, name);
    }
    virtual void takeMoney(Account &client){
	    add(client, 7, name);
    }
    virtual void depositMoney(Account &client){
	    add(client, 7, name);
    }
    void takeLoan(Account &client){
	    add(client, 15, name, ClientState::loanEval);
    }
};

class ATM : public BankElement{
    public:
    ATM(int aid = -1) : BankElement(aid, "ATM ") {}
    virtual void getInfo(Account &client){
	    add(client, 3, name);
    }
    virtual void changePIN(Account &client){
	    add(client, 4, name);
    }
};

class InputTM : public ATM{
    public:
    InputTM(int iid = -1) : ATM(iid){}
    virtual void takeMoney(Account &client){
	    std::cout << "can't do that here!\n"; //TODO: exception
    }
    virtual void depositMoney(Account &client){
	    add(client, 5, name);
    }
};

class OutputTM : public ATM{
    public:
    OutputTM(int oid = -1) : ATM(oid){}
    virtual void takeMoney(Account &client){
	    add(client, 5, name);
    }
    virtual void depositMoney(Account &client){
	    std::cout << "can't do that here!\n"; //TODO: exception
    }
};

class BankBranch{
	public:
    std::vector<Account> clients;
    std::vector<Teller> tellers;
    InputTM itm;
    OutputTM otm;

    BankBranch(const unsigned int &clientsAmount, const unsigned int &tellersAmount)
    : itm(InputTM(tellersAmount)), otm(OutputTM(tellersAmount + 1)), clients(std::vector<Account>(0)),
		    tellers(std::vector<Teller>(0)){
        unsigned int max = clientsAmount > tellersAmount ? clientsAmount : tellersAmount;
        int i = 0;
        for(; i < max; ++i){
            if(i < clientsAmount)
                clients.push_back(Account(i));
            if(i < tellersAmount)
                tellers.push_back(Teller(i));
        }
    }
};
int main(){
    BankBranch bb(5, 5);
    BankElement *elem = &bb.otm;
    elem->getInfo(bb.clients[0]);
    elem->changePIN(bb.clients[1]);
    elem->showQueue();
}
