#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
enum ClientType {individual, business};
class Account{
    unsigned int id;
    ClientType type;
    long long balance;

    public:
    Account(const unsigned int &aid) : id(aid){
        type = ClientType::individual; //todo: randomize
        balance = 0; //todo: randomize
    }
    unsigned int getID() const{
	    return id;
    }
};

class BankElement{
	protected:
    unsigned int id;
    std::queue<std::tuple<Account, unsigned int>> queue;
    unsigned int timeRemaining;

    public:
    BankElement(const unsigned int &bid) : id(bid),  {}
    virtual void getInfo(const Account &client) = 0;
};

class Teller : public BankElement{
    public:
    Teller(const unsigned int &tid) : BankElement(tid){}
    virtual void getInfo(const Account &client){
        queue.push({client, 5});
        std::cout << "Client " << client.getID() << "joins queue to teller " << id << std::endl;
    }
};

class ATM : public BankElement{
    public:
    ATM(const unsigned int &aid) : BankElement(aid){}
    virtual void getInfo(const Account &client){
        queue.push({client, 3});
        std::cout << "Client " << client.getID() << "joins queue to ATM " << id << std::endl;
    }
};

class InputTM : public ATM{
    public:
    InputTM(const unsigned int &iid) : ATM(iid){}
};

class OutputTM : public ATM{
    public:
    OutputTM(const unsigned int &oid) : ATM(oid){}
};

class BankBranch{
	public:
    std::vector<Account> clients;
    std::vector<Teller> tellers;
    InputTM itm;
    OutputTM otm;

    BankBranch(const unsigned int &clientsAmount, const unsigned int &tellersAmount)
    : itm(InputTM(tellersAmount)), otm(OutputTM(tellersAmount + 1)), clients(std::vector<Account>(clientsAmount)),
		    tellers(std::vector<Teller>(tellersAmount)){
        unsigned int max = clientsAmount > tellersAmount ? clientsAmount : tellersAmount;
        unsigned int i = 0;
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
    bb.tellers[0].getInfo(bb.clients[0]);
}
