#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
enum ClientType {individual, business};
class Account{
    int id;
    ClientType type;
    long long balance;

    public:
    Account(int aid = -1) : id(aid){
        type = ClientType::individual; //todo: randomize
        balance = 0; //todo: randomize
    }
    int getID() const{
	    return id;
    }
};

class BankElement{
	protected:
    int id;
    std::queue<std::tuple<Account, unsigned int>> queue;
    unsigned int timeRemaining;

    public:
    BankElement(int bid) : id(bid), queue(), timeRemaining(0) {}
    virtual void getInfo(const Account &client) = 0;
    int getID() const{
	    return id;
    }
    void showQueue() const{
	    std::cout << std::get<0>(queue.front()).getID() << "\t" << std::get<1>(queue.front()) << std::endl;
	    std::cout << "remaining: " << timeRemaining << std::endl;
    }
};

class Teller : public BankElement{
    public:
    Teller(int tid = -1) : BankElement(tid){}
    virtual void getInfo(const Account &client){
        queue.push({client, 5});
	if(!timeRemaining)
		timeRemaining = 5;
        std::cout << "Client " << client.getID() << "joins queue to teller " << id << std::endl;
    }
};

class ATM : public BankElement{
    public:
    ATM(int aid = -1) : BankElement(aid){}
    virtual void getInfo(const Account &client){
        queue.push({client, 3});
	if(!timeRemaining)
		timeRemaining = 3;
        std::cout << "Client " << client.getID() << "joins queue to ATM " << id << std::endl;
    }
};

class InputTM : public ATM{
    public:
    InputTM(int iid = -1) : ATM(iid){}
};

class OutputTM : public ATM{
    public:
    OutputTM(int oid = -1) : ATM(oid){}
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
    elem->showQueue();
}
